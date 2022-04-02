#ifndef _SPHERE_H
#define _SPHERE_H

#include "Point.h"
#include "Hittable.h"

using namespace utils;

namespace prims
{
    class Sphere: public Hittable 
    {
    public:
        Point location;
        double specular = 0.2;
        double lambert = 0.7;
        double ambient = 0.1;
        Point color;
        int rad;

        Sphere();

        Sphere(int rad, Point col, Point loc);

        bool hit(const Ray& r, float minTime, float maxTime, hitRecord& rec) const;

    private:

    };
}

#endif