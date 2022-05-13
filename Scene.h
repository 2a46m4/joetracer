#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "prims/Sphere.h"
#include "PinholeCamera.h"
#include "utils/Functions.h"
#include "prims/Light.h"
#include "utils/Ray.h"
#include "prims/Hittable.h"
#include "prims/BVHNode.h"

#include <math.h>
#include <vector>
#include <utility>
#include <memory>

using namespace utils;

class Scene
{

private:
    int height;
    int width;

    std::vector<prims::Light> lights;
    // std::vector<prims::Sphere> spheres;
    prims::HittableList hittables;

    Point background;

    int samples = 10;
    int bounces = 4;

    char *pixels;

public:
    PinholeCamera camera;

    Scene();

    Scene(int w, int h, PinholeCamera camera, Point background);

    char *render() const;

    // Inserts a pointer to a hittable object into the list
    void addObject(prims::Hittable *o);

    void debugAddCube();

    void newCamera(PinholeCamera p);

    void addLight(prims::Light p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    const std::vector<prims::Light> getLights() const;

    void changeBackground(Point background);

    // Sphere stuff

    Point Colour(Ray r, int limit, prims::BVHNode& sceneBox) const;

    // // returns the t that the intersection happened, as well as the normal
    // bool sphereIntersect(Ray& rIn, prims::hitRecord& rec) const;

    // std::vector<prims::Sphere> getSpheres() const;

    prims::HittableList getObjects() const;

    void changeSamples(int a);

    void changeBounces(int a);
};

#endif