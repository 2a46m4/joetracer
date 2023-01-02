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
  Point3 p;
  Vector3 normal;
  float t;
  bool frontFacing;

  inline void setFaceNormal(const Ray3 &r, const Vector3 &outwardNormal) {
    frontFacing = r.direction.dot(outwardNormal) < 0;
    normal = frontFacing ? outwardNormal : -outwardNormal;
  }
};

// Stores the PDF of the ray, the attenuation, the specular ray, and if the ray is specular
struct scatterRecord {
  pdf *pdfptr;
  Point3 attenuation;
  Ray3 specularRay;
  bool isSpecular;
};

// represents an object that a ray can intersect with.
class Hittable {
public:
  // Returns true if the ray has hit an object within tMin and tMax, and stores
  // the information in rec.
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const = 0;

  // Returns true if a Hittable can be bounded by a box, and stores the
  // bounding box of the hittable object in outputBox
  virtual bool boundingBox(double t0, double t1, aabb &outputBox) const = 0;

  // Returns the probability of a ray that starts at origin hitting this object.
  virtual double pdfValue(const Point3 &origin, const Vector3 &v) const {
    return 0.0;
  }

  // random
  virtual Vector3 random(const Point3 &origin) const { return Vector3(1, 0, 0); }
};

#endif // _HITTABLE_H

#ifndef _MATERIALS_H
#define _MATERIALS_H

class Materials {
public:
  virtual bool scatter(const Ray3 &ray, const hitRecord &rec,
                       scatterRecord &) const = 0;

  virtual Point3 emitted(double u, double v, const Point3 &p, const hitRecord,
                        const Ray3) const {
    return Point3(0, 0, 0);
  };

  virtual double scatteringPDF(const Ray3 &rIn, const hitRecord &rec,
                               const Ray3 &rOut) const {
    return 0;
  }
};

#endif // _MATERIALS_H

#ifndef _HITTABLE_LIST_H
#define _HITTABLE_LIST_H

// a list of hittable objects
class HittableList : public Hittable {
public:
  HittableList() {}

  void clear() { objects.clear(); }

  void add(Hittable *object) { objects.push_back(object); }

  // Returns true if a ray has hit a list of hittable objects, and stores the
  // hit information in rec.
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
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

  double pdfValue(const Point3 &origin, const Vector3 &v) const override {
    float weight = 1.0 / objects.size();
    float sum = 0.0;
    for (const auto &object : objects) {
      sum += weight * object->pdfValue(origin, v);
    }
    return sum;
  }

  Vector3 random(const Point3 &origin) const override {
    return objects[randomgen::randomInt(0, objects.size() - 1)]->random(origin);
  }

  std::vector<Hittable *> objects;
};

#endif // _HITTABLE_LIST_H
