#include "Sphere.h"
#include "Point.h"
#include <cmath>
#include "VectorOps.h"

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

    Sphere::Sphere(float rad, Point col, Point loc, Materials* material)
    {
        this->rad = rad;
        location = loc;
        color = col;
        this->material = material;
    }

    bool Sphere::hit(const Ray &r, hitRecord &rec) const
    {
        bool intercept = false;
        float dist = std::numeric_limits<float>::max();
        Vec v = sub(r.origin.direction(), location.direction());
        float a = dotProduct(r.direction, r.direction);
        float b = dotProduct(r.direction, v);
        float c = dotProduct(v, v) - (rad * rad);
        float discriminant = (b * b) - (a * c);
        if (discriminant > 0)
        {
            rec.t = ((-sqrt(discriminant)) - b) / a;
            if (dist > rec.t && rec.t > 0.001)
            {
                intercept = true;
                dist = rec.t;
                rec.normal = getUnitVec(sub(add(r.origin.direction(), scale(rec.t, r.direction)), location.direction()));
                rec.p = add(r.origin, point(scale(rec.t, r.direction)));
                rec.matPtr = material;
            }
            rec.t = (sqrt(discriminant) - b) / a;
            if (dist > rec.t && rec.t > 0.001)
            {
                intercept = true;
                dist = rec.t;
                rec.normal = getUnitVec(sub(add(r.origin.direction(), scale(rec.t, r.direction)), location.direction()));
                rec.p = add(r.origin, point(scale(rec.t, r.direction)));
                rec.matPtr = material;
            }
        }
        return intercept;
    }
}