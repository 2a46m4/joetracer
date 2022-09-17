#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Const.h"
#include "Point.h"
#include "Vec.h"
#include <cmath>
#include <math.h>
#include <random>
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
inline double length(Vec &a) {
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

const double sqrlen(const Vec &a);

const inline double length(const Vec &a){
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

double dotProduct(const Vec &a, const Vec &b);

template <class T, class U> T crossProduct(T &a, U &b) {
  return T((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z),
           (a.x * b.y) - (a.y * b.x));
}

// Perfect reflection
template <class T, class U> T reflection(T &normal, U &a) {
  return sub(a, scale(2, scale(dotProduct(a, normal), normal)));
}

Point vecToPoint(Vec &a);

Vec power(const Vec &a, int power);

Point point(const Vec &a);

float schlick(const float cosine, const float refractIdx);

Vec randomRayInSphere(const Vec &n);

Vec randomRayInUnitVector();

Vec randomCosinePDFRay();

Vec randomSphereRay(float radius, float distanceSquared);

template <class T> bool isDegenerate(T v) {
  const double nearZero = 0.00000001;
  return (std::fabs(v.x) <= nearZero && std::fabs(v.y) <= nearZero &&
          std::fabs(v.z) <= nearZero);
}

Vec refract(const Vec &v, const Vec &n, float etaRatio);

double clamp(double val, double low, double high);

double degreesToRadians(double degrees);

template <class T> inline T findCentre(T min, T max) {
  return T((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
}

#endif
