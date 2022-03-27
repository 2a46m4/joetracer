#include "VectorOps.h"
#include "Vec.h"
#include "Point.h"
#include <math.h>

namespace math
{

    Vec sub(const Vec &a, const Vec &b)
    {
        return Vec(a.x - b.x,
                   a.y - b.y,
                   a.z - b.z);
    }

    Vec add(Vec &a, Vec &b)
    {
        return Vec(a.x + b.x,
                   a.y + b.y,
                   a.z + b.z);
    }

    Vec add3(Vec &a, Vec &b, Vec &c)
    {
        return Vec(a.x + b.x + c.z,
                   a.y + b.y + c.z,
                   a.z + b.z + c.z);
    }

    Vec scale(double m, Vec &a)
    {
        return Vec(a.x * m,
                   a.y * m,
                   a.z * m);
    }

    Vec getUnitVec(Vec &a)
    {
        return scale((1 / length(a)), a);
    }

    double length(Vec &a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    double dotProduct(const Vec &a, const Vec &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    Vec crossProduct(Vec &a, Vec &b)
    {

        return Vec((a.y * b.z) - (a.z * b.y),
                   (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x));
    }

    Vec reflection(double normal, Vec &a) {

    }

    Point vecToPoint(Vec& a) {
        return Point(a.x, a.y, a.z);
    }

    Vec power(const Vec&a, int power) {
        Vec b = a;
        while(--power) {
            b.x *= a.x;
            b.y *= a.y;
            b.z *= a.z;
        }
        return b;
    }

} // namespace utils
