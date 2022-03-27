#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/Surfel.h"
#include "utils/VectorOps.h"

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

    std::vector<Point> lights;
    std::vector<Sphere> spheres;
    PinholeCamera camera;

public:
    Scene();

    Scene(int w, int h);

    char* render() const;

    Point debugColour(Point P, Vec w) const;

    bool debugIntersection(Point P, Vec w) const;

    std::shared_ptr<Surfel> findFirstIntersection(Point P, Vec w) const;

    void addSphere(Sphere o);

    void debugAddSphere(int r, int x, int y, int z);

    void newCamera(PinholeCamera p);

    void addLight(Point p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    std::vector<Point> getLights() const;

    std::vector<Sphere> getSpheres() const;
    
};

#endif