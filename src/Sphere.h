#ifndef _SPHERE_H
#define _SPHERE_H

#include "./Hittable.h"
#include "./Point.h"
#include "./aabb.h"

// A geometric sphere.
class Sphere : public Hittable {
public:
  Point location;
  int rad;

  Materials *material;

  Sphere();

  Sphere(float rad, Point loc, Materials *material);

  bool boundingBox(double t0, double t1, aabb &outputBox) const override;

  bool hit(const Ray &r, hitRecord &rec, double tMin,
           double tMax) const override;
  
  double pdfValue(const Point& o, const Vec3& v) const override;

  Vec3 random(const Point& o) const override;
  
private:
  // gets the uv coordinates on a sphere given normal vector p on the unit
  // sphere. u and v are normalized to [0,1]. Given x and z = 0, u will be 0.5.
  static void getUV(const Vec3 &p, float &u, float &v);
};

#endif
