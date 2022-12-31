#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Point &P0, const Point &P1, const Point &P2) {}

bool Triangle::boundingBox(double t0, double t1, aabb &outputBox) const {
  
}

bool Triangle::hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

double Triangle::pdfValue(const Point &o, const Vec3 &v) const override;

Vec3 Triangle::random(const Point &o) const override;
