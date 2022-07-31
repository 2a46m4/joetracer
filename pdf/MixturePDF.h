#ifndef _MIXTURE_PDF_H
#define _MIXTURE_PDF_H

#include "../pdf.h"
#include "../RandomGenerator.h"

class MixturePDF : public pdf {
 public:
  MixturePDF(pdf* p0, pdf* p1) {
    pdf0 = p0;
    pdf1 = p1;
    
  }

  virtual double value(const Vec& direction) const override {
    return (mixNum * pdf0->value(direction)) + ((1 - mixNum) * pdf1->value(direction));
  }

  virtual Vec generate() const override {
    if(joetracer::randomOne() < mixNum)
      return pdf1->generate();
    else
      return pdf0->generate();
  }
  
  pdf* pdf0;
  pdf* pdf1;
  float mixNum = 0.5;
};

#endif
