#ifndef _SPHERE_H
#define _SPHERE_H

#include "../utils/Point.h"
#include "Hittable.h"

using namespace utils;
namespace prims {
    class Sphere: public Hittable 
    {
    public:
        Point location;
        Point color;
        int rad;

        prims::Materials* material;

        Sphere();

        Sphere(float rad, Point col, Point loc, Materials* material);

        bool boundingBox(double t0, double t1, aabb& outputBox) const;

        bool hit(const Ray& r, hitRecord& rec, double tMin, double tMax) const override;

    private:

    };
}
#endif