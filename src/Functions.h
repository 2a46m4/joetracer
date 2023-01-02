#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Const.h"
#include "Point.h"
#include "Vec3.h"
#include <cmath>
#include <math.h>
#include <random>
#include <sys/types.h>
#include "RandomGenerator.h"

template <class T, class U> const T sub(const T &a, const U &b) {
  return T(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <class T, class U> T sub(T &a, U &b) {
  return T(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <class T> T add3(T &a, T &b, T &c) {
  return T(a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z);
}

template <class T, class U> T add(const T &a, const U &b) {
  return T(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <class T, class U> T add(T &a, U &b) {
  return T(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <class T> const T scale(const double m, const T &a) {
  // std::cout << m << std::endl;	//
  return T(a.x * m, a.y * m, a.z * m);
}

template <class T> T scale(double m, T &a) {
  return T(a.x * m, a.y * m, a.z * m);
}

template <class T> T unitVec(T a){
    return scale((1 / length(a)), a);
}

// Returns the magnitude of the vector
inline double length(Vec3 &a) {
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

const double sqrlen(const Vec3 &a);

const inline double length(const Vec3 &a){
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double dotProduct(const Vec3 &a, const Vec3 &b);

template <class T, class U> T crossProduct(T &a, U &b) {
  return T((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z),
           (a.x * b.y) - (a.y * b.x));
}

Vector3 reflection(const Vector3& normal, const Vector3& incomingVector);

// Perfect reflection
// template <class T, class U> T reflection(T &normal, U &a) {
  // return sub(a, scale(2, scale(dotProduct(a, normal), normal)));
// }

Point vecToPoint(Vec3 &a);

Vec3 power(const Vec3 &a, int power);

Point point(const Vec3 &a);

float schlick(const float cosine, const float refractIdx);

Vec3 randomRayInSphere(const Vec3 &n);

Vec3 randomRayInUnitVector();

Vec3 randomCosinePDFRay();

Vec3 randomSphereRay(float radius, float distanceSquared);

template <class T> bool isDegenerate(T v) {
  const double nearZero = 0.00000001;
  return (std::fabs(v.x) <= nearZero && std::fabs(v.y) <= nearZero &&
          std::fabs(v.z) <= nearZero);
}

Vector3 refract(const Vector3 &v, const Vector3 &n, float etaRatio);

Vec3 refract(const Vec3 &v, const Vec3 &n, float etaRatio);

double clamp(double val, double low, double high);

double degreesToRadians(double degrees);

template <class T> inline T findCentre(T min, T max) {
  return T((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
}

#endif
