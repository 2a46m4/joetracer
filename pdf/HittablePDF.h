#ifndef _HITTABLE_PDF_H
#define _HITTABLE_PDF_H

#include "../Hittable.h"
#include "../pdf.h"

class HittablePDF : public pdf {
public:
  HittablePDF(Hittable *p, const Point &origin) : ptr(p), o(origin) {}

  virtual double value(const Vec &direction) const override {
    return ptr->pdfValue(o, direction);
  }

  virtual Vec generate() const override { return ptr->random(o); }

  Point o;
  Hittable *ptr;
};

#endif
