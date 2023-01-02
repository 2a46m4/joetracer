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
    Vec3 vNormal = Vector3ToVec3(normal);
    Vec3 scatterDirection = add(vNormal, randomRayInSphere(vNormal));
    if (isDegenerate(scatterDirection))
      scatterDirection = vNormal;
    return Vec3ToVector3(unitVec(scatterDirection));
    }
  
  Vector3 normal;
};

#endif
