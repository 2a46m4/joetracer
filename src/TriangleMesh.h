#ifndef _TRIANGLE_MESH_H
#define _TRIANGLE_MESH_H

#include "Hittable.h"
#include "Point.h"
#include "Vector3.h"
#include <vector>

class TriangleMesh : public Hittable {
public:
  TriangleMesh();

  TriangleMesh(const int numTriangles, const int *vertexIndices, const Point *p,
               const Vec3 *s, const Vec3 *n, Materials *material);

  bool boundingBox(double t0, double t1, aabb &outputBox) const override;

  bool hit(const Ray &r, hitRecord &rec, double tMin,
           double tMax) const override;

  double pdfValue(const Point &o, const Vec3 &v) const override;

  Vec3 random(const Point &o) const override;

private:
  const int numTriangles, numVertices;
  std::vector<int> vertexIndices;

  Point vertices[3];
};

#endif
