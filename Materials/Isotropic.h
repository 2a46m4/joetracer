#ifndef _ISOTROPIC_H
#define _ISOTROPIC_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec.h"

// Scatters a randomrayinsphere
class Isotropic : public Materials {
public:
  Isotropic(Point c) : albedo(new SolidColour(c)) {}
  Isotropic(Texture *t) : albedo(t) {}
  Texture *albedo;

  virtual bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation,
                       Ray &scattered) const override {
    scattered = Ray(rec.p, randomRayInSphere(rec.normal));
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
  }
};

#endif
