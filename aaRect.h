#ifndef _AA_RECT_H
#define _AA_RECT_H

#include <cmath>

#include "Hittable.h"
#include "Point.h"
#include "Ray.h"

// Axis aligned rectangle
class XYRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XYRectangle(double x0, double x1, double y0, double y1, double k,
              Materials *mat);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double x0, x1, y0, y1, k;
};

// Axis aligned rectangle
class XZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XZRectangle(double x0, double x1, double z0, double z1, double k,
              Materials *mat);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double x0, x1, z0, z1, k;
};

// Axis aligned rectangle
class YZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  YZRectangle(double y0, double y1, double z0, double z1, double k,
              Materials *mat);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double y0, y1, z0, z1, k;
};

#endif
