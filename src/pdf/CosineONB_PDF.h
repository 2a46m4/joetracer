#ifndef _COSINEONB_PDF
#define _COSINEONB_PDF

#include "../onb.h"
#include "../pdf.h"
// A generator class for the .
class CosineONB_PDF : public pdf {
public:
  CosineONB_PDF(const Vec3 &w) { uvw.buildFromW(w); }

  // Returns the value of a ray inputted into a cosine PDF centered on the ONB coordinates. Returns zero if the ray is absorbed, i.e. the ray goes into the object.
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
