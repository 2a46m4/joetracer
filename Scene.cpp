#include "Scene.h"
#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/VectorOps.h"
#include "utils/Light.h"
#include "utils/Ray.h"
#include "utils/Functions.h"

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
    char *pixels = new char[width * height * 3];
    int limit = 4;
    int loc = 0;
    int aa_limit = 1;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Ray r;
            Point col;

            std::random_device aa;  // Will be used to obtain a seed for the random number engine
            std::mt19937 gen(aa()); // Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<> asd(0, 1);

            for (int i = 0; i < aa_limit; i++)
            {
                camera.getPrimaryRay(float(x) + asd(aa), float(y) + asd(aa), width, height, r);
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
    prims::hitRecord rec;
    rec.t = std::numeric_limits<float>::max();

    // prims::Triangle tri;
    // bool intersect_triangle = testAllTriangles(P, w, tri);

    if (sphereIntersect(r, rec) && limit > 0)
    {
        Ray scattered;
        Point attenuation;
        rec.matPtr->scatter(r, rec, attenuation, scattered);
        return attenuation * Colour(scattered, limit - 1);
    }
    else
        return Point(150, 170, 240); // Background colour
}

void Scene::addSphere(prims::Sphere o)
{
    spheres.push_back(o);
}

// Sphere intersection
bool Scene::sphereIntersect(Ray &rIn, prims::hitRecord &rec) const
{
    bool hit = false;
    for (auto sphere : spheres)
    {
        prims::hitRecord temp;
        temp.t = std::numeric_limits<float>::max();
        bool hitsphere = sphere.hit(rIn, temp);
        if (hitsphere && temp.t < rec.t)
        {
            rec = temp;
        }
        hit = hit || hitsphere;
    }
    return hit;
}
