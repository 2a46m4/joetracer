#ifndef _VECTOR_H
#define _VECTOR_H

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>
#include "Vec3.h"

typedef Eigen::Vector3f Vector3;
typedef Eigen::Vector4f Vector4;

Vec3 Vector3ToVec3(Vector3 v) {
  return Vec3(v(0), v(1), v(2));
}

Vector3 Vec3ToVector3(Vec3 v) {
  return Vector3(v.x, v.y, v.z);
}

#endif
