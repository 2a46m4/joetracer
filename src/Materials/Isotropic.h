#ifndef _ISOTROPIC_H
#define _ISOTROPIC_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec3.h"

// Scatters a randomrayinsphere
class Isotropic : public Materials {
public:
  Isotropic(Point c) : albedo(new SolidColour(c)) {}
  Isotropic(Texture *t) : albedo(t) {}
  Texture *albedo;

  virtual bool scatter(const Ray &ray, const hitRecord &rec, scatterRecord& srec) const override {
    srec.specularRay = Ray(rec.p, randomRayInSphere(rec.normal));
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
  }
};

#endif
