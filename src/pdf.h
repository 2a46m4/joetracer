#ifndef _PDF_H
#define _PDF_H

#include "Vec3.h"
// Stores data about a probability density function.
class pdf {
 public:
  virtual ~pdf() {}
  
  // Generates the PDF value of the vector.
  virtual double value(const Vector3& direction) const = 0;
  
  // Returns a randomly generated vector based on the PDF.
  virtual Vector3 generate() const = 0;
};

#endif
