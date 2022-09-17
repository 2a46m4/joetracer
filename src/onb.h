#ifndef _ONB_H
#define _ONB_H

#include "Functions.h"
#include "Vec.h"
class onb {
public:
  onb() {}

  inline Vec u() const { return axis0; }
  inline Vec v() const { return axis1; }
  inline Vec w() const { return axis2; }

  // Scaling 
  Vec local(double a, double b, double c) const {
    return add3(scale(a, u()), scale(b, v()), scale(c, w()));
  }

  Vec local(const Vec &a) const {
    return add3(scale(a.x, u()), scale(a.y, v()), scale(a.z, w()));
  }

  void buildFromW(Vec);
  
  Vec axis0;
  Vec axis1;
  Vec axis2;
};

#endif
