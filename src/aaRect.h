#ifndef _AA_RECT_H
#define _AA_RECT_H

#include <cmath>

#include "Functions.h"
#include "Hittable.h"
#include "Point.h"
#include "Ray.h"

// Axis aligned rectangle
class XYRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XYRectangle(double x0, double x1, double y0, double y1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double x0, x1, y0, y1, k;
  int face;
};

// Axis aligned rectangle
class XZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  XZRectangle(double x0, double x1, double z0, double z1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

    // This is the periodic density function of the light.
    // p(direction) = distancesquared / lightcosine * lightarea
    // This is the pdf of our light if we only sample the light.
    // If we make it farther, the buckets that the rays will fall in will be
    // higher, since the range of the angle of the rays will be smaller, given
    // the same area. Now we need to downsample the rays such that they aren't
    // overrepresented. The probability of a ray hitting a certain range inside
    // the light is given by range / pdf. for example choosing a random number
    // from 1-5, the probability of a number being within 0-2 is equal to 2/5.
    // Now, the probability is
    // a lot of light rays * lightcosine * lightarea / distancesquared.
    // given that we sample the same in a big light versus a small light, we
    // need to downsample the small light more because there will be more values
    // falling into the small light, and to keep the total probability at 1, we
    // need to divide it with a higher number - given by the equation above.
    // This is analagous to the inverse square law in physics.
  
  virtual double pdfValue(const Point &origin, const Vec3 &vec) const override {
    hitRecord rec;
    if (!this->hit(Ray(origin, vec), rec, 0.001, DBL_INF)) {
      return 0;
    }

    double area = (x1 - x0) * (z1 - z0);
    double distanceSquared = rec.t * rec.t * length(vec) * length(vec);
    double cosine = fabs(dotProduct(rec.normal, vec) / length(vec));
    return distanceSquared / (cosine * area);
  }

  virtual Vec3 random(const Point& origin) const override {
    Point randomPoint = Point(randomgen::randomNum(x0, x1), k, randomgen::randomNum(z0, z1));
    return sub(randomPoint, origin).direction();
  }

private:
  Materials *mat;
  double x0, x1, z0, z1, k;
  int face;
};

// Axis aligned rectangle
class YZRectangle : public Hittable {
public:
  // The two corners that define the rectangle. also the z distance and the
  // material
  YZRectangle(double y0, double y1, double z0, double z1, double k,
              Materials *mat, int face);

  // Takes ray to be examined, the interval tmin and tmax and returns if the ray
  // has intersected the bounding box or not
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

private:
  Materials *mat;
  double y0, y1, z0, z1, k;
  int face;
};

#endif
