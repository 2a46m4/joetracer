#include "Sphere.h"
#include "./Point.h"
#include "./aabb.h"
#include "Functions.h"
#include "Hittable.h"
#include "Ray.h"
#include "Vec3.h"
#include "onb.h"

#include <cmath>
#include <iostream>
#include <limits>

Sphere::Sphere() {
  rad = 5;
  location = Point3(0, 0, -5);
}

Sphere::Sphere(float rad, Point3 loc, Materials *material) {
  this->rad = rad;
  location = loc;
  this->material = material;
}

bool Sphere::boundingBox(double t0, double t1, aabb &outputBox) const {
  outputBox = aabb(location - Point3(rad, rad, rad),
                   location + Point3(rad, rad, rad));
  return true;
}

bool Sphere::hit(const Ray3 &r, hitRecord &rec, double tMin,
                 double tMax) const {
  bool intercept = false;
  Vector3 sphereVector = r.origin - location;
  float a = r.direction.dot(r.direction);
  float b = sphereVector.dot(r.direction);
  float c = sphereVector.dot(sphereVector) - (rad * rad);
  float discriminant = (b * b) - (a * c);
  float time = 0;
  if (discriminant < 0.0)
    return false;
  auto sqrtd = sqrt(discriminant);
  auto root = (-b - sqrtd) / a;
  if (root < tMin || tMax < root) {
    root = (-b + sqrtd) / a;
    if (root < tMin || tMax < root)
      return false;
  }

  rec.t = root;
  // tMax = rec.t;
  rec.p = r.positionAtTime(rec.t);
  Vector3 outwardNormal = ((rec.p - location) / rad).normalized();
  rec.setFaceNormal(r, outwardNormal);
  getUV(rec.normal, rec.u, rec.v);
  rec.matPtr = material;
  return true;
  
  // time = ((-sqrt(discriminant)) - b) / a;

  // if (tMax > time && time > 0.001) {
  //   intercept = true;
  //   rec.t = time;
  //   tMax = rec.t;
  //   rec.p = r.pointAtTime(rec.t);
  //   Vec3 outwardNormal =
  //       unitVec(scale(1.0 / rad, (rec.p - location)).direction());
  //   rec.setFaceNormal(r, outwardNormal);
  //   getUV(rec.normal, rec.u, rec.v);
  //   rec.matPtr = material;
  // }
  // time = (sqrt(discriminant) - b) / a;
  // if (tMax > time && time > 0.001) {
  //   intercept = true;
  //   rec.t = time;
  //   tMax = rec.t;
  //   rec.p = r.pointAtTime(rec.t);
  //   Vec3 outwardNormal =
  //       unitVec(scale(1.0 / rad, (rec.p - location)).direction());
  //   rec.setFaceNormal(r, outwardNormal);
  //   getUV(rec.normal, rec.u, rec.v);
  //   rec.matPtr = material;
  // }
  // return intercept;
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
  float distanceSquared = (location - o).dot(location - o);
  float cosThetaMax = sqrt(1 - (rad * rad / distanceSquared));
  float solidAngle = 2 * PI * (1 - cosThetaMax);

  // the larger the solid angle, the
  // higher the probability of the ray hitting the object
  return 1.0 / solidAngle;
}

Vector3 Sphere::random(const Point3 &o) const {
  Vector3 difference = location - o;
  float distanceSquared = difference.dot(difference);
  onb uvw;
  uvw.buildFromW(difference);
  return uvw.local(Vec3ToVector3(randomSphereRay(rad, distanceSquared)));
}
