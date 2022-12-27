#include "ConstantMedium.h"
#include "Functions.h"
#include "Hittable.h"
#include "Point.h"
#include "RandomGenerator.h"
#include "Textures/Texture.h"
#include "aabb.h"

ConstantMedium::ConstantMedium(Hittable *hittablePtr, double d,
                               Texture *texturePtr) {
  boundary = hittablePtr;
  negativeInvertedDensity = -1 / d;
  phaseFunction = new Isotropic(texturePtr);
}

ConstantMedium::ConstantMedium(Hittable *hittablePtr, double d, Point &col) {
  boundary = hittablePtr;
  negativeInvertedDensity = -1 / d;
  phaseFunction = new Isotropic(col);
}

bool ConstantMedium::hit(const Ray &r, hitRecord &rec, double tMin,
                         double tMax) const {

  // The hit going in and out of the boundary
  hitRecord rec1, rec2;

  //
  if (!boundary->hit(r, rec1, DBL_NEG_INF, DBL_INF))
    return false;
  if (!boundary->hit(r, rec2, rec1.t + 0.0001, DBL_INF))
    return false;

  // The total time is stretched to match the time the ray has spent inside the
  // medium
  if (rec1.t < tMin)
    rec1.t = tMin;
  if (rec2.t > tMax)
    rec2.t = tMax;

  // Impossible or edge case
  if (rec1.t >= rec2.t)
    return false;

  // If the time is negative
  if (rec1.t < 0)
    rec1.t = 0;

  // Length of the ray
  const float rayLength = length(r.direction);
  // Distance that it travels inside the boundary
  const float distanceInsideBoundary = (rec2.t - rec1.t) * rayLength;
  // - 1/d * log(rand(0, 1))
  // Lower density means higher probability that the medium will pass straight
  // through
  const float hitDistance =
      negativeInvertedDensity * log(randomgen::randomOne());

  if (hitDistance > distanceInsideBoundary)
    return false;

  rec.t = rec1.t + hitDistance / rayLength;
  rec.p = r.pointAtTime(rec.t);

  rec.normal = Vec3(1, 0, 0); // arbitrary
  rec.matPtr = phaseFunction;

  return true;
}

bool ConstantMedium::boundingBox(double t0, double t1, aabb &outputBox) const {
  return boundary->boundingBox(t0, t1, outputBox);
}
