#include "Light.h"
#include "./Functions.h"
#include "./Point.h"

#define PI 3.1415926535

Light::Light(Point loc, float pow, Point col) {
  position = loc;
  power = pow;
  colour = col;
}

// The biradiance of the light at a given point
Point Light::biradiance(Point X) {
  Vec3 v = sub(position, X).direction();
  float dist = length(v);
  float birad = this->power / (4 * PI * dist * dist);
  Point p = Point(birad * this->colour.x, birad * this->colour.y,
                  birad * this->colour.z);
  return p;
}

// The biradiance of the light at a given point
const Point Light::biradiance(const Point X) const {
  Vec3 v = sub(this->position, X).direction();
  float dist = length(v);
  float birad = this->power / (4 * PI * dist * dist);
  Point p = Point(birad * this->colour.x, birad * this->colour.y,
                  birad * this->colour.z);
  return p;
}

Point &Light::getPosition() { return this->position; }

const Point &Light::getPosition() const { return this->position; }
