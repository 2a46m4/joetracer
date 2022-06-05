#ifndef _SCENE_H
#define _SCENE_H

#include "./Point.h"
#include "./Vec.h"
#include "./Sphere.h"
#include "PinholeCamera.h"
#include "./Functions.h"
#include "./Light.h"
#include "./Ray.h"
#include "./Hittable.h"
#include "./BVHNode.h"

#include <math.h>
#include <vector>
#include <utility>
#include <memory>

class Scene
{

private:
    int height;
    int width;
		
    HittableList hittables;

    unsigned char *pixels;

public:
    PinholeCamera camera;

    int samples = 12;
    int bounces = 4;
    Point background;

    Scene();

    Scene(int w, int h, PinholeCamera camera, Point background);

    unsigned char *render() const;

    // Inserts a pointer to a hittable object into the list
    void addObject(Hittable *o);

    void debugAddCube();

    void newCamera(PinholeCamera p);

    // Removes based on the id of the Object
    // True if success
    void removeObject(int i);

    void deleteScene();

    // Sphere stuff

    Point Colour(Ray r, int limit, BVHNode &sceneBox) const;

    std::vector<Hittable*> getObjects() const;
};

#endif