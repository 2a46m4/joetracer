#ifndef _BVHNODE_H
#define _BVHNODE_H

#include <algorithm>
#include <vector>

#include "./Functions.h"
#include "./Ray.h"
#include "./aabb.h"
#include "Hittable.h"

// A binary tree that stores the bounding boxes of two Hittables, which are
// separated by an axis.
class BVHNode : public Hittable {
public:
  BVHNode();

  BVHNode(const HittableList &list, double t0, double t1)
      : BVHNode(list.objects, 0, list.objects.size(), t0, t1) {}

  // Constructor for a BVHNode. Given a list of objects, sorts the list by an
  // axis and divides it into two smaller Hittables.
  // TODO: determine a better way to divide objects.
  // Octrees/k-d trees would be applicable I think?
  BVHNode(const std::vector<Hittable *> &objects, size_t start, size_t end,
          double t0, double t1);

  // Determines if a ray has hit some Hittable in the BVHNode. If it did, then
  // return true and store the information about the hit in hitRecord. Otherwise
  // return false.
  virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const override;

  // Stores the BVHNode's bounding box in outputBox.
  virtual bool boundingBox(double t0, double t1,
                           aabb &outputBox) const override;

  // Left child
  Hittable *left;
  // Right Child
  Hittable *right;
  // Box that encapsulates the BVHNode
  aabb box;
};

#endif
