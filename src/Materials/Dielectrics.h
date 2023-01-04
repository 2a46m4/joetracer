#ifndef _DIELECTRIC_H
#define _DIELECTRIC_H

#include "../Functions.h"
#include "../Hittable.h"
#include "../Ray.h"
#include "../Vector.h"

class Dielectrics : public Materials {
public:
  Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

  virtual bool scatter(const Ray3 &ray, const hitRecord &rec,
                       scatterRecord &srec) const {
    srec.isSpecular = true;   
    srec.pdfptr = nullptr;
    srec.attenuation = Point3(1.0, 1.0, 1.0);
    float refractionRatio = rec.frontFacing ? (1.0 / refractIdx) : refractIdx;
    Vector3 inDirNormalized = ray.direction.normalized();
    float cosine =
      std::fmin((-inDirNormalized).dot(rec.normal), 1.0);
    float sine = sqrt(1.0 - cosine * cosine);

    // If there is total internal reflection || fresnel effect on glancing
    // edges
    Vector3 direction;
    if ((refractionRatio * sine > 1.0) ||
        randomgen::randomOne() < schlick(cosine, refractionRatio)) {
      direction = reflection(rec.normal, inDirNormalized);
    }
    else

      direction = refract(inDirNormalized, rec.normal, refractionRatio);

    srec.specularRay = Ray3(rec.p, direction);
    return true;
  }
  float refractIdx;
};

#endif
