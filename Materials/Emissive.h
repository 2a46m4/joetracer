#ifndef _EMISSIVE_H
#define _EMISSIVE_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec.h"

class Emissive : public Materials {
public:
  Emissive(const Point &a) : emit(new SolidColour(a)) {}
  Emissive(const Texture *a) : emit(a){};
  bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation,
               Ray &scattered, double& pdf) const {
    return false; // never scatters, duh
  }

  // unidirectional light 
  Point emitted(double u, double v, const Point &p, const hitRecord rec, const Ray ray) const override {
    if(dotProduct(rec.normal, ray.direction) >= 0) return Point(0, 0, 0);
    else
      return emit->value(u, v, p);
  }

  const Texture *emit;
};

#endif
