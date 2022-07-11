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
  virtual bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation,
                       Ray &scattered, double& pdf) const {
    // std::cout << rec.normal.z << " " << ray.direction.x << " " <<
    // ray.direction.y << " " << ray.direction.z << std::endl;
    const Vec reflected = reflection(rec.normal, ray.direction);
    scattered =
        Ray(rec.p, add(reflected, scale(fuzz, randomRayInSphere(rec.normal))));
    attenuation = albedo;
    return (dotProduct(scattered.direction, rec.normal) > 0);
  }

  Point albedo;
  float fuzz;
};

#endif
