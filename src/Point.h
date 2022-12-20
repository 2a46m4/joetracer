#ifndef _POINT_H
#define _POINT_H

#include "Vec3.h"
#include <iostream>

class Point {
public:
  float x, y, z;

  Point();

  Point(float x, float y, float z);

  // Returns distance between two points
  double dist(Point p);

  static Point one();

  static Point zero();

  static Point char_max();

  Vec3 direction();

  const Vec3 direction() const;

  Point operator+(Point a);

  Point operator-(Point a);

  Point operator*(Point a);

  Point operator/(Point a);
  
  float &operator[](int idx);

  const Point operator*(const Point &a) const;

  bool operator==(const Point &a) const;

  friend std::ostream &operator<<(std::ostream &out, const Point &point);
};

#endif
