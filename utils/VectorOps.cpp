#include "VectorOps.h"
#include "Vec.h"
#include "Point.h"
#include "math.h"

namespace utils
{

    Vec VectorOps::sub(Vec &a, Vec &b)
    {
        return Vec(a.x - b.x,
                   a.y - b.y,
                   a.z - b.z);
    }

    Vec VectorOps::add(Vec &a, Vec &b)
    {
        return Vec(a.x + b.x,
                   a.y + b.y,
                   a.z + b.z);
    }

    Vec VectorOps::add3(Vec &a, Vec &b, Vec &c)
    {
        return Vec(a.x + b.x + c.z,
                   a.y + b.y + c.z,
                   a.z + b.z + c.z);
    }

    Vec VectorOps::scale(double m, Vec &a)
    {
        return Vec(a.x * m,
                   a.y * m,
                   a.z * m);
    }

    Vec VectorOps::getUnitVec(Vec &a)
    {
        return scale((1 / length(a)), a);
    }

    double VectorOps::length(Vec &a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    double VectorOps::dotProduct(Vec &a, Vec &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    Vec VectorOps::crossProduct(Vec &a, Vec &b)
    {

        return Vec((a.y * b.z) - (a.z * b.y),
                   (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x));
    }

    Vec VectorOps::reflection(double normal, Vec &a) {

    }

    Point VectorOps::vecToPoint(Vec& a) {
        return Point(a.x, a.y, a.z);
    }

} // namespace utils
