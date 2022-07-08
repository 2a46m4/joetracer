#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../Point.h"

class Texture {
public:
  virtual Point value(double u, double v, const Point p) const = 0;
};

#endif
