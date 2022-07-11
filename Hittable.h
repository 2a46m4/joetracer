#ifndef _HITTABLE_H
#define _HITTABLE_H

#include <vector>

#include "./Functions.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Vec.h"
#include "./aabb.h"

class Materials;

// Stores time, the point, the normal, material of the object that was hit.
// Normal is always outside, so a dot product needs to be taken to ensure
// correct orientation.
struct hitRecord {
  float t;
  Point p;
  Vec normal;
  Materials *matPtr;

  double u;
  double v;
};

class Hittable {
public:
  // Returns true if the ray has hit an object within tMin and tMax, and stores
  // the information in rec.
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const = 0;

  // Returns true if a primitive can be bound with a box, and stores the
  // bounding box of the hittable object in outputBox
  virtual bool boundingBox(double t0, double t1, aabb &outputBox) const = 0;
};

#endif // _HITTABLE_H

#ifndef _MATERIALS_H
#define _MATERIALS_H

class Materials {
public:
  virtual bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation,
                       Ray &scattered, double& pdf) const = 0;

  virtual Point emitted(double u, double v, const Point &p) const {
    return Point(0, 0, 0);
  };

  virtual double scatteringPDF(const Ray &rIn, const hitRecord &rec,
                               const Ray &rOut) const {
    return 0;
  }
};

#endif // _MATERIALS_H

#ifndef _HITTABLE_LIST_H
#define _HITTABLE_LIST_H

class HittableList : public Hittable {
public:
  HittableList() {}

  void clear() { objects.clear(); }

  void add(Hittable *object) { objects.push_back(object); }

  // Returns true if a ray has hit a list of hittable objects, and stores the
  // hit information in rec.
  virtual bool hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const override {
    hitRecord tempRec;
    bool objHit = false;
    double closest = tMax;

    // Gets the closest object
    for (const auto &object : objects) {
      if (object->hit(r, tempRec, tMin, closest)) {
        objHit = true;
        closest = tempRec.t;
        rec = tempRec;
      }
    }
    return objHit;
  }

  // Returns true if a bounding box is created, and stores the smallest bounding
  // box of all the objects in outputBox.
  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override {
    if (objects.empty())
      return false;

    aabb tempBox;
    bool firstBox = true;

    for (auto &object : objects) {
      // object does not have a bounding box
      if (!object->boundingBox(t0, t1, tempBox))
        return false;
      if (firstBox)
        outputBox = tempBox;
      else
        outputBox = surroundingBox(outputBox, tempBox);
    }
    return true;
  }

  std::vector<Hittable *> objects;
};

#endif // _HITTABLE_LIST_H
