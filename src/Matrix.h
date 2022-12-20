#ifndef _MATRIX_H
#define _MATRIX_H
#include "Vec3.h"

// 4x4 square matrix.
class Matrix4 {
public:
  Matrix4();

  Matrix4(Vec4 columns[4]);

  static Matrix4 translate(float dx, float dy, float dz);

  static Matrix4 rotateX(float pitch);
  static Matrix4 rotateY(float yaw);
  static Matrix4 rotateZ(float roll);

  static Matrix4 scale(float sx, float sy, float sz);

  static Matrix4 identity();

  static Matrix4 multiply(Matrix4 a, Matrix4 b);

  // returns an orthographic projection (maps 3 dimensional object to 2
  // dimensions)
  static Matrix4 orthoProject(float left, float right, float bottom, float top,
                              float near, float far);

  static Matrix4 copyZToW(float factor);

  static Matrix4 perspective(float fovRad, float aspectRatio, float near,
                             float far);

  static Matrix4 inverse(Matrix4 m);

  // transforms vector with matrix
  static Matrix4 transformFunction();

  static Matrix4 lookAt(Vec3 cameraPosition, Vec3 target, Vec3 upVec);

  static Matrix4 transpose(Matrix4 m);

  Vec4 multiply(Vec4 vec4);

  Vec4 getX();
  Vec4 getY();
  Vec4 getZ();

private:
  Vec4 columns[4];
};

#endif
