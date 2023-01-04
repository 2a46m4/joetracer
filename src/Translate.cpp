#include "Translate.h"
#include "Functions.h"
#include "Ray.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>

Translate::Translate(Hittable *hittablePtr, const Vector3 &offset) {
  this->hittablePtr = hittablePtr;
  this->offset = offset;
}

bool Translate::hit(const Ray3 &r, hitRecord &rec, double tMin,
                    double tMax) const {
  Ray3 moved(r.origin - offset, r.direction);
  if (!hittablePtr->hit(moved, rec, tMin, tMax))
    return false;
  else {
    rec.p = rec.p + offset;
    rec.setFaceNormal(moved, rec.normal);
    return true;
  }
}

bool Translate::boundingBox(double t0, double t1, aabb &outputBox) const {
  if (!hittablePtr->boundingBox(t0, t1, outputBox))
    return false;

  outputBox = aabb(outputBox.min + offset, outputBox.max + offset);
  return true;
}
