#ifndef _LAMBERTIAN_H
#define _LAMBERTIAN_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vector.h"
#include "../pdf/CosinePDF.h"

#include <limits>
class Lambertian : public Materials {
public:
  Lambertian(const Point3 &a) : albedo(new SolidColour(a)) {}
  Lambertian(const Texture *a) : albedo(a){};
  virtual bool scatter(const Ray3 &ray, const hitRecord &rec, scatterRecord& srec) const override {
    // direction, follows a cosine distribution
    Vector3 scatterDirection = rec.normal + randomRayInUnitVector();
    if (isDegenerate(scatterDirection))
      scatterDirection = rec.normal;
    srec.specularRay = Ray3(rec.p, scatterDirection.normalized());
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    // pdf of a lambertian reflectance model (same as the scattering
    // reflectance) allowed to be negative to not throw divide by zero errors
    srec.pdfptr = new CosinePDF(rec.normal); // dotProduct(rec.normal, scattered.direction) / PI
    return true;
  }

  double scatteringPDF(const Ray3 &rIn, const hitRecord &rec,
                       const Ray3 &rOut) const override {
    double cosine = rec.normal.dot(rOut.direction.normalized());
    // absorb case where the cosine is negative
    // otherwise return scattering pdf of lambertian reflectance
    // return cosine / PI;	   
    return (cosine > 0.0)? cosine / PI : 0;
  }

  const Texture *albedo;
};

#endif
