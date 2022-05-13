#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Vec.h"
#include "Point.h"
#include <cmath>
#include <random>

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
        return T(a.x - b.x,
                 a.y - b.y,
                 a.z - b.z);
    }

    Vec add3(Vec &a, Vec &b, Vec &c);

    template <class T>
    T add(const T &a, const T &b)
    {
        return T(a.x + b.x,
                 a.y + b.y,
                 a.z + b.z);
    }

    template <class T>
    T add(T &a, T &b)
    {
        return T(a.x + b.x,
                 a.y + b.y,
                 a.z + b.z);
    }

    template <class T>
    const T scale(const double m, const T &a)
    {
        return T(a.x * m,
                 a.y * m,
                 a.z * m);
    }

    template <class T>
    T scale(double m, T &a)
    {
        return T(a.x * m,
                 a.y * m,
                 a.z * m);
    }

    Vec unitVec(Vec &a);

    const Vec unitVec(const Vec &a);

    // Returns the magnitude of the vector
    double length(Vec &a);

    const double sqrlen(const Vec &a);

    const double length(const Vec &a);

    double dotProduct(const Vec &a, const Vec &b);

    template <class T>
    Vec crossProduct(T &a, T &b)
    {
        return Vec((a.y * b.z) - (a.z * b.y),
                   (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x));
    }

    // Perfect reflection
    template <class T>
    T reflection(T &normal, T &a)
    {
        return sub(a, scale(2, scale(dotProduct(a, normal), normal)));
    }

    Point vecToPoint(Vec &a);

    Vec power(const Vec &a, int power);

    Point point(const Vec &a);

    float schlick(const float cosine, const float refractIdx);

    Vec randomRayInSphere(const Vec& n);

    Vec refract(const Vec &v, const Vec &n, float etaRatio);

    // Returns a random number [min, max). For integers add 1 to the max.
    template <class T>
    inline T randomNum(T min, T max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> urd(min, max);
        return (T)(urd(gen));
    }
}

#endif