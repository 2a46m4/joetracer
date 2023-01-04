#include "onb.h"
#include "Functions.h"
#include "Vector.h"
#include <cmath>

// Builds a orthonormal basis with n as the "w"
void onb::buildFromW(Vector3 n) {
  axis2 = n.normalized();
  Vector3 a = (std::fabs(w().x()) > 0.9) ? Vector3(0, 1, 0) : Vector3(1, 0, 0);
  axis1 = axis2.cross(a).normalized();
  axis0 = axis2.cross(axis1);
}
