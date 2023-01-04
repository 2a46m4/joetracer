#ifndef _CONSTANT_MEDIUM_H
#define _CONSTANT_MEDIUM_H

#include "Hittable.h"
#include "Materials/Isotropic.h"
#include "Textures/Texture.h"

// A hittable object composed of a constant density medium. Light is able to
// pass through but scatters inside.
class ConstantMedium : public Hittable {
public:
  ConstantMedium(Hittable *hittablePtr, double d, Texture *texturePtr);

  ConstantMedium(Hittable *hittablePtr, double d, Point3 &col);

  bool hit(const Ray3 &r, hitRecord &rec, double tMin,
           double tMax) const override;

  bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

  double pdfValue(const Point3& o, const Vector3 &v) const override;

  Vector3 random(const Point3 &o) const override;

  // The fog
  Materials *phaseFunction;
  // The boundary between the medium and outside
  Hittable *boundary;
  double negativeInvertedDensity;
};

#endif
