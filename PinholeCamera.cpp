#include "PinholeCamera.h"
#include "utils/Point.h"

using namespace utils;

PinholeCamera::PinholeCamera() {}

PinholeCamera::PinholeCamera(float z_near, float verticalFOV, Point location)
{
    this->z_near = z_near;
    this->verticalFOV = verticalFOV;
    this->location = location;
}

void PinholeCamera::getPrimaryRay(float x, float y, int width, int height, Point &P, Vec &w) const
{
    // the scaling that depends on the fov of the camera; greater values means that the rays are projected farther away from the centre of the screen
    const float side = -2.0f * tan(verticalFOV / 2.0f);

    // distance from the centre of projection * distance from the centre of the virtual plane * projection scaling
    P = Point(z_near * (x / width - 0.5f) * side * width / height,
              z_near * -(y / height - 0.5f) * side,
              z_near);
    
    w = P.direction();
}