
#ifndef _LAMBERTIAN_ONB_H
#define _LAMBERTIAN_ONB_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"
#include "../Vec.h"
#include "../onb.h"

class Lambertian_ONB : public Materials {
public:
  Lambertian_ONB(const Point &a) : albedo(new SolidColour(a)) {}
  Lambertian_ONB(const Texture *a) : albedo(a){};
  virtual bool scatter(const Ray &ray, const hitRecord &rec, Point &alb,
                       Ray &scattered, double &pdf) const override {
    // direction, follows a cosine distribution
    // std::cout << rec.normal << std::endl;
    onb uvw;
    uvw.buildFromW(rec.normal);
    Vec rcpr = randomCosinePDFRay();
    // std::cout << uvw.u() << std::endl;
    // std::cout << uvw.v() << std::endl; //
    // std::cout << uvw.w() << std::endl; //
    // std::cout << rcpr << std::endl;
    Vec scatterDirection = uvw.local(rcpr);
    // std::cout << scatterDirection << std::endl;
    if (isDegenerate(scatterDirection))
      scatterDirection = rec.normal;
    scattered = Ray(rec.p, unitVec(scatterDirection));
    alb = albedo->value(rec.u, rec.v, rec.p);
    // std::cout << alb << std::endl; //
    // pdf of a lambertian reflectance model (same as the scattering
    // reflectance) allowed to be negative to not throw divide by zero errors
    // std::cout << scattered.direction << std::endl;
    pdf = dotProduct(uvw.w(), scattered.direction) / PI;
    // std::cout << pdf << std::endl;
    return true;
  }

  double scatteringPDF(const Ray &rIn, const hitRecord &rec,
                       const Ray &rOut) const override {
    double cosine = dotProduct(rec.normal, unitVec(rOut.direction));
    // absorb case where the cosine is negative
    // otherwise return scattering pdf of lambertian reflectance
    return cosine < 0 ? 0 : cosine / PI;
  }

  const Texture *albedo;
};

#endif
