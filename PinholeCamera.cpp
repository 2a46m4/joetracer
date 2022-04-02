#include "PinholeCamera.h"
#include "utils/Ray.h"
#include "utils/VectorOps.h"

using namespace utils;

#define PI 3.14159265358979323846264338327950288419716939937510582097

PinholeCamera::PinholeCamera()
{
}

PinholeCamera::PinholeCamera(float z_near, float verticalFOV, Point location, Vec direction)
{
    this->z_near = z_near;
    this->verticalFOV = verticalFOV;
    this->location = location;
    this->direction = math::getUnitVec(direction);
}

void PinholeCamera::getPrimaryRay(float x, float y, int width, int height, Ray &r) const
{
    // the scaling that depends on the fov of the camera; greater values means that the rays are projected farther away from the centre of the screen
    const float side = -2 * tan(verticalFOV * PI / 360.0f);

    Vec u, v, w;

    Vec vUp = Vec(0, -1, 0);

    w = direction;
    u = math::getUnitVec(math::crossProduct(vUp, w));
    v = math::crossProduct(u, w);

    // distance from the centre of projection * distance from the centre of the virtual plane * projection scaling
    r.origin = Point((z_near * (x / width - 0.5f) * side * width / height),
                     (z_near * -(y / height - 0.5f) * side),
                     (z_near));

    r.origin = math::sub(r.origin, math::point(math::scale(side, u)));
    r.origin = math::sub(r.origin, math::point(math::scale(side, v)));
    r.origin = math::sub(r.origin, math::point(-w));

    // TODO: implement camera rotation
    r.direction = math::sub(r.origin.direction(), location.direction());
}

void PinholeCamera::changeLocation(Point p)
{
    location = p;
}