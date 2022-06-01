#ifndef _BVHNODE_H
#define _BVHNODE_H

#include <vector>
#include <algorithm>

#include "Hittable.h"
#include "../utils/Ray.h"
#include "../utils/aabb.h"
#include "../utils/Functions.h"

namespace prims
{
    class BVHNode : public Hittable
    {
        public:
        BVHNode();

        BVHNode(const HittableList &list, double t0, double t1) : BVHNode(list.objects, 0, list.objects.size(), t0, t1) {}

        // Divides a list of objects into several bounding boxes. It does this by randomly selecting an axis to divide and then sorting the objects with respect to the axis.
        // Future: determine a better way to divide objects. Octrees/k-d trees would be applicable I think?
        BVHNode(const std::vector<Hittable *> &objects, size_t start, size_t end, double t0, double t1);

        virtual bool hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const override;

        virtual bool boundingBox(double t0, double t1, aabb &outputBox) const override;

        // Two children and the box that encapsulates them.
        Hittable *left;
        Hittable *right;
        aabb box;
    };

}

#endif