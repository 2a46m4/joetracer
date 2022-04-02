#ifndef _PINHOLE_CAMERA_H
#define _PINHOLE_CAMERA_H
#include "utils/Ray.h"
#include <cmath>

using namespace utils;

class PinholeCamera
{
protected:
    // Distance of the virtual plane to the centre of projection
    float z_near;

    float verticalFOV;

    Point location;

public:
    PinholeCamera();

    PinholeCamera(float z_near, float verticalFOV, Point location);

    /*
    x, y are the virtual coordinates on the virtual plane camera (our "sensor")
    width and height are the real size on the virtual plane
    P is the actual point of the ray
    w is the direction of the ray
     */
    void getPrimaryRay(float x, float y, int width, int height, Ray& r) const;

    void changeLocation(Point p);
};

#endif