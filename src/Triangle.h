#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Hittable.h"
#include "Point.h"

class Triangle : public Hittable {
public:
  Triangle();

  Triangle(const Point &P0, const Point &P1, const Point &P2);

  bool boundingBox(double t0, double t1, aabb &outputBox) const override;

  bool hit(const Ray &r, hitRecord &rec, double tMin,
           double tMax) const override;

  double pdfValue(const Point &o, const Vec3 &v) const override;

  Vector3 random(const Point &o) const override;

private:
	Point vertices[3];
};

#endif
