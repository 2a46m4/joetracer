#include "Sphere.h"
#include "Point.h"
#include <cmath>

using namespace utils;

namespace prims
{

    Sphere::Sphere()
    {
        rad = 5;
        location = Point(0, 0, -5);
    }

    Sphere::Sphere(int rad, Point col, Point loc)
    {
        this->rad = rad;
        location = loc;
        color = col;
    }

    bool Sphere::hit(const Ray &r, float minTime, float maxTime, hitRecord &rec) const {
        
    }
}