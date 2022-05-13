#ifndef _BVHNODE_H
#define _BVHNODE_H

#include <vector>

#include "Hittable.h"
#include "Ray.h"

namespace prims
{
    class BVHNode : public Hittable
    {
        BVHNode();

        BVHNode(const HittableList& list, double t0, double t1) :
            BVHNode(list.objects, 0, list.objects.size(), t0, t1) {}

        BVHNode(const std::vector<Hittable*>& objects, size_t start, size_t end, double t0, double t1);

        virtual bool hit(
            const Ray& r, hitRecord& rec, double tMin, double tMax, ) const override;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

    };

}

#endif