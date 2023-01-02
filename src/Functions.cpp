#include "Functions.h"
#include "RandomGenerator.h"
#include <cmath>
#include <random>

// Schlick's approximation for the Fresnel factor between two media
float schlick(const float cosine, const float refractIdx) {
  float r0 = (1 - refractIdx) / (1 + refractIdx);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// Returns a randomly generated ray that has a PDF of Cos(x).
Vector3 randomCosinePDFRay() {
  double r1 = randomgen::randomOne();
  double r2 = randomgen::randomOne();
  double z = sqrt(1 - r2);

  double phi = 2 * PI * r1;
  double x = cos(phi) * sqrt(r2);
  double y = sin(phi) * sqrt(r2);
  // Range: -1 < x, y, z < 1
  return Vector3(x, y, z);
}

Vec3 randomSphereRay(float radius, float distanceSquared) {

  float r1 = randomgen::randomOne();
  float r2 = randomgen::randomOne();
  float z = 1 + r2 * (sqrt(1 - radius * radius / distanceSquared) - 1);

  float phi = 2 * PI * r1;
  float x = cos(phi) * sqrt(1 - z * z);
  float y = sin(phi) * sqrt(1 - z * z);
  return Vec3(x, y, z);
}

// Returns a random ray in the upper hemisphere
Vector3 randomRayInSphere(const Vector3 &n) {
  Vector3 w;
  do {
    w = Vector3(randomgen::randomNum(-1, 1), randomgen::randomNum(-1, 1),
             randomgen::randomNum(-1, 1));
  } while (w.norm() >= 1.0);
  if (w.dot(n) > 0.0) // in the same hemisphere as the normal
    return w;
  else
    return -w;
}

bool isDegenerate(Vector3 v) {
  const double nearZero = 0.00000001;
  return (std::fabs(v.x()) <= nearZero && std::fabs(v.y()) <= nearZero &&
          std::fabs(v.z()) <= nearZero);
}


// Returns a random ray in the unit sphere
Vector3 randomRayInUnitVector() {
  return Vector3(randomgen::randomNum(-1, 1), randomgen::randomNum(-1, 1),
                      randomgen::randomNum(-1, 1)).normalized();
}

Vector3 reflection(const Vector3& normal, const Vector3& incomingVector) {
  float bLength = incomingVector.dot(normal);
  return incomingVector - 2 * bLength * normal;
}

Vector3 refract(const Vector3 &incomingVector, const Vector3 &normal,
                float etaRatio) {
  double cosTheta = fmin((-incomingVector).dot(normal), 1.0);
  Vector3 rPerpen = etaRatio * (incomingVector + cosTheta * normal);
  Vector3 rParall = -sqrt(fabs(1.0 - rPerpen.dot(rPerpen))) * normal;
  return rParall + rPerpen;
}

double clamp(double val, double low, double high) {
  if (val > high)
    return high;
  if (val < low)
    return low;
  else
    return val;
}

double degreesToRadians(double degrees) { return degrees * PI / 180; }
