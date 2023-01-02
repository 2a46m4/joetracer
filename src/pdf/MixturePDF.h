#ifndef _MIXTURE_PDF_H
#define _MIXTURE_PDF_H

#include "../pdf.h"
#include "../RandomGenerator.h"

// Mixes two different PDFs together.
class MixturePDF : public pdf {
 public:
  MixturePDF(pdf* p0, pdf* p1) {
    pdf0 = p0;
    pdf1 = p1;
  }

  virtual double value(const Vector3& direction) const override {
    return (mixNum * pdf0->value(direction)) + ((1 - mixNum) * pdf1->value(direction));
  }

  virtual Vector3 generate() const override {
    if(randomgen::randomOne() < mixNum)
      return pdf0->generate();
    else
      return pdf1->generate();
  }
  
  pdf* pdf0;
  pdf* pdf1;
  float mixNum = 0.5;
};

#endif
