#include "Translate.h"
#include "Functions.h"
#include "Ray.h"

Translate::Translate(Hittable *hittablePtr, const Vec &offset) {
  this->hittablePtr = hittablePtr;
  this->offset = offset;
}

bool Translate::hit(const Ray &r, hitRecord &rec, double tMin,
                    double tMax) const {
  Ray moved(sub(r.origin, offset), r.direction);
  if (!hittablePtr->hit(moved, rec, tMin, tMax))
    return false;
  else {
    rec.p = add(rec.p, offset);
    rec.normal = (dotProduct(rec.normal, moved.direction) > 0)
                     ? scale(-1, rec.normal)
                     : rec.normal;
    return true;
  }
}

bool Translate::boundingBox(double t0, double t1, aabb &outputBox) const {
  if (!hittablePtr->boundingBox(t0, t1, outputBox))
    return false;

  outputBox = aabb(add(outputBox.min, offset), add(outputBox.max, offset));
}
