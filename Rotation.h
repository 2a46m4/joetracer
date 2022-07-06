#ifndef _ROTATION_H
#define _ROTATION_H

#include "Hittable.h"
#include "Point.h"
#include "aabb.h"

class Rotation : public Hittable {
public:
  Rotation(Hittable *p, Point angle);

  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1, aabb &outputBox) const override;

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
