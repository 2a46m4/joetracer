#ifndef _METAL_H
#define _METAL_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Vec.h"
#include <iostream>

class Metal : public Materials {
public:
  Metal(const Point &a, float f) : albedo(a) {
    if (f < 1)
      fuzz = f;
    else
      fuzz = 1;
  }
  
  virtual bool scatter(const Ray &ray, const hitRecord &rec,
                       scatterRecord &srec) const {
    const Vec reflected = reflection(rec.normal, ray.direction);
    srec.specularRay =
        Ray(rec.p, add(reflected, scale(fuzz, randomRayInSphere(rec.normal))));
    srec.attenuation = albedo;
	srec.isSpecular = true;
	srec.pdfptr = 0;
    return (dotProduct(srec.specularRay.direction, rec.normal) > 0);
  }

  Point albedo;
  float fuzz;
};

#endif
