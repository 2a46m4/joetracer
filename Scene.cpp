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

bool rayTriangleIntersect(const Point& P, const Vec w, const Point V[3], float b[3], float& t) {
    const float precision = 1e-6;

    const Vec& edge1 = math::sub(V[1].direction(), V[0].direction());
}

Point Scene::debugColour(Point P, Vec w) const
{

    bool intersect = debugIntersection(P, w);

    if (intersect)
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