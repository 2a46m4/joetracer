#ifndef _ONB_H
#define _ONB_H

#include "Functions.h"
#include "Vec3.h"

// An orthonormal basis built from a given W. That is, U, V, and W's dot products with each other are all zero.
class onb {
public:
  onb() {}

  inline Vec3 u() const { return axis0; }
  inline Vec3 v() const { return axis1; }
  inline Vec3 w() const { return axis2; }

  // Scaling 
  Vec3 local(double a, double b, double c) const {
    return add3(scale(a, u()), scale(b, v()), scale(c, w()));
  }

  // 
  Vec3 local(const Vec3 &a) const {
    return add3(scale(a.x, u()), scale(a.y, v()), scale(a.z, w()));
  }

  void buildFromW(Vec3);
  
  Vec3 axis0;
  Vec3 axis1;
  Vec3 axis2;
};

#endif
