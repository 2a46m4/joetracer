#ifndef _METAL_H
#define _METAL_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Vector.h"
#include <iostream>

class Metal : public Materials {
public:
  Metal(const Point3 &a, float f) : albedo(a) {
    if (f < 1)
      fuzz = f;
    else
      fuzz = 1;
  }
  
  virtual bool scatter(const Ray3 &ray, const hitRecord &rec,
                       scatterRecord &srec) const {
    const Vector3 reflected = reflection(rec.normal, ray.direction);
    srec.specularRay =
        Ray3(rec.p, reflected + (fuzz * randomRayInSphere(rec.normal)));
    srec.attenuation = albedo;
	srec.isSpecular = true;
	srec.pdfptr = 0;
	return (srec.specularRay.direction.dot(rec.normal) > 0);
  }

  Point3 albedo;
  float fuzz;
};

#endif
