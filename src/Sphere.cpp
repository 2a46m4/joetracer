#include "Sphere.h"
#include "./Point.h"
#include "./aabb.h"
#include "Functions.h"
#include "Hittable.h"
#include "Ray.h"
#include "onb.h"

#include <cmath>
#include <eigen3/Eigen/src/Core/DenseBase.h>
#include <iostream>
#include <limits>

Sphere::Sphere() {
  rad = 5;
  sphereLocation = Point3(0, 0, -5);
}

Sphere::Sphere(float rad, Point3 loc, Materials *material) {
  this->rad = rad;
  sphereLocation = loc;
  this->material = material;
}

bool Sphere::boundingBox(double t0, double t1, aabb &outputBox) const {
  outputBox = aabb(sphereLocation - Point3(rad, rad, rad),
                   sphereLocation + Point3(rad, rad, rad));
  return true;
}

bool Sphere::hit(const Ray3 &r, hitRecord &rec, double tMin,
                 double tMax) const {
  Vector3 positionVector = r.origin - sphereLocation;
  float a = r.direction.dot(r.direction);
  float b = positionVector.dot(r.direction);
  float c = positionVector.dot(positionVector) - (rad * rad);
  float discriminant = (b * b) - (a * c);
  
  if (discriminant < 0.0)
    return false;
  
  else {
    // More numerically stable quadratic equation
    float sqrtd = sqrt(discriminant);
    float q = (b > 0.0) ?
      -(b + sqrtd) :
      -(b - sqrtd);
    float root1 = q / a;
    float root2 = c / q;
    // Check if the first root is valid
    if (root1 < tMin || tMax < root1) {
      root1 = FLT_INF;
      if (root2 < tMin || tMax < root2)
	return false;
    }
    if (root2 < tMin || tMax < root2)
      root2 = FLT_INF;

    rec.t = std::fmin(root1, root2);
    tMax = rec.t;
    rec.p = r.positionAtTime(rec.t);
    Vector3 outwardNormal = (rec.p - sphereLocation).normalized();
    rec.setFaceNormal(r, outwardNormal);
    getUV(rec.normal, rec.u, rec.v);
    rec.matPtr = material;
    return true;
  }
}

void Sphere::getUV(const Vector3 &p, float &u, float &v) {

  // taken from raytracing book
  //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
  //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
  //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

  double theta = acos(-p[1]);
  double phi = atan2(-p[2], p[0]) + PI;

  u = phi / (2 * PI);
  v = theta / PI;
}

double Sphere::pdfValue(const Point3 &o, const Vector3 &v) const {

  hitRecord rec;

  // Ray didn't hit this object. PDF is zero
  if (!this->hit(Ray3(o, v), rec, 0.001, DBL_INF))
    return 0;
  float distanceSquared = (sphereLocation - o).dot(sphereLocation - o);
  float cosThetaMax = sqrt(1 - (rad * rad / distanceSquared));
  float solidAngle = 2 * PI * (1 - cosThetaMax);

  // the larger the solid angle, the
  // higher the probability of the ray hitting the object
  return 1.0 / solidAngle;
}

Vector3 Sphere::random(const Point3 &o) const {
  Vector3 difference = sphereLocation - o;
  float distanceSquared = difference.dot(difference);
  onb uvw;
  uvw.buildFromW(difference);
  return uvw.local(randomSphereRay(rad, distanceSquared));
}
