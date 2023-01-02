#ifndef _RAY_H
#define _RAY_H

#include "Point.h"
#include "Vec3.h"
#include <iostream>

class Ray3 {
public:
  Point3 origin;
  Vector3 direction;

  Ray3() {
    origin = Point3();
    direction = Vector3();
  }
  
  Ray3(Point3 o, Vector3 d) : origin(o), direction(d) {};

  Point3 positionAtTime(float t) const;
  
  friend std::ostream& operator<<(std::ostream& os, const Ray3& r) {
    os << "Origin: " << r.origin << '\n';
    os << "Direction: " << r.direction << '\n';
    return os;
  }

};

class Ray {
public:
  Point origin;

  Vec3 direction;

  Ray();

  Ray(Point &origin, Vec3 &direction);

  Ray(const Point &origin, const Vec3 &direction);

  Point pointAtTime(float t) const;

  friend std::ostream &operator<<(std::ostream &out, const Ray &point) {
    out << "Ray Origin: " << point.origin << '\n';
    out << "Ray Direction: " << point.direction << '\n';
    return out;
  }

  Ray3 toRay3();

  static Ray getRay(Ray3 r);
};

#endif
