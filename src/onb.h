#ifndef _ONB_H
#define _ONB_H

#include "Functions.h"
#include "Vec3.h"

// An orthonormal basis built from a given W. That is, U, V, and W's dot products with each other are all zero.
class onb {
public:
  onb() {}

  inline Vector3 u() const { return axis0; }
  inline Vector3 v() const { return axis1; }
  inline Vector3 w() const { return axis2; }

  // Scaling 
  Vector3 local(double a, double b, double c) const {
    return a * u() + b * v() + c * w();
  }

  // 
  Vector3 local(const Vector3 &a) const {
    return local(a(0), a(1), a(2));
  }

  void buildFromW(Vector3);
  
  Vector3 axis0;
  Vector3 axis1;
  Vector3 axis2;
};

#endif
