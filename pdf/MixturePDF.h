#ifndef _MIXTURE_PDF_H
#define _MIXTURE_PDF_H

#include "../pdf.h"
#include "../Functions.h"

class MixturePDF : public pdf {
 public:
  MixturePDF(pdf* p0, pdf* p1) {
    pdf0 = p0;
    pdf1 = p1;
  }

  virtual double value(const Vec& direction) const override {
    return 0.5 * pdf0->value(direction) + 0.5 * pdf1->value(direction);
  }

  virtual Vec generate() const override {
    if(randomNum(0.0, 1.0) < 0.5)
      return pdf0->generate();
    else
      return pdf1->generate();
  }
  
  pdf* pdf0;
  pdf* pdf1;
};

#endif
