#include "PinholeCamera.h"
#include "./Functions.h"
#include "./Ray.h"
#include "Translate.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Geometry/AngleAxis.h>
#include <eigen3/Eigen/src/Geometry/Quaternion.h>
#include <eigen3/Eigen/src/Geometry/Transform.h>
#include <eigen3/Eigen/src/Geometry/Translation.h>

#include <fstream>
#include <iostream>

PinholeCamera::PinholeCamera() {}

PinholeCamera::PinholeCamera(int width, int height, Eigen::Vector3f location,
                             Eigen::Vector3f rotation, float verticalFOV) {
  Eigen::AngleAxisf xRotation(rotation[0], Eigen::Vector3f::UnitX());
  Eigen::AngleAxisf yRotation(rotation[1], Eigen::Vector3f::UnitY());
  Eigen::AngleAxisf zRotation(rotation[2], Eigen::Vector3f::UnitZ());
  Eigen::Quaternion<float> q = xRotation * yRotation * zRotation;
  
  Eigen::MatrixXf rotationMatrix = q.matrix();
  // rotationMatrix.conservativeResize(4, 4);
  // rotationMatrix.col(3).setZero();
  // rotationMatrix.row(3).setZero();
  // rotationMatrix(3, 3) = 1;

  

  // Eigen::Matrix4f translationMatrix {
  //   {1, 0, 0, location(0)},
  //   {0, 1, 0, location(1)},
  //   {0, 0, 1, location(2)},
  //   {0, 0, 0, 1}
  // };

  this->rotationTranslationMatrix = rotationMatrix;
  this->translationMatrix = location;
  this->width = width;
  this->height = height;
  this->viewportHeight = tan((verticalFOV * PI / 360.0f)/2);
  viewportWidth = viewportHeight * width / height; // magnitude of the width
}

// http://fastgraph.com/makegames/3drotation/

PinholeCamera::PinholeCamera(int width, int height, float verticalFOV,
                             Point location, Point view) {
  useMatrix = false;
  this->verticalFOV = verticalFOV;
  this->location = location;
  this->view = view;
  this->width = width;
  this->height = height;

  // Reference
  vUp = Vec3(0, 1, 0);

  // Get u, v, w
  w = unitVec(sub(location, view).direction());
  u = unitVec(crossProduct(vUp, w));
  v = crossProduct(w, u);

  theta = verticalFOV * PI / 360.0f;
  h = tan(theta / 2);       // dist from out vector to top of virtual plane
  viewportHeight = 2.0 * h; // magnitude of the height
  viewportWidth = viewportHeight * width / height; // magnitude of the width
  horizontal =
      scale(viewportWidth, u); // width scaled to the direction of the u vector
  vertical = scale(viewportHeight,
                   v); // height scaled to the direction of the v vector
  lowerLeftCorner =
      sub(location.direction(),
          add(w, add(scale(0.5, horizontal),
                     scale(0.5, vertical)))); // add focal distance (currently w
                                              // = 1 so focal distance is 1)
}

void PinholeCamera::getPrimaryRay(float x, float y, Ray &r) const {

  // the scaling that depends on the fov of the camera; greater values means
  // that the rays are projected farther away from the centre of the screen
  // const float side = -2 * tan(verticalFOV * PI / 360.0f);
    r.origin = Point(translationMatrix(0), translationMatrix(1), translationMatrix(2));
    Eigen::Vector3f a = {((2*((x + 0.5) / width) -1) * viewportWidth), (-2*((y + 0.5) /height)+ 1) * viewportHeight, -1};
    a = rotationTranslationMatrix * a;
    r.direction = Vec3(a(0), a(1), a(2));
}

void PinholeCamera::changeLocation(Point p) { location = p; }

void PinholeCamera::changeView(Point P) { view = P; }
