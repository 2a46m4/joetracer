#ifndef _ROTATION_H
#define _ROTATION_H

#include "Hittable.h"
#include "aabb.h"
#include "Ray.h"

class Rotation : public Hittable {
public:
  Rotation(Hittable *p, Point3 angle);

  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

  virtual double pdfValue(const Point3 &origin, const Vector3 &vec) const override {
    return obj->pdfValue(origin, vec);
  }

  virtual Vector3 random(const Point3 &origin) const override {
    return obj->random(origin);
  }

  Hittable *obj;
  bool hasBox;
  aabb rotBox;

  double sinXTheta;
  double sinYTheta;
  double sinZTheta;

  double cosXTheta;
  double cosYTheta;
  double cosZTheta;
};

#endif
