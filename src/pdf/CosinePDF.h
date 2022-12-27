#ifndef _COSINE_PDF
#define _COSINE_PDF

#include "../pdf.h"

#include "../Functions.h"
// A cosine PDF. 
class CosinePDF : public pdf {
 public:
  CosinePDF(const Vec3& n) {
    normal = n;
  }

  // Returns zero if the ray is absorbed, otherwise returns the cosine scattering pdf 
  virtual double value(const Vec3& direction) const override {
    double cosine = dotProduct(unitVec(direction), normal);
    return cosine / PI;
  }

  // Generates a random cosine ray based on the normal angle.
  virtual Vec3 generate() const override {
    Vec3 scatterDirection = add(normal, randomRayInSphere(normal));
    if (isDegenerate(scatterDirection))
      scatterDirection = normal;
    return unitVec(scatterDirection);
    }
  
  Vec3 normal;
};

#endif
