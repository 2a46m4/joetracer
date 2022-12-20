#include "Functions.h"
#include "RandomGenerator.h"
#include <cmath>
#include <random>

const double sqrlen(const Vec3 &a) { return a.x * a.x + a.y * a.y + a.z * a.z; }

double dotProduct(const Vec3 &a, const Vec3 &b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Point vecToPoint(Vec3 &a) { return Point(a.x, a.y, a.z); }

Vec3 power(const Vec3 &a, int power) {
  Vec3 b;
  b.x = powf(a.x, power);
  b.y = powf(a.y, power);
  b.z = powf(a.z, power);
  return b;
}

Point point(const Vec3 &a) { return Point(a.x, a.y, a.z); }

// Schlick's approximation for the Fresnel factor between two media
float schlick(const float cosine, const float refractIdx) {
  float r0 = (1 - refractIdx) / (1 + refractIdx);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// I'm not totally sure how this works, but it returns a ray in the direction of
// Z with a PDF of cosine(theta). See Peter Shirley's book
Vec3 randomCosinePDFRay() {
  double r1 = joetracer::randomOne();
  double r2 = joetracer::randomOne();
  double z = sqrt(1 - r2);

  double phi = 2 * PI * r1;
  double x = cos(phi) * sqrt(r2);
  double y = sin(phi) * sqrt(r2);
  // Range: -1 < x, y, z < 1
  return Vec3(x, y, z);
}

Vec3 randomSphereRay(float radius, float distanceSquared) {
  
  float r1 = joetracer::randomOne();
  float r2 = joetracer::randomOne();
  float z = 1 + r2 * (sqrt(1 - radius * radius / distanceSquared) - 1);

  float phi = 2*PI*r1;
  float x = cos(phi) * sqrt(1 - z*z);
  float y = sin(phi) * sqrt(1 - z*z);
  return Vec3(x, y, z);
}

// Returns a random ray in the upper hemisphere
Vec3 randomRayInSphere(const Vec3 &n) {
  Vec3 w;
  do {
    w = Vec3(joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1));
  } while (length(w) >= 1.0);
  if (dotProduct(w, n) > 0.0) // in the same hemisphere as the normal
    return w;
  else
    return -w;
}

// Returns a random ray in the unit sphere
Vec3 randomRayInUnitVector() {
  return unitVec(Vec3(joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1))); 
}

// Returns true if there is refraction (and not reflection), and finds the
// direction of the ray.
Vec3 refract(const Vec3 &v, const Vec3 &n, float etaRatio) {
  double cosTheta = fmin(dotProduct(-v, n), 1.0);
  Vec3 rPerpen = scale(etaRatio, (add(v, scale(cosTheta, n))));
  Vec3 rParall =
      -(scale(sqrt(fabs(1.0 - (length(rPerpen) * length(rPerpen)))), n));
  return add(rParall, rPerpen);
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
