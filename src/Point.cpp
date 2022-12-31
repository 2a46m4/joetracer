#include "Point.h"
#include "Vec3.h"
#include <cmath>

Point::Point() {
  x = 0;
  y = 0;
  z = 0;
}

Point::Point(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Point::Point(Point3 p) {
  this->x = p(0);
  this->y = p(1);
  this->z = p(2);
}

// Uses sqrt distance
double Point::dist(Point p) {
  double a = (x - p.x) * (x - p.x);
  double b = (y - p.y) * (y - p.y);
  double c = (z - p.z) * (z - p.z);

  return sqrt(a + b + c);
}

Point Point::one() { return Point(1, 1, 1); }

Point Point::zero() { return Point(0, 0, 0); }

Point Point::char_max() { return Point(255, 255, 255); }

Vec3 Point::direction() { return Vec3(x, y, z); }

const Vec3 Point::direction() const { return Vec3(x, y, z); }

Point Point::operator+(Point a) { return Point(x + a.x, y + a.y, z + a.z); }

Point Point::operator-(Point a) { return Point(x - a.x, y - a.y, z - a.z); }

Point Point::operator*(Point a) { return Point(x * a.x, y * a.y, z * a.z); }

Point Point::operator/(Point a) { return Point(x / a.x, y / a.y, z / a.z);}

const Point Point::operator*(const Point &a) const {
  return Point(x * a.x, y * a.y, z * a.z);
}

bool Point::operator==(const Point &a) const {
  return ((x == a.x) && (y == a.y) && (z == a.z));
}

float &Point::operator[](int idx) {
  if (idx == 1) {
    return x;
  } else if (idx == 2) {
    return y;
  } else {
    return z;
  }
}

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << "Point(" << point.x << ", " << point.y << ", " << point.z
      << ')'; // actual output done here

  return out;
}

Point Point3ToPoint(Point3 p) {
  return Point(p(0), p(1), p(2));
}
Point3 PointToPoint3(Point p) {
  return Point3(p.x, p.y, p.z);
}
