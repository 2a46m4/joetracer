#ifndef _PDF_H
#define _PDF_H

#include "Vec.h"
class pdf {
 public:
  virtual ~pdf() {}
  virtual double value(const Vec& direction) const = 0;
  virtual Vec generate() const = 0;
};

#endif
