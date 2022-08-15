#ifndef _DIELECTRIC_H
#define _DIELECTRIC_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Vec.h"

class Dielectrics : public Materials {
public:
  Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

  virtual bool scatter(const Ray &ray, const hitRecord &rec,
                       scatterRecord &srec) const {
    srec.isSpecular = true;
    srec.pdfptr = nullptr;
    srec.attenuation = Point(1.0, 1.0, 1.0);
    float refractionRatio = rec.frontFacing ? (1.0 / refractIdx) : refractIdx;
    float cosine =
        std::fmin(dotProduct(-unitVec(ray.direction), rec.normal), 1.0);
    float sine = sqrt(1.0 - cosine * cosine);

    // If there is total internal reflection || fresnel effect on glancing
    // edges
    Vec direction;
    if ((refractionRatio * sine > 1.0) ||
        joetracer::randomOne() < schlick(cosine, refractionRatio)) {
      Vec inDir = unitVec(ray.direction);
      direction = reflection(rec.normal, inDir);
    }
    else
      direction = refract(ray.direction, rec.normal, refractionRatio);

    srec.specularRay = Ray(rec.p, direction);
    return true;
  }
  float refractIdx;
};

#endif
