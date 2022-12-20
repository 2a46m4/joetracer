#ifndef _LAMBERTIAN_H
#define _LAMBERTIAN_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec3.h"
#include "../pdf/CosinePDF.h"

#include <limits>
class Lambertian : public Materials {
public:
  Lambertian(const Point &a) : albedo(new SolidColour(a)) {}
  Lambertian(const Texture *a) : albedo(a){};
  virtual bool scatter(const Ray &ray, const hitRecord &rec, scatterRecord& srec) const override {
    // direction, follows a cosine distribution
    Vec3 scatterDirection = add(rec.normal, randomRayInUnitVector());
    if (isDegenerate(scatterDirection))
      scatterDirection = rec.normal;
    srec.specularRay = Ray(rec.p, unitVec(scatterDirection));
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    // pdf of a lambertian reflectance model (same as the scattering
    // reflectance) allowed to be negative to not throw divide by zero errors
    srec.pdfptr = new CosinePDF(rec.normal); // dotProduct(rec.normal, scattered.direction) / PI
    return true;
  }

  double scatteringPDF(const Ray &rIn, const hitRecord &rec,
                       const Ray &rOut) const override {
    double cosine = dotProduct(rec.normal, unitVec(rOut.direction));
    // absorb case where the cosine is negative
    // otherwise return scattering pdf of lambertian reflectance
    return cosine / PI;
  }

  const Texture *albedo;
};

#endif
