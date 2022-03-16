#ifndef _SCENE_H
#define _SCENE_H

#include "utils/Point.h"
#include "utils/Vec.h"
#include "utils/Object.h"
#include "utils/Camera.h"

#include <math.h>
#include <vector>
#include <utility>

using namespace utils;

class Scene
{

private:
    int height;
    int width;

    camera c;

public:
    Scene();

    Scene(int w, int h);

    void render();

    void addObject(Object o);

    void newCamera(Point p, Vec v, int fov);

    void addLight(Point p);

    // Removes based on the id of the Object
    // True if success
    bool removeObject(int i);

    bool removeLight(int i);

    void deleteScene();

    Point *trace(Vec ray, int depth);

    std::pair<double, Object> *intersectScene(Vec ray);

    double sphereIntersection(Object obj, Vec ray);

    Vec *surface();
    
    std::vector<Point> lights;
    std::vector<Object> objects;
};

#endif