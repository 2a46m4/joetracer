#include "PinholeCamera.h"
#include "utils/Ray.h"

using namespace utils;

PinholeCamera::PinholeCamera() {}

PinholeCamera::PinholeCamera(float z_near, float verticalFOV, Point location)
{
    this->z_near = z_near;
    this->verticalFOV = verticalFOV;
    this->location = location;
}

void PinholeCamera::getPrimaryRay(float x, float y, int width, int height, Ray& r) const
{
    // the scaling that depends on the fov of the camera; greater values means that the rays are projected farther away from the centre of the screen
    const float side = -2.0f * tan(verticalFOV / 2.0f);

    // distance from the centre of projection * distance from the centre of the virtual plane * projection scaling
    r.origin = Point((z_near * (x / width - 0.5f) * side * width / height) + location.x,
              (z_near * -(y / height - 0.5f) * side) + location.y,
              z_near + location.z);
    
    // TODO: implement camera rotation
    r.direction = r.origin.direction();
}

void PinholeCamera::changeLocation(Point p){
    location = p;
}