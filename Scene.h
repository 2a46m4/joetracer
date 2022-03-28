#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Sphere.h"
#include "PinholeCamera.h"
#include "utils/Surfel.h"
#include "utils/VectorOps.h"
#include "utils/Light.h"

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
    PinholeCamera camera;

public:
    Scene();

    Scene(int w, int h);

    char* render() const;

    Point debugColour(Point P, Vec w) const;

    bool debugIntersection(Point P, Vec w) const;

    Point lightIn(const Point P, const Vec wi);

    Point lightOut(const std::shared_ptr<Surfel>& sx, const Vec& wo);

    Point lightScatteredDirect(const std::shared_ptr<Surfel> &sx, const Vec &wo);

    std::shared_ptr<Surfel> findFirstIntersection(Point P, Vec w) const;

    void addSphere(prims::Sphere o);

    void debugAddSphere(int r, int x, int y, int z);

    void newCamera(PinholeCamera p);

    void addLight(prims::Light p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    const std::vector<prims::Light> getLights() const;

    std::vector<prims::Sphere> getSpheres() const;
    
};

#endif