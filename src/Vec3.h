#ifndef _VEC3_H
#define _VEC3_H

#include <iostream>

class Vec3 {
public:
  float x, y, z;

  Vec3();

  Vec3(const float dx, const float dy, const float dz);

  Vec3 operator-() const;

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &point);
};

class Vec4 {
public:
  float x, y, z, w;
  
  Vec4();
  
  Vec4(const float dx, const float dy, const float dz, const float dw);

  Vec4 operator-() const;

  Vec4 operator*(float f) const;

  Vec4 operator*(Vec4 v) const;

  friend std::ostream &operator<<(std::ostream &out, const Vec4 &point);
};

#endif
