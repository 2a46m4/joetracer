#ifndef _VEC_H
#define _VEC_H

#include <iostream>

class Vec {
public:
  float x, y, z;

  Vec();

  Vec(const float dx, const float dy, const float dz);

  Vec operator-() const;

  friend std::ostream &operator<<(std::ostream &out, const Vec &point);
};

#endif
