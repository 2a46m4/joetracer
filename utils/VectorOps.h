#ifndef _VEC_OPS_H
#define _VEC_OPS_H

#include "Vec.h"
#include "Point.h"
#include <cmath>

using namespace utils;

namespace math
{
    Vec sub(const Vec &a, const Vec &b);

    Vec add3(Vec &a, Vec &b, Vec &c);

    Vec add(Vec &a, Vec &b);

    Vec scale(double m, Vec &a);

    Vec getUnitVec(Vec &a);

    double length(Vec &a);

    double dotProduct(const Vec &a, const Vec &b);

    Vec crossProduct(Vec &a, Vec &b);

    Vec reflection(double normal, Vec &a);

    Point vecToPoint(Vec &a);

    Vec power(const Vec &a, int power);
}

#endif