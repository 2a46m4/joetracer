#include "Move.h"
#include "Functions.h"
#include "Ray.h"
#include <iostream>

// Moves the average centre of mass of the object to the point
Move::Move(Hittable *hittablePtr, const Point &move) {
  this->hittablePtr = hittablePtr;
  aabb box;
  hittablePtr->boundingBox(0, 1, box);
  // std::cout << move << std::endl;
  // std::cout << box.min << std::endl;
  // std::cout << box.max << std::endl;
  const Point com = findCentre(box.min, box.max);
  // std::cout << com << std::endl;
  offset = sub(move, com);
  // std::cout << offset << std::endl;
}

bool Move::hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const {
  Ray moved(sub(r.origin, offset), r.direction);
  if (!hittablePtr->hit(moved, rec, tMin, tMax))
    return false;
  else {
    rec.p = add(rec.p, offset);
    rec.normal = (dotProduct(rec.normal, moved.direction) > 0)
                     ? scale(-1, rec.normal)
                     : rec.normal;
    return true;
  }
}

bool Move::boundingBox(double t0, double t1, aabb &outputBox) const {
  if (!hittablePtr->boundingBox(t0, t1, outputBox)) {
    return false;
  }
  outputBox = aabb(add(outputBox.min, offset), add(outputBox.max, offset));
  return true;
}
