#ifndef _RAY_H
#define _RAY_H

#include "Point.h"
#include "Vec3.h"
#include <iostream>

class Ray {
public:
  Point origin;

  Vec3 direction;

  Ray();

  Ray(Point &origin, Vec3 &direction);

  Ray(const Point &origin, const Vec3 &direction);

  Point pointAtTime(float t) const;

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &point);
};

#endif
