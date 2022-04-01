#include "VectorOps.h"
#include <cmath>

using namespace utils;

namespace math
{

    // Vec sub(const Vec &a, const Vec &b)
    // {
    //     return Vec(a.x + b.x,
    //                a.y + b.y,
    //                a.z + b.z);
    // }

    Vec add3(Vec &a, Vec &b, Vec &c)
    {
        return Vec(a.x + b.x + c.z,
                   a.y + b.y + c.z,
                   a.z + b.z + c.z);
    }

    Vec getUnitVec(Vec &a)
    {
        return scale((1 / length(a)), a);
    }

    const Vec getUnitVec(const Vec &a)
    {
        return scale((1 / length(a)), a);
    }

    const double length(const Vec &a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    double length(Vec &a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    double dotProduct(const Vec &a, const Vec &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    Vec reflection(double normal, Vec &a)
    {
        return Vec(0, 0, 0);
    }

    Point vecToPoint(Vec &a)
    {
        return Point(a.x, a.y, a.z);
    }

    Vec power(const Vec &a, int power)
    {
        Vec b = a;
        while (--power)
        {
            b.x *= a.x;
            b.y *= a.y;
            b.z *= a.z;
        }
        return b;
    }

    Point point(const Vec &a)
    {
        return Point(a.x, a.y, a.z);
    }
}
