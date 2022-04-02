#include "Scene.h"
#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/VectorOps.h"
#include "utils/Light.h"
#include "utils/Ray.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <random>

#define PI 3.14159265358979323846264338327950288419716939937510582097

using namespace utils;

Scene::Scene()
{
    width = 640;
    height = 480;
}

Scene::Scene(int w, int h)
{
    width = w;
    height = h;
}

char *Scene::render(PinholeCamera camera) const
{
    // PinholeCamera *camera = new PinholeCamera(1.0f, 45.0f, Point(0, 0, 0));
    char *pixels = new char[width * height * 3];
    int limit = 4;
    int loc = 0;
    int aa_limit = 32;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // std::cout << x << " " << y << std::endl;
            Point P;
            Vec w;
            // Depricate point/vec soon
            Ray r;
            Point col;

            std::random_device rd;  // Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> dis(0, 1);

            for (int i = 0; i < aa_limit; i++)
            {
                camera.getPrimaryRay(float(x) + dis(gen), float(y) + dis(gen), width, height, P, w);
                r = Ray(P, w);
                col = math::add(col, Colour(r, limit));
            }

            // const Point col = lightIn(P, w);

            // std::cout << col.x << " " << col.y << " " << col.z << std::endl;

            // R channel
            pixels[loc] = col.x / aa_limit;
            loc++;
            // G channel
            pixels[loc] = col.y / aa_limit;
            loc++;
            // B channel
            pixels[loc] = col.z / aa_limit;
            loc++;
        }
    }
    return pixels;
}

// checks for intersection between triangle and ray.
// P + tw is ray, and V[3] is triangle. Stores barycentric coordinates in b[],
// and stores the intersection distance in t. Otherwise returns false.
bool Scene::rayTriangleIntersect(const Point &P, const Vec w, const Point V[3], float b[3], float &t) const
{
    const float precision = 1e-6;

    // Edge vectors
    const Vec &edge1 = math::sub(V[1].direction(), V[0].direction());
    const Vec &edge2 = math::sub(V[2].direction(), V[0].direction());

    // Normal
    const Vec &n = math::crossProduct(edge1, edge2);

    const Vec &q = math::crossProduct(w, edge2);
    const float a = math::dotProduct(edge1, q); // this is prob the m

    // Return false if nearly parallel or backfacing, or close to precision limit
    if ((math::dotProduct(n, w) >= 0) || (abs(a) <= precision))
        return false;

    const Vec &s = math::scale(1 / a, math::sub(P, V[0]).direction());
    const Vec &r = math::crossProduct(s, edge1);

    b[0] = math::dotProduct(s, q); // Barycentric coordinates of V0
    b[1] = math::dotProduct(r, w); // Barycentric coordinates of V1
    b[2] = 1.0f - b[0] - b[1];     // Barycentric coordinates of V2

    // Intersection outside triangle
    if ((b[0] < 0.0f || b[1] < 0.0f || b[2] < 0.0f))
        return false;

    t = math::dotProduct(edge2, r);
    return (t >= 0.0f);
}

// Returns if the ray has intersected a triangle or not and stores the closest triangle
bool Scene::testAllTriangles(const Point P, const Vec w, prims::Triangle &tri, float &t) const
{
    float min = t = std::numeric_limits<float>::max();
    for (int i = 0; i < tlist.size(); i++)
    {
        const prims::Triangle temp = tlist.triangle(i);
        float b[3];
        rayTriangleIntersect(P, w, temp.m_vertex, b, t);
        if (t < min)
        {
            min = t;
            tri = temp;
        }
        return (min != std::numeric_limits<float>::max());
    }
}

// Takes in a light point Y and a test point X and checks if there are any triangles intersecting it
bool Scene::visible(const Point Y, const Point X) const
{
    Vec b = math::sub(Y, X).direction();
    Vec a = math::getUnitVec(b);
    // const Vec b = Vec(0.02, 0.02, 0.02);
    // const Vec w = math::add(a, b); // Add bump
    prims::Triangle tri;
    float t;
    if (findFirstIntersection(Y, a, tri, t))
    {
        return true;
    }
    return false;
}

// Returns the amount of light received if the ray intersects wtih a triangle. Otherwise returns 0.
Point Scene::lightIn(const Point P, const Vec wi) const
{
    // Intersection triangle
    prims::Triangle s;
    // Intersection distance
    float t;
    if (findFirstIntersection(P, wi, s, t))
    {
        Point intsec = math::add(P, math::point((math::scale(t, wi))));
        // std::cout << "found intersection at: " << intsec.x << intsec.y << intsec.z << std::endl;
        Point L;
        L = lightOut(s, -wi, intsec);
        return L;
    }
    return Point(0, 0, 0); // No intersection has been found
}

// Returns the amount of light that bounces from a surface (not using a surfel)
Point Scene::lightOut(prims::Triangle &sx, const Vec &wo, const Point &X) const
{
    // Local radiance, we'll implement that later
    Point L = sx.material.emittedRadiance(wo);
    // Position of the intersection point
    // The dot product(?) between the light source and the normal of the material (in world coordinates)
    const Vec &edge1 = math::sub(sx.m_vertex[1].direction(), sx.m_vertex[0].direction());
    const Vec &edge2 = math::sub(sx.m_vertex[2].direction(), sx.m_vertex[0].direction());
    const Vec &n = math::crossProduct(edge1, edge2);

    for (const prims::Light &light : lights)
    {
        const Point &Y = light.getPosition();

        if (visible(Y, X))
        {
            const Vec &wi = math::sub(Y, X).direction();
            const Point &bi = light.biradiance(X);
            const Point &f = sx.material.finiteScatteringDensity(wi, wo);
            L = L + math::scale(abs(math::dotProduct(n, wi)), bi * f);
        }
    }

    return L;
}

// Finds the first intersection of a triangle and stores the triangle in s, and returns true. Returns false if nothing is intersected by the ray.
bool Scene::findFirstIntersection(const Point &P, const Vec &w, prims::Triangle &s, float &t) const
{
    prims::Triangle tri;
    if (testAllTriangles(P, w, tri, t))
    {
        s = tri;
        return true;
    }
    else
        return false;
}

// This takes too long to add. Need a better way to add primitive shapes / organize triangles. Also things are clockwise for some reason
void Scene::debugAddCube()
{
    tlist.addTriangle(prims::Triangle(Point(2, 0, -20),
                                      Point(-1, 0, -20),
                                      Point(-1, 3, -20)));
    tlist.addTriangle(prims::Triangle(Point(2, 0, -20),
                                      Point(-1, 3, -20),
                                      Point(2, 3, -20)));
    tlist.addTriangle(prims::Triangle(Point(2, 0, -23),
                                      Point(2, 0, -20),
                                      Point(2, 3, -20)));
    tlist.addTriangle(prims::Triangle(Point(2, 0, -23),
                                      Point(2, 0, -20),
                                      Point(2, 3, -20)));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));
    // tlist.addTriangle(prims::Triangle(Point(),
    //                                   Point(),
    //                                   Point()));

    std::cout << tlist.size() << std::endl;
    ;
}

void Scene::newCamera(PinholeCamera p)
{
    camera = p;
}

void Scene::addLight(prims::Light p)
{
    lights.push_back(p);
}

bool Scene::removeObject(int i)
{
    if (i > spheres.size())
        return false;
    else
        spheres.erase(spheres.begin() + i);
}

bool Scene::removeLight(int i)
{
    if (i > lights.size())
        return false;
    else
        lights.erase(lights.begin() + i);
}

void Scene::deleteScene()
{
}

const std::vector<prims::Light> Scene::getLights() const
{
    return lights;
}

/*--------------- Sphere stuff ---------------*/

std::vector<prims::Sphere> Scene::getSpheres() const
{
    return spheres;
}

Point Scene::Colour(Ray r, int limit) const
{
    float t;
    Vec n;
    bool intersect_sphere = sphereIntersect(r.origin, r.direction, t, n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1);
    // prims::Triangle tri;
    // bool intersect_triangle = testAllTriangles(P, w, tri);

    if (intersect_sphere && limit > 0)
    {
        Point P = math::add(r.pointAtTime(t), math::point(math::scale(0.01, n)));
        Vec w;
        do
        {
            w = Vec(dis(gen), dis(gen), dis(gen));
        } while (math::length(w) >= 1.0);
        w = math::add(w, n);
        Point col = math::scale(0.5, Colour(Ray(P, w), limit - 1));
        return col;

        // Point x = Point(n.x + 1, n.y + 1, n.z + 1);
        // Point y = math::scale(128, x);
        // return y;
    }
    else
        return Point(128, 150, 200);
}

void Scene::addSphere(prims::Sphere o)
{
    spheres.push_back(o);
}

void Scene::addSphere(int r, int x, int y, int z)
{
    spheres.push_back(prims::Sphere(r, Point(100, 100, 100), Point(x, y, z)));
}

// Sphere intersection
bool Scene::sphereIntersect(Point P, Vec w, float &t, Vec &n) const
{
    bool hit = false;
    for (auto sphere : spheres)
    {

        float dist = std::numeric_limits<float>::max();
        Vec v = math::sub(P.direction(), sphere.location.direction());
        float a = math::dotProduct(w, w);
        float b = math::dotProduct(w, v);
        float c = (math::dotProduct(v, v) - (sphere.rad * sphere.rad));
        float discriminant = (b * b) - (a * c);
        if (discriminant > 0)
        {
            t = ((-sqrt(discriminant)) - b) / a;
            if (dist > t && t > 0.01)
            {
                hit = true;
                dist = (float)std::abs(math::dotProduct(v, v));
                n = math::getUnitVec(math::sub(math::add(P.direction(), (math::scale(t, w))), sphere.location.direction()));
            }
            t = (sqrt(discriminant) - b) / a;
            if (dist > t && t > 0.01)
            {
                hit = true;
                dist = (float)std::abs(math::dotProduct(v, v));
                n = math::getUnitVec(math::sub(math::add(P.direction(), (math::scale(t, w))), sphere.location.direction()));
            }
        }
    }
    return hit;
}
