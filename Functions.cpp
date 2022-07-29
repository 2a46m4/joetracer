#include "Functions.h"
#include "RandomGenerator.h"
#include <cmath>
#include <random>

Vec unitVec(Vec a) {
  return scale((1 / length(a)), a);
}
const double sqrlen(const Vec &a) { return a.x * a.x + a.y * a.y + a.z * a.z; }

double dotProduct(const Vec &a, const Vec &b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Point vecToPoint(Vec &a) { return Point(a.x, a.y, a.z); }

Vec power(const Vec &a, int power) {
  Vec b;
  b.x = powf(a.x, power);
  b.y = powf(a.y, power);
  b.z = powf(a.z, power);
  return b;
}

Point point(const Vec &a) { return Point(a.x, a.y, a.z); }

// Schlick's approximation for the Fresnel factor between two media
float schlick(const float cosine, const float refractIdx) {
  float r0 = (1 - refractIdx) / (1 + refractIdx);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// I'm not totally sure how this works, but it returns a ray in the direction of
// Z with a PDF of cosine(theta). See Peter Shirley's book
Vec randomCosinePDFRay() {
  double r1 = joetracer::randomOne();
  double r2 = joetracer::randomOne();
  double z = sqrt(1 - r2);

  double phi = 2 * PI * r1;
  double x = cos(phi) * sqrt(r2);
  double y = sin(phi) * sqrt(r2);
  // Range: -1 < x, y, z < 1
  return Vec(x, y, z);
}

// Returns a random ray in the upper hemisphere
Vec randomRayInSphere(const Vec &n) {
  Vec w;
  do {
    w = Vec(joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1));
  } while (length(w) >= 1.0);
  if (dotProduct(w, n) > 0.0) // in the same hemisphere as the normal
    return w;
  else
    return -w;
}

// Returns a random ray in the unit sphere
Vec randomRayInUnitVector() {
  Vec w;
  do {
    w = Vec(joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1), joetracer::randomNum(-1, 1));
  } while (length(w) >= 1.0);
  return w;
}

// Returns true if there is refraction (and not reflection), and finds the
// direction of the ray.
Vec refract(const Vec &v, const Vec &n, float etaRatio) {
  double cosTheta = fmin(dotProduct(-v, n), 1.0);
  Vec rPerpen = scale(etaRatio, (add(v, scale(cosTheta, n))));
  Vec rParall =
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
