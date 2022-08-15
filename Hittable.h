#ifndef _HITTABLE_H
#define _HITTABLE_H

#include <vector>

#include "./Functions.h"
#include "./aabb.h"
#include "./pdf.h"
#include "RandomGenerator.h"

class Materials;

// Stores time, the point, the normal, material of the object that was hit.
// Normal is always outside, so a dot product needs to be taken to ensure
// correct orientation.
struct hitRecord {
  Materials *matPtr;
  float u;
  float v;
  Point p;
  Vec normal;
  float t;
  bool frontFacing;

  inline void setFaceNormal(const Ray &r, const Vec &outwardNormal) {
    frontFacing = dotProduct(r.direction, outwardNormal) < 0;
    normal = frontFacing ? outwardNormal : -outwardNormal;
  }
};

struct scatterRecord {
  pdf *pdfptr;
  Point attenuation;
  Ray specularRay;
  bool isSpecular;
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

  // The PDF value of the hittable object
  virtual double pdfValue(const Point &origin, const Vec &v) const {
    return 0.0;
  }

  // random
  virtual Vec random(const Point &origin) const { return Vec(1, 0, 0); }
};

#endif // _HITTABLE_H

#ifndef _MATERIALS_H
#define _MATERIALS_H

class Materials {
public:
  virtual bool scatter(const Ray &ray, const hitRecord &rec,
                       scatterRecord &) const = 0;

  virtual Point emitted(double u, double v, const Point &p, const hitRecord,
                        const Ray) const {
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

  double pdfValue(const Point &origin, const Vec &v) const override {
    float weight = 1.0 / objects.size();
    float sum = 0.0;
    for (const auto &object : objects) {
      sum += weight * object->pdfValue(origin, v);
    }
    return sum;
  }

  Vec random(const Point &origin) const override {
    return objects[joetracer::randomInt(0, objects.size() - 1)]->random(origin);
  }

  std::vector<Hittable *> objects;
};

#endif // _HITTABLE_LIST_H
