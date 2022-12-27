#include "Matrix.h"
#include "Vec3.h"
#include <cstring>
#include <math.h>

Matrix4::Matrix4() {}

// copies 16 floats from data and puts in our data structure
Matrix4::Matrix4(Vec4 columns[4]) {
  memcpy(&this->columns, columns, sizeof(Vec4) * 4);
}

Matrix4 Matrix4::translate(float dx, float dy, float dz) {
  Vec4 columns[4] = {Vec4(1, 0, 0, 0), Vec4(0, 1, 0, 0), Vec4(0, 0, 1, 0),
                     Vec4(dx, dy, dz, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::rotateX(float dx) {
  float c = cosf(dx);
  float s = sinf(dx);
  Vec4 columns[4] = {Vec4(1, 0, 0, 0), Vec4(0, c, s, 0), Vec4(0, -s, c, 0),
                     Vec4(0, 0, 0, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::rotateY(float dy) {
  float c = cosf(dy);
  float s = sinf(dy);
  Vec4 columns[4] = {Vec4(c, 0, s, 0), Vec4(0, 1, 0, 0), Vec4(-s, 0, c, 0),
                     Vec4(0, 0, 0, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::rotateZ(float dz) {
  float c = cosf(dz);
  float s = sinf(dz);
  Vec4 columns[4] = {Vec4(c, -s, 0, 0), Vec4(s, c, 0, 0), Vec4(0, 0, 1, 0),
                     Vec4(0, 0, 0, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::scale(float sx, float sy, float sz) {
  Vec4 columns[4] = {Vec4(sx, 0, 0, 0), Vec4(0, sy, 0, 0), Vec4(0, 0, sz, 0),
                     Vec4(0, 0, 0, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::identity() {
  Vec4 columns[4] = {Vec4(1, 0, 0, 0), Vec4(0, 1, 0, 0), Vec4(0, 0, 1, 0),
                     Vec4(0, 0, 0, 1)};
  return Matrix4(columns);
}

Matrix4 Matrix4::multiply(Matrix4 a, Matrix4 b) {
	
}

Matrix4 Matrix4::orthoProject(float left, float right, float bottom, float top,
                              float near, float far) {}

Matrix4 Matrix4::copyZToW(float factor) {
  
}

Matrix4 Matrix4::perspective(float fovRad, float aspectRatio, float near,
                             float far) {}

Matrix4 Matrix4::inverse(Matrix4 m) {}

Matrix4 Matrix4::lookAt(Vec3 cameraPosition, Vec3 target, Vec3 upVec) {}

Matrix4 Matrix4::transpose(Matrix4 m) {}

// Vec4 Matrix4::multiply(Vec4 vec4) {
// vec4.x = vec4.x * this->columns[0];
// mat4.data[];
// return vec4;
// }
