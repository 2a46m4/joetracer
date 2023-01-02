#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../Point.h"

class Texture {
public:
  virtual Point3 value(double u, double v, const Point3 p) const = 0;
};

#endif
