#include "Ray.h"
#include "Functions.h"
#include "Point.h"
#include "Vec3.h"
#include <cmath>
#include <iostream>

Point3 Ray3::positionAtTime(float t) const {
  return origin + (direction * t);
}
