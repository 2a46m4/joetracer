#ifndef _TRANSLATE_H
#define _TRANSLATE_H

#include "Hittable.h"
#include "Vector.h"
#include <eigen3/Eigen/Dense>

// Translated instance of a hittable object.
class Translate : public Hittable {
public:
  Translate(Hittable *hittablePtr, const Vector3 &offset);

  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

  // virtual double pdfValue(const Point &origin, const Vec3 &vec) const override {
  //   return hittablePtr->pdfValue(origin, vec);
  // }

  // virtual Vec3 random(const Point &origin) const override {
  //   return hittablePtr->random(origin);
  // }

  Hittable *hittablePtr;
  Vector3 offset;
};

#endif
