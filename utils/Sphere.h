#ifndef _SPHERE_H
#define _SPHERE_H

#include "Point.h"
#include "Hittable.h"
#include "Materials.h"

using namespace utils;

namespace prims
{
    class Sphere: public Hittable 
    {
    public:
        Point location;
        Point color;
        int rad;

        utils::Materials* material;

        Sphere();

        Sphere(int rad, Point col, Point loc);

        bool hit(const Ray& r, float minTime, float maxTime, hitRecord& rec) const;

    private:

    };
}

#endif