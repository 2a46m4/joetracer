#include "Vec3.h"
#include <cmath>

Vec3::Vec3() {
  x = 0;
  y = 0;
  z = 0;
}

Vec3::Vec3(const float dx, const float dy, const float dz) {
  this->x = dx;
  this->y = dy;
  this->z = dz;
}

Vec3 Vec3::operator-() const {
  Vec3 v;
  v.x = -x;
  v.y = -y;
  v.z = -z;
  return v;
}

std::ostream &operator<<(std::ostream &out, const Vec3 &point) {
  out << "Point(" << point.x << ", " << point.y << ", " << point.z
      << ')'; // actual output done here
  return out;
}

Vec4::Vec4() {
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}

Vec4::Vec4(const float dx, const float dy, const float dz, const float dw) {
  this->x = dx;
  this->y = dy;
  this->z = dz;
  this->w = dw;
}

Vec4 Vec4::operator-() const {
  Vec4 v;
  v.x = -x;
  v.y = -y;
  v.z = -z;
  v.w = -w;
  return v;
}

Vec4 Vec4::operator*(float f) const {
	return Vec4(f * this->x, f*this->y, f * this->z, f * this->w);
}

Vec4 Vec4::operator*(Vec4 v) const {
	return Vec4(v.x * this->x, v.y*this->y, v.z * this->z, v.w * this->w);
}

std::ostream &operator<<(std::ostream &out, const Vec4 &point) {
  out << "Point(" << point.x << ", " << point.y << ", " << point.z << ", "
      << point.w << ')'; // actual output done here
  return out;
}
