#include "Rotation.h"
#include "Functions.h"
#include "Point.h"
#include "Vector.h"
#include <climits>
#include <cmath>
#include <limits>

// Todo: replace all of this with matrices

Rotation::Rotation(Hittable *p, Point3 angle) {
  obj = p;
  hasBox = p->boundingBox(0, 1, rotBox);

  double rotYPlane = degreesToRadians(angle.x());
  double rotZPlane = degreesToRadians(angle.y());
  double rotXPlane = degreesToRadians(angle.z());

  sinXTheta = std::sin(rotYPlane);
  cosXTheta = std::cos(rotYPlane);

  sinYTheta = std::sin(rotZPlane);
  cosYTheta = std::cos(rotZPlane);

  sinZTheta = std::sin(rotXPlane);
  cosZTheta = std::cos(rotXPlane);

  double inf = std::numeric_limits<double>::max();
  double neginf = std::numeric_limits<double>::lowest();

  Point3 min(inf, inf, inf);
  Point3 max(neginf, neginf, neginf);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {

        // gets each box corner to test
        double x = i * rotBox.max.x() + (1 - i) * rotBox.min.x();
        double y = j * rotBox.max.y() + (1 - j) * rotBox.min.y();
        double z = k * rotBox.max.z() + (1 - k) * rotBox.min.z();

        // The rotated x and rotated y
        double newX = cosXTheta * x + sinXTheta * z;
        double newZ = -sinXTheta * x + cosXTheta * z;

        // aabb bounding boxes are still axis aligned, so we need to find the
        // smallest box that fits with the new corners
        Vector3 cur(newX, y, newZ);
        min.x() = std::fmin(min.x(), cur.x());
        max.x() = std::fmax(max.x(), cur.x());
        min.y() = std::fmin(min.y(), cur.y());
        max.y() = std::fmax(max.y(), cur.y());
        min.z() = std::fmin(min.z(), cur.z());
        max.z() = std::fmax(max.z(), cur.z());
      }
    }
  }
  // gets the new box dimensions
  rotBox = aabb(min, max);
}

bool Rotation::hit(const Ray3 &r, hitRecord &rec, double tMin,
                   double tMax) const {

  Point3 origin = r.origin;
  Vector3 direction = r.direction;

  // Rotate origin of the ray
  origin.x() = (cosXTheta * r.origin.x()) - (sinXTheta * r.origin.z());
  origin.z() = (sinXTheta * r.origin.x()) + (cosXTheta * r.origin.z());

  // Rotate direction of the ray
  direction.x() = cosXTheta * r.direction.x() - sinXTheta * r.direction.z();
  direction.z() = sinXTheta * r.direction.x() + cosXTheta * r.direction.z();

  // Rotate the ray
  Ray3 rotated(origin, direction);
  if (!obj->hit(rotated, rec, tMin, tMax))
    return false;

  Point3 p = rec.p;
  Vector3 normal = rec.normal;

  // Rotate hit point
  p.x() = cosXTheta * rec.p.x() + sinXTheta * rec.p.z();
  p.z() = -sinXTheta * rec.p.x() + cosXTheta * rec.p.z();

  // Rotate the normal
  normal.x() = cosXTheta * rec.normal.x() + sinXTheta * rec.normal.z();
  normal.z() = -sinXTheta * rec.normal.x() + cosXTheta * rec.normal.z();

  rec.p = p;
  rec.setFaceNormal(rotated, normal);
  return true;
}

bool Rotation::boundingBox(double t0, double t1, aabb &outputBox) const {
  outputBox = rotBox;
  return hasBox;
}

