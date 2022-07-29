#ifndef _COSINEONB_PDF
#define _COSINEONB_PDF

#include "../pdf.h"
#include "../onb.h"
// The scattering pdf that has the distribution of a cosine wave. Most commonly used for lambertian reflectance
class CosineONB_PDF : public pdf {
 public:
  CosineONB_PDF(const Vec& w) {uvw.buildFromW(w);}

  // Returns zero if the ray is absorbed, otherwise returns the cosine scattering pdf 
  virtual double value(const Vec& direction) const override {
    float cosine = dotProduct(unitVec(direction), uvw.w());
    return cosine / PI;
  }

  // Generates a random cosine ray based on the normal angle.
  virtual Vec generate() const override {
    return uvw.local(randomCosinePDFRay());
  }
  
  onb uvw;
};

#endif
