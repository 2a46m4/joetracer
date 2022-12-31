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

Ray3 Ray::toRay3() {
  return Ray3(PointToPoint3(this->origin), Vec3ToVector3(this->direction));
}

Ray Ray::getRay(Ray3 r) {
  return Ray(Point3ToPoint(r.origin), Vector3ToVec3(r.direction));
}
