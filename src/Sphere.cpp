#include "Sphere.h"
#include "./Point.h"
#include "./aabb.h"
#include "Functions.h"
#include "Hittable.h"
#include "Ray.h"
#include "onb.h"

#include <cmath>
#include <iostream>
#include <limits>

Sphere::Sphere() {
  rad = 5;
  location = Point(0, 0, -5);
}

Sphere::Sphere(float rad, Point loc, Materials *material) {
  this->rad = rad;
  location = loc;
  this->material = material;
}

bool Sphere::boundingBox(double t0, double t1, aabb &outputBox) const {
  outputBox = aabb(sub(location, Point(rad, rad, rad)),
                   add(location, Point(rad, rad, rad)));
  return true;
}

bool Sphere::hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const {
  bool intercept = false;
  Vec3 v = sub(r.origin.direction(), location.direction());
  float a = dotProduct(r.direction, r.direction);
  float b = dotProduct(v, r.direction);
  float c = dotProduct(v, v) - (rad * rad);
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
  rec.p = r.pointAtTime(rec.t);
  Vec3 outwardNormal =
      unitVec(scale(1.0 / rad, (rec.p - location)).direction());
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

void Sphere::getUV(const Vec3 &p, float &u, float &v) {

  // taken from raytracing book
  //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
  //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
  //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

  double theta = acos(-p.y);
  double phi = atan2(-p.z, p.x) + PI;

  u = phi / (2 * PI);
  v = theta / PI;
  // std::cout << u  << " " << v << std::endl;
}

double Sphere::pdfValue(const Point &o, const Vec3 &v) const {

  hitRecord rec;

  // Ray didn't hit this object. PDF is zero
  if (!this->hit(Ray(o, v), rec, 0.001, DBL_INF))
    return 0;

  float lengthSquared = length(sub(location, o).direction());
  lengthSquared *= lengthSquared;
  float cosThetaMax = sqrt(1 - (rad * rad / lengthSquared));
  float solidAngle = 2 * PI * (1 - cosThetaMax);

  // returns the inverse of the solid angle; the larger the solid angle, the
  // higher the probability. Thus we need to downsample.
  return 1.0 / solidAngle;
}

Vec3 Sphere::random(const Point &o) const {
  Vec3 direction = sub(location, o).direction();
  float distanceSquared = length(direction) * length(direction);
  onb uvw;
  uvw.buildFromW(direction);
  return uvw.local(randomSphereRay(rad, distanceSquared));
}
