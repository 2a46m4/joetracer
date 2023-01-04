#ifndef _AA_RECT_H
#define _AA_RECT_H

#include <cmath>

#include "Functions.h"
#include "Hittable.h"
#include "Point.h"
#include "Ray.h"

// Axis aligned rectangle, aligned in the XY plane.
class XYRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XYRectangle(double x0, double x1, double y0, double y1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double x0, x1, y0, y1, k;
  int face;
};

// Axis aligned rectangle, aligned in the XZ plane.
class XZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XZRectangle(double x0, double x1, double z0, double z1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;
  
  virtual double pdfValue(const Point3 &origin, const Vector3 &vec) const override {
    hitRecord rec;
    if (!this->hit(Ray3(origin, vec), rec, 0.001, DBL_INF)) {
      return 0;
    }

    double area = (x1 - x0) * (z1 - z0);
    double distanceSquared = rec.t * rec.t * vec.dot(vec);
    double cosine = fabs(rec.normal.dot(vec) / fsqrt(vec.dot(vec)));
    return distanceSquared / (cosine * area);
  }

  virtual Vector3 random(const Point3& origin) const override {
    Point3 randomPoint = Point3(randomgen::randomNum(x0, x1), k, randomgen::randomNum(z0, z1));
    return randomPoint - origin;
  }

private:
  Materials *mat;
  double x0, x1, z0, z1, k;
  int face;
};

// Axis aligned rectangle, aligned in the YZ plane.
class YZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  YZRectangle(double y0, double y1, double z0, double z1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double y0, y1, z0, z1, k;
  int face;
};

#endif
