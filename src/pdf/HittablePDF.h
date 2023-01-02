#ifndef _HITTABLE_PDF_H
#define _HITTABLE_PDF_H

#include "../Hittable.h"
#include "../pdf.h"

// Generates the importance of shit
class HittablePDF : public pdf {
public:
  HittablePDF(Hittable *p, const Point3 &origin) : ptr(p), o(origin) {}

  virtual double value(const Vector3 &direction) const override {
    return ptr->pdfValue(o, direction);
  }

  virtual Vector3 generate() const override { return ptr->random(o); }

  Point3 o;
  Hittable *ptr;
};

#endif
