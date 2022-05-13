#include "Sphere.h"
#include "../utils/Point.h"
#include <cmath>
#include "../utils/Functions.h"
#include "../utils/aabb.h"

#include <limits>

using namespace utils;
using namespace math;
namespace prims
{

    Sphere::Sphere()
    {
        rad = 5;
        location = Point(0, 0, -5);
    }

    Sphere::Sphere(float rad, Point col, Point loc, Materials *material)
    {
        this->rad = rad;
        location = loc;
        color = col;
        this->material = material;
    }

    bool Sphere::boundingBox(double t0, double t1, aabb &outputBox) const
    {
        outputBox = aabb(
            sub(location, Point(rad, rad, rad)),
            add(location, Point(rad, rad, rad)));
        return true;
    }

    bool Sphere::hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const
    {
        bool intercept = false;
        Vec v = sub(r.origin.direction(), location.direction());
        float a = dotProduct(r.direction, r.direction);
        float b = dotProduct(r.direction, v);
        float c = dotProduct(v, v) - (rad * rad);
        float discriminant = (b * b) - (a * c);
        if (discriminant > 0)
        {
            rec.t = ((-sqrt(discriminant)) - b) / a;
            if (tMax > rec.t && rec.t > 0.0001)
            {
                intercept = true;
                tMax = rec.t;
                rec.normal = unitVec(sub(add(r.origin.direction(), scale(rec.t, r.direction)), location.direction()));
                rec.p = add(r.origin, point(scale(rec.t, r.direction)));
                rec.matPtr = material;
            }
            rec.t = (sqrt(discriminant) - b) / a;
            if (tMax > rec.t && rec.t > 0.0001)
            {
                intercept = true;
                tMax = rec.t;
                rec.normal = unitVec(sub(add(r.origin.direction(), scale(rec.t, r.direction)), location.direction()));
                rec.p = add(r.origin, point(scale(rec.t, r.direction)));
                rec.matPtr = material;
            }
        }
        return intercept;
    }
}