#ifndef _COSINE_PDF
#define _COSINE_PDF

#include "../pdf.h"

#include "../Functions.h"
// The scattering pdf that has the distribution of a cosine wave. Most commonly used for lambertian reflectance
class CosinePDF : public pdf {
 public:
  CosinePDF(const Vec& n) {
    normal = n;
  }

  // Returns zero if the ray is absorbed, otherwise returns the cosine scattering pdf 
  virtual double value(const Vec& direction) const override {
    float cosine = dotProduct(unitVec(direction), normal);
    return cosine / PI;
  }

  // Generates a random cosine ray based on the normal angle.
  virtual Vec generate() const override {
    Vec scatterDirection = add(normal, randomRayInUnitVector());
    if (isDegenerate(scatterDirection))
      scatterDirection = normal;
    Vec scattered = unitVec(scatterDirection);
    return scattered;
    }
  
  Vec normal;
};

#endif