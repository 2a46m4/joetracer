#ifndef _COSINE_PDF
#define _COSINE_PDF

#include "../pdf.h"

#include "../Functions.h"
// A cosine PDF. 
class CosinePDF : public pdf {
 public:
  CosinePDF(const Vector3& n) {
    normal = n;
  }

  // Returns zero if the ray is absorbed, otherwise returns the cosine pdf 
  virtual double value(const Vector3& direction) const override {
    double cosine = direction.normalized().dot(normal);
    return cosine / PI;
  }

  // Generates a random cosine ray based on the normal angle.
  virtual Vector3 generate() const override {
    Vector3 scatterDirection = normal + randomRayInSphere(normal);
    if (isDegenerate(scatterDirection))
      scatterDirection = normal;
    return scatterDirection.normalized();
    }
  
  Vector3 normal;
};

#endif
