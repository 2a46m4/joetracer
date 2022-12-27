#ifndef _PDF_H
#define _PDF_H

#include "Vec3.h"
// the probability density function 
class pdf {
 public:
  virtual ~pdf() {}
  
  // Generates the PDF value of the vector.
  virtual double value(const Vec3& direction) const = 0;
  
  // Returns a randomly generated vector based on the PDF.
  virtual Vec3 generate() const = 0;
};

#endif
