#include "aaRect.h"
#include <iostream>

// face is 0, 1
XYRectangle::XYRectangle(double x0, double x1, double y0, double y1, double k,
                         Materials *mat, int face) {
  this->x0 = x0;
  this->x1 = x1;
  this->y0 = y0;
  this->y1 = y1;
  this->k = k;
  this->mat = mat;
  this->face = face;
}

bool XYRectangle::hit(const Ray &r, hitRecord &rec, double tMin,
                      double tMax) const {
  // time it took to reach the "z"
  double t = (k - r.origin.z) / r.direction.z;
  // No hit
  if (t < tMin || t > tMax || t < 0.001)
    return false;
  Point hit = r.pointAtTime(t);
  // Out of bounds
  if (hit.x > x1 || hit.x < x0 || hit.y > y1 || hit.y < y0)
    return false;
  rec.u = (hit.x - x0) / (x1 - x0);
  rec.v = (hit.y - y0) / (y1 - y0);
  rec.matPtr = mat;
  rec.p = hit;
  rec.t = t;

  if (face)
    rec.normal = Vec(0, 0, -1);
  else
    rec.normal = Vec(0, 0, 1);
  return true;
}

bool XYRectangle::boundingBox(double t0, double t1, aabb &outputBox) const {
  // So that the z is not infinitely thin
  outputBox = aabb(Point(x0, y0, k - 0.0001), Point(x1, y1, k + 0.0001));
  return true;
}

XZRectangle::XZRectangle(double x0, double x1, double z0, double z1, double k,
                         Materials *mat, int face) {
  this->x0 = x0;
  this->x1 = x1;
  this->z0 = z0;
  this->z1 = z1;
  this->k = k;
  this->mat = mat;
  this->face = face;
}

bool XZRectangle::hit(const Ray &r, hitRecord &rec, double tMin,
                      double tMax) const {
  double t = (k - r.origin.y) / r.direction.y;
  // No hit
  if (t < tMin || t > tMax || t < 0.001)
    return false;
  Point hit = r.pointAtTime(t);
  // Out of bounds
  if (hit.x > x1 || hit.x < x0 || hit.z > z1 || hit.z < z0)
    return false;
  rec.u = (hit.x - x0) / (x1 - x0);
  rec.v = (hit.z - z0) / (z1 - z0);
  rec.matPtr = mat;
  rec.p = r.pointAtTime(t);
  rec.t = t;
  if (face)
    rec.normal = Vec(0, -1, 0);
  else
    rec.normal = Vec(0, 1, 0);
  return true;
}

bool XZRectangle::boundingBox(double t0, double t1, aabb &outputBox) const {
  // So that the z is not infinitely thin
  outputBox = aabb(Point(x0, k - 0.0001, z0), Point(x1, k + 0.0001, z1));
  return true;
}

YZRectangle::YZRectangle(double y0, double y1, double z0, double z1, double k,
                         Materials *mat, int face) {
  this->y0 = y0;
  this->y1 = y1;
  this->z0 = z0;
  this->z1 = z1;
  this->k = k;
  this->mat = mat;
  this->face = face;
}

bool YZRectangle::hit(const Ray &r, hitRecord &rec, double tMin,
                      double tMax) const {
  double t = (k - r.origin.x) / r.direction.x;
  // No hit
  if (t < tMin || t > tMax || t < 0.001)
    return false;
  Point hit = r.pointAtTime(t);
  // Out of bounds
  if (hit.y > y1 || hit.y < y0 || hit.z > z1 || hit.z < z0)
    return false;
  rec.u = (hit.y - y0) / (y1 - y0);
  rec.v = (hit.z - z0) / (z1 - z0);
  rec.matPtr = mat;
  rec.p = hit;
  rec.t = t;
  if (face)
    rec.normal = Vec(-1, 0, 0);
  else
    rec.normal = Vec(1, 0, 0);
  return true;
}

bool YZRectangle::boundingBox(double t0, double t1, aabb &outputBox) const {
  // So that the z is not infinitely thin
  outputBox = aabb(Point(k - 0.0001, y0, z0), Point(k + 0.0001, y1, z1));
  return true;
}
