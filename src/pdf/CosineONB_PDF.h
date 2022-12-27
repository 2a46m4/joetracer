#ifndef _COSINEONB_PDF
#define _COSINEONB_PDF

#include "../onb.h"
#include "../pdf.h"
// The scattering pdf that has the distribution of a cosine wave.
class CosineONB_PDF : public pdf {
public:
  CosineONB_PDF(const Vec3 &w) { uvw.buildFromW(w); }

  // Returns zero if the ray is absorbed, otherwise returns the cosine
  // scattering pdf
  virtual double value(const Vec3 &direction) const override {
    float cosine = dotProduct(unitVec(direction), uvw.w());
    return (cosine < 0.0)? 0 : cosine / PI;
  }

  // Returns a ray generated from a cosine PDF using the ONB coordinates.
  virtual Vec3 generate() const override {
    return uvw.local(randomCosinePDFRay());
  }

  onb uvw;
};

#endif
