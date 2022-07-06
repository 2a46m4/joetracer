#include "Rotation.h"
#include "Functions.h"
#include "Point.h"
#include "Vec.h"
#include <climits>
#include <cmath>
#include <limits>

Rotation::Rotation(Hittable *p, Point angle) {
  obj = p;
  double radX = degreesToRadians(angle.x);
  double radY = degreesToRadians(angle.y);
  double radZ = degreesToRadians(angle.z);

  hasBox = p->boundingBox(0, 1, rotBox);

  sinXTheta = std::sin(radX);
  cosXTheta = std::cos(radX);

  double inf = std::numeric_limits<double>::max();
  double neginf = std::numeric_limits<double>::lowest();
  
  Point min(inf, inf, inf);
  Point max(neginf, neginf, neginf);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {

        // gets each box corner to test
        double x = i * rotBox.max.x + (1 - i) * rotBox.min.x;
        double y = j * rotBox.max.y + (1 - j) * rotBox.min.y;
        double z = k * rotBox.max.z + (1 - k) * rotBox.min.z;

	// The rotated x and rotated y
        double newX = cosXTheta * x + sinXTheta * z;
        double newZ = -sinXTheta * x + cosZTheta * z;

	// aabb bounding boxes are still axis aligned, so we need to find the smallest box that fits with the new corners
        Vec cur(newX, y, newZ);

        min.x = std::fmin(min.x, cur.x);
        max.x = std::fmax(max.x, cur.x);
        min.y = std::fmin(min.y, cur.y);
        max.y = std::fmax(max.y, cur.y);
        min.z = std::fmin(min.z, cur.z);
        max.z = std::fmax(max.z, cur.z);
      }
    }
  }
  // gets the new box dimensions
  rotBox = aabb(min, max);
}

bool Rotation::hit(const Ray &r, hitRecord &rec, double tMin,
                   double tMax) const {

  Point origin = r.origin;
  Vec direction = r.direction;

  // Rotate origin of the ray
  origin.x = (cosXTheta * r.origin.x) - (sinXTheta * r.origin.z);
  origin.z = (sinXTheta * r.origin.x) + (cosXTheta * r.origin.z);

  // Rotate direction of the ray
  direction.x = cosXTheta * r.direction.x - sinXTheta * r.direction.z;
  direction.z = sinXTheta * r.direction.x + cosXTheta * r.direction.z;

  // Rotate the ray
  Ray rotated(origin, direction);
  if (!obj->hit(rotated, rec, tMin, tMax))
    return false;

  Point p = rec.p;
  Vec normal = rec.normal;

  // Rotate hit point
  p.x = cosXTheta * rec.p.x + sinXTheta * rec.p.z;
  p.z = -sinXTheta * rec.p.x + cosXTheta * rec.p.z;

  // Rotate the normal
  normal.x = cosXTheta * rec.normal.x + sinXTheta * rec.normal.z;
  normal.z = -sinXTheta * rec.normal.x + sinXTheta * rec.normal.z;

  rec.p = p;
  rec.normal = normal;

  return true;
}

bool Rotation::boundingBox(double t0, double t1, aabb &outputBox) const {
  outputBox = rotBox;
  return hasBox;
}