#ifndef _VEC_OPS_H
#define _VEC_OPS_H

#include "Vec.h"
#include "Point.h"
#include <cmath>

using namespace utils;

namespace math
{

    template <class T>
    const T sub(const T &a, const T &b)
    {
        return T(a.x - b.x,
                 a.y - b.y,
                 a.z - b.z);
    }

    template <class T>
    T sub(T &a, T &b)
    {
        return const_cast<T>(sub(const_cast<T>(a), const_cast<T>(b)));
    }

    // Vec sub(const Vec &a, const Vec &b);

    Vec add3(Vec &a, Vec &b, Vec &c);

    Vec add(Vec &a, Vec &b);

    template <class T>
    const T scale(double m, T &a)
    {
        return T(a.x * m,
                 a.y * m,
                 a.z * m);
    }

    Vec getUnitVec(Vec &a);

    double length(Vec &a);

    double dotProduct(const Vec &a, const Vec &b);

    template <class T>
    Vec crossProduct(T &a, T &b)
    {
        return Vec((a.y * b.z) - (a.z * b.y),
                   (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x));
    }

    Vec reflection(double normal, Vec &a);

    Point vecToPoint(Vec &a);

    Vec power(const Vec &a, int power);
}

#endif