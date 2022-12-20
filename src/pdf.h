#ifndef _PDF_H
#define _PDF_H

#include "Vec3.h"
class pdf {
 public:
  virtual ~pdf() {}
  virtual double value(const Vec3& direction) const = 0;
  virtual Vec3 generate() const = 0;
};

#endif
