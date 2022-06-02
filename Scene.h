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

    unsigned char *pixels;

public:
    PinholeCamera camera;

    int samples = 1;
    int bounces = 4;
    Point background;

    Scene();

    Scene(int w, int h, PinholeCamera camera, Point background);

    unsigned char *render() const;

    // Inserts a pointer to a hittable object into the list
    void addObject(prims::Hittable *o);

    void debugAddCube();

    void newCamera(PinholeCamera p);

    void addLight(prims::Light p);

    // Removes based on the id of the Object
    // True if success
    void removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    const std::vector<prims::Light> getLights() const;

    // Sphere stuff

    Point Colour(Ray r, int limit, prims::BVHNode &sceneBox) const;

    std::vector<prims::Hittable*> getObjects() const;
};

#endif