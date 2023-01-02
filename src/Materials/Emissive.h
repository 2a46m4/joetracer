#ifndef _EMISSIVE_H
#define _EMISSIVE_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec3.h"

class Emissive : public Materials {
public:
  Emissive(const Point &a) : emit(new SolidColour(a)) {}
  Emissive(const Texture *a) : emit(a){};
  bool scatter(const Ray &ray, const hitRecord &rec, scatterRecord& srec) const {
    return false; // never scatters, duh
  }

  // unidirectional light 
  Point3 emitted(double u, double v, const Point3 &p, const hitRecord rec, const Ray3 ray) const override {
    if(rec.frontFacing) return Point3(0, 0, 0);
    else
      return PointToPoint3(emit->value(u, v, p));
  }

  const Texture *emit;
};

#endif
