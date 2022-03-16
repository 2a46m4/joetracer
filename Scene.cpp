#include "Scene.h"
#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Object.h"
#include "utils/Camera.h"

#include <math.h>
#include <vector>
#include <utility>

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

void Scene::render()
{
    Vec *uv = c.v.getUnitVec();
    Vec *vpRight = uv->crossProduct(0, 1, 0);
    Vec *vpUp = uv->crossProduct(*vpRight);

    double fov_rads = (PI * (c.fov / 2)) / 180;
    double whratio = height / width;

    // Rectangle expanding outwards of the camera - our fov
    // half* is the length from the border to the middle
    // cam* is the total length (inf when fov = 180)
    // pix* is the size of the "pixel" per real pixel
    double halfWidth = tan(fov_rads);
    double halfHeight = whratio * halfWidth;
    double camWidth = halfWidth * 2;
    double camHeight = halfHeight * 2;
    double pixWidth = camWidth / (width - 1);
    double pixHeight = camHeight / (width - 1);

    int idx;
    Point *col;
    std::vector<int> data;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Vec xvec = *vpRight;
            Vec yvec = *vpUp;
            xvec.scale(x * pixWidth - halfWidth);
            yvec.scale(y * pixHeight - halfHeight);

            // the direction of the pixel vector (cam vec skewed to x and y)
            Vec a = *uv;
            a.add(xvec, yvec);

            // Traces this particular ray with depth starting at 0
            col = trace(a, 0);
            data.push_back(col->x); // temp, stores colour into this array
        }
    }

    Object *o = new Object();
    addObject(*o);
}

void Scene::addObject(Object o)
{
}

void Scene::newCamera(Point p, Vec v, int fov)
{
}

void Scene::addLight(Point p)
{
}

bool Scene::removeObject(int i)
{
}

bool Scene::removeLight(int i)
{
}

void Scene::deleteScene()
{
}

std::vector<Point> getLights() {

}

// Traces the ray, stops when it hits depth
Point* Scene::trace(Vec ray, int depth)
{
    Point *col = new Point();

    // Too deep, just return white
    if (depth > 3)
        return col;

    // find closest intersection, returns the first object found and the distance to it 
    std::pair<double, Object>* distObj = intersectScene(ray);

    // Did not find anything, return white
    if (distObj->first == __DBL_MAX__) // Distance of the object is infinite
    {
        return col;
    }

    double dist = distObj->first;
    Object object = distObj->second;

    // Scales the ray to the length of the intersection
    ray.scale(dist);
    // direction of the camera
    Point camPosition = c.p;
    camPosition.addVector(ray);
    Point intersectionPoint = camPosition;

    return col;
}

// Return distance and object that a ray intersected, else return inf
std::pair<double, Object>* Scene::intersectScene(Vec ray)
{
    std::pair<double, Object>* closest = new std::pair<double, Object>();

    for (int i = 0; i < objects.size(); i++) {
        double dist = sphereIntersection(objects[i], ray);
        if (dist != -1 && dist < closest->first) {
            closest->first = dist;
            closest->second = objects[i];
        }
    }

    return closest; 
}

Vec* Scene::surface()
{

}

double Scene::sphereIntersection(Object obj, Vec ray) {
    Vec eyeToCentre = obj->loc
    return 1;
}