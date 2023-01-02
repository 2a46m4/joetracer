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

Vector3 reflection(const Vector3& normal, const Vector3& incomingVector);

float schlick(const float cosine, const float refractIdx);

Vector3 randomRayInSphere(const Vector3 &n);

Vector3 randomRayInUnitVector();

Vector3 randomCosinePDFRay();

Vec3 randomSphereRay(float radius, float distanceSquared);

bool isDegenerate(Vector3 v);

Vector3 refract(const Vector3 &v, const Vector3 &n, float etaRatio);

double clamp(double val, double low, double high);

double degreesToRadians(double degrees);

template <class T> inline T findCentre(T min, T max) {
  return T((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
}

#endif
