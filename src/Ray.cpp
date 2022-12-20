#include "Ray.h"
#include "Functions.h"
#include "Point.h"
#include "Vec3.h"
#include <cmath>
#include <iostream>

Ray::Ray() {
  origin = Point();
  direction = Vec3();
}

Ray::Ray(Point &origin, Vec3 &direction) {
  this->origin = origin;
  this->direction = direction;
}

Ray::Ray(const Point &origin, const Vec3 &direction) {
  this->origin = origin;
  this->direction = direction;
}

Point Ray::pointAtTime(float t) const {
  return add(point(scale(t, direction)), origin);
}

std::ostream &operator<<(std::ostream &out, const Ray &point) {
  std::cout << "Ray("
            << "Point(" << point.origin.x << ", " << point.origin.y << ", "
            << point.origin.z << "), Vec3(" << point.direction.x << ", "
            << point.direction.y << ", " << point.direction.z
            << ")"; // actual output done here

  return out;
}
