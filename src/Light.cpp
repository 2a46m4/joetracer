#include "Light.h"
#include "./Functions.h"
#include "./Point.h"
#include "Const.h"

Light::Light(Point3 loc, float pow, Point3 col) {
  position = loc;
  power = pow;
  colour = col;
}

// The biradiance of the light at a given point
Point3 Light::biradiance(Point3 X) {
  Vector3 v = position - X;
  float dist = v.norm();
  float birad = this->power / (4 * PI * dist * dist);
  Point3 p = Point3(birad * this->colour.x(), birad * this->colour.y(),
		    birad * this->colour.z());
  return p;
}

// The biradiance of the light at a given point
const Point3 Light::biradiance(const Point3 X) const {
  Vector3 v = this->position - X;
  float dist = v.norm();
  float birad = this->power / (4 * PI * dist * dist);
  Point3 p = Point3(birad * this->colour.x(), birad * this->colour.y(),
		    birad * this->colour.z());
  return p;
}

Point3 &Light::getPosition() { return this->position; }

const Point3 &Light::getPosition() const { return this->position; }
