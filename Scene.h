#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/VectorOps.h"
#include "utils/Light.h"
#include "utils/TriangleList.h"
#include "utils/Triangle.h"
#include "utils/Ray.h"

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
    std::vector<prims::Sphere> spheres;
    TriangleList tlist;
    PinholeCamera camera;

public:
    Scene();

    Scene(int w, int h);

    char *render(PinholeCamera camera) const;

    void addSphere(prims::Sphere o);

    void debugAddCube();

    void newCamera(PinholeCamera p);

    void addLight(prims::Light p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    const std::vector<prims::Light> getLights() const;

    // Sphere stuff

    Point Colour(Ray r, int limit) const;

    // returns the t that the intersection happened, as well as the normal
    bool sphereIntersect(Ray& rIn, prims::hitRecord& rec) const;

    void addSphere(int r, int x, int y, int z);

    std::vector<prims::Sphere> getSpheres() const;
};

#endif