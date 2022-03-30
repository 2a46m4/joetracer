#include "Scene.h"
#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/Surfel.h"
#include "utils/VectorOps.h"
#include "utils/Light.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
#include <memory>
#include <limits>

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

char *Scene::render() const
{
    PinholeCamera *camera = new PinholeCamera(1.0f, 45.0f, Point(0, 0, 0));
    char *pixels = new char[width * height * 3];

    int loc = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Point P;
            Vec w;

            camera->getPrimaryRay(float(x) + 0.5f, float(y) + 0.5f, width, height, P, w);

            Point col = debugColour(P, w);

            // R channel
            pixels[loc++] = col.x;
            // G channel
            pixels[loc++] = col.y;
            // B channel
            pixels[loc++] = col.z;
        }
    }
    return pixels;
}

// checks for intersection between triangle and ray.
// P + tw is ray, and V[3] is triangle. Stores barycentric coordinates in b[],
// and stores the intersection distance in t. Otherwise returns false.
bool Scene::rayTriangleIntersect(const Point& P, const Vec w, const Point V[3], float b[3], float& t) {
    const float precision = 1e-6;

    // Edge vectors
    const Vec& edge1 = math::sub(V[1].direction(), V[0].direction());
    const Vec& edge2 = math::sub(V[2].direction(), V[0].direction());

    // Normal
    const Vec& n = math::crossProduct(edge1, edge2);

    const Vec& q = math::crossProduct(w, edge2);
    const float a = math::dotProduct(edge1, q); // this is prob the m 

    // Return false if nearly parallel or backfacing, or close to precision limit
    if ((math::dotProduct(n, w) >= 0) || (abs(a) <= precision)) return false;

    const Vec& s = math::scale(1/a, math::sub(P, V[0]).direction());
    const Vec& r = math::crossProduct(s, edge1);

    b[0] = math::dotProduct(s, q); // Barycentric coordinates of V0
    b[1] = math::dotProduct(r, w); // Barycentric coordinates of V1
    b[2] = 1.0f - b[0] - b[1];     // Barycentric coordinates of V2

    // Intersection outside triangle
    if ((b[0] < 0.0f || b[1] < 0.0f || b[2] < 0.0f)) return false;

    t = math::dotProduct(edge2, r);
    return (t >= 0.0f);
}

// Returns if the ray has intersected a triangle or not and stores the closest triangle
bool Scene::testAllTriangles(const Point P, const Vec w, prims::Triangle& tri) {
    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < tlist.size(); i++) {
        const prims::Triangle temp = tlist.triangle(i);
        float b[3];
        float t = min;
        rayTriangleIntersect(P, w, temp.m_vertex, b, t);
        if(t < min) {
            min = t;
            tri = temp;
        }
        return (min != std::numeric_limits<float>::max());
    }
}

Point Scene::debugColour(Point P, Vec w) const
{

    bool intersect_sphere = debugIntersection(P, w);
    bool intersect_triangle;

    if (intersect_sphere || intersect_triangle)
        return Point::char_max();
    else
        return Point::zero();
}

Point Scene::lightIn(const Point P, const Vec wi)
{

    const std::shared_ptr<Surfel> &s = findFirstIntersection(P, wi);

    if (s != nullptr)
    {
        return lightOut(s, -wi);
    }
}

Point Scene::lightOut(const std::shared_ptr<Surfel> &sx, const Vec &wo) {
    // Local radiance
    Point L = sx->emittedRadiance(wo); 
    const Point& X = sx->position;
    const Vec& n = sx->shadingNormal;

    bool visible = true; // Just set true for now

    for(prims::Light& light : lights) {
        Point& Y = light.position;

        if(visible) {
            const Vec& wi = (Y - X).direction();
            const Point& bi = light.biradiance(X);
            const Point& f = sx->finiteScatteringDensity(wi, wo);
            L = L + bi * f; 
        }
    }

    return L;
}

Point Scene::lightScatteredDirect(const std::shared_ptr<Surfel> &sx, const Vec &wo) {

}

bool Scene::debugIntersection(Point P, Vec w) const
{
    for (auto sphere : spheres)
    {

        Vec v = math::sub(P.direction(), sphere.location.direction());
        int a = math::dotProduct(w, v) * math::dotProduct(w, v);
        int b = math::dotProduct(w, w) * (math::dotProduct(v, v) - (sphere.rad * sphere.rad));
        if (a - b > 0)
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Surfel> Scene::findFirstIntersection(Point P, Vec w) const
{
    return NULL;
}

void Scene::addSphere(prims::Sphere o)
{
    spheres.push_back(o);
}

void Scene::debugAddSphere(int r, int x, int y, int z)
{
    spheres.push_back(prims::Sphere(r, Point(100, 100, 100), Point(x, y, z)));
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

std::vector<prims::Sphere> Scene::getSpheres() const
{
    return spheres;
}