#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Object.h"
#include "PinholeCamera.h"

#include <math.h>
#include <vector>
#include <utility>

using namespace utils;

class Scene
{

private:
    int height;
    int width;

    std::vector<Point> lights;
    std::vector<Object> objects;
    PinholeCamera camera;

public:
    Scene();

    Scene(int w, int h);

    void render() const;

    void addObject(Object o);

    void newCamera(Point p, Vec v, int fov);

    void addLight(Point p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    std::vector<Point> getLights() const;

    Point *trace(Vec ray, int depth);

    std::pair<double, Object> *intersectScene(Vec ray);

    double sphereIntersection(Object obj, Vec ray);

    Vec *surface();
    
};

#endif