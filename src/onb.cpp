#include "onb.h"
#include "Functions.h"
#include <cmath>

// Builds a orthonormal basis with n as the "w"
void onb::buildFromW(Vec3 n) {
  axis2 = unitVec(n);
  Vec3 a = (std::fabs(w().x) > 0.9) ? Vec3(0, 1, 0) : Vec3(1, 0, 0);
  axis1 = unitVec(crossProduct(axis2, a));
  axis0 = crossProduct(axis2, axis1);
}
