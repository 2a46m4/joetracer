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
  Point emitted(double u, double v, const Point &p) const override {
    return emit->value(u, v, p);
  }

  const Texture *emit;
};

#endif
