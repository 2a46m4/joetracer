#ifndef _PINHOLE_CAMERA_H
#define _PINHOLE_CAMERA_H
#include "./Ray.h"
#include <cmath>

class PinholeCamera
{
protected:
    // Distance of the virtual plane to the centre of projection
    float height, width;

    float verticalFOV;

    Point location;

    // the out axis
    Point view;

    Vec vUp, u, v, w;

    float theta, h;

    Vec horizontal, vertical, lowerLeftCorner;

    float viewportHeight, viewportWidth;

public:
    PinholeCamera();

    PinholeCamera(int width, int height, float verticalFOV, Point location, Point view);

    /*
    x, y are the virtual coordinates on the virtual plane camera (our "sensor")
    width and height are the real size on the virtual plane
    P is the actual point of the ray
    w is the direction of the ray
     */
    void getPrimaryRay(float x, float y, Ray& r) const;

    void changeLocation(Point p);

    void changeView(Point p);
};

#endif
