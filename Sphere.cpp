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
  Vec v = sub(r.origin.direction(), location.direction());
  float a = dotProduct(r.direction, r.direction);
  float b = dotProduct(v, r.direction);
  float c = dotProduct(v, v) - (rad * rad);
  float discriminant = (b * b) - (a * c);
  float time = 0;
  if (discriminant > 0.0) {
    time = ((-sqrt(discriminant)) - b) / a;
    if (tMax > time && time > 0.001) {
      intercept = true;
      rec.t = time;
      tMax = rec.t;
	  rec.p = r.pointAtTime(rec.t);
      Vec outwardNormal = unitVec(scale(rad, (rec.p - location)).direction());
      rec.setFaceNormal(r, outwardNormal);
      getUV(rec.normal, rec.u, rec.v);
      rec.matPtr = material;
    }
    time = (sqrt(discriminant) - b) / a;
    if (tMax > time && time > 0.001) {
      intercept = true;
      rec.t = time;
      tMax = rec.t;
	  rec.p = r.pointAtTime(rec.t);
      Vec outwardNormal = unitVec(scale(rad, (rec.p - location)).direction());
      rec.setFaceNormal(r, outwardNormal);
      getUV(rec.normal, rec.u, rec.v);
      rec.matPtr = material;
    }
  }
  return intercept;
  // Vec v = sub(r.origin, location).direction();
  // double a = length(r.direction) * length(r.direction);
  // double b = dotProduct(v, r.direction);
  // double c = length(v) * length(v) - (rad * rad);
  // double discriminant = (b * b) - (a * c);
  // double time = 0;
  // if (discriminant < 0)
  //   return false; // No solutions
  // time = fmin((sqrt(discriminant) - b) / a, ((-sqrt(discriminant)) - b) / a);
  // if (tMax > time && time > 0.001) {
  //   rec.t = time;
  //   tMax = rec.t;
  //   rec.p = add(r.origin, point(scale(rec.t, r.direction)));
  //   Vec outwardNormal = unitVec(scale(rad, (rec.p - location)).direction());
  //   rec.setFaceNormal(r, outwardNormal);
  //   getUV(rec.normal, rec.u, rec.v);
  //   rec.matPtr = material;
  //   return true;
  // }
  // return false;
}

void Sphere::getUV(const Vec &p, float &u, float &v) {

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

double Sphere::pdfValue(const Point &o, const Vec &v) const {
  hitRecord rec;
  if (!this->hit(Ray(o, v), rec, 0.001, DBL_INF))
    return 0;

  float lengthSquared = length(sub(location, o).direction());
  lengthSquared *= lengthSquared;
  float cosThetaMax = sqrt(1 - rad * rad / (lengthSquared));
  float solidAngle = 2 * PI * (1 - cosThetaMax);

  return 1.0 / solidAngle;
}

Vec Sphere::random(const Point &o) const {
  Vec direction = sub(location, o).direction();
  float distanceSquared = length(direction) * length(direction);
  onb uvw;
  uvw.buildFromW(direction);
  return uvw.local(randomSphereRay(rad, distanceSquared));
}
