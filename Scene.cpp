#include "Scene.h"
#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/Surfel.h"
#include "utils/math/VectorOps.h"

#include <math.h>
#include <vector>
#include <utility>
#include <memory>

#define PI 3.14159265358979323846264338327950288419716939937510582097

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
    PinholeCamera camera;
    char* pixels = new char[width * height * 3];

    int loc = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Point P;
            Vec w;

            camera.getPrimaryRay(float(x) + 0.5f, float(y) + 0.5f, width, height, P, w);

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

Point Scene::debugColour(Point P, Vec w) const
{
    // const std::shared_ptr<Surfel> &s = findFirstIntersection(P, w);

    bool intersect = debugIntersection(P, w);

    if (intersect)
        return Point::char_max();
    else
        return Point::zero();
}

bool Scene::debugIntersection(Point P, Vec w) const
{
    for(auto sphere : spheres) {
        
        Vec v = math::sub(P.direction(), sphere.location.direction());
        int a = math::dotProduct(w, v) * math::dotProduct(w, v);
        int b = math::dotProduct(w, w) * (math::dotProduct(v, v) - (sphere.rad * sphere.rad));
        if(a - b < 0) return false;
        else return true;
    }
    return false;
}

std::shared_ptr<Surfel> Scene::findFirstIntersection(Point P, Vec w) const
{
    return NULL;
}

void Scene::addSphere(Sphere o)
{
    spheres.push_back(o);
}

void Scene::debugAddSphere(int r, int x, int y, int z) {
    spheres.push_back(Sphere(r, Point(100, 100, 100), Point(x, y, z)));
}

void Scene::newCamera(PinholeCamera p)
{
    camera = p;
}

void Scene::addLight(Point p)
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

std::vector<Point> Scene::getLights() const
{
    return lights;
}

std::vector<Sphere> Scene::getSpheres() const
{
    return spheres;
}