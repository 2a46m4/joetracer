#include <vector>
#include <algorithm>
#include <iostream>

#include "BVHNode.h"
#include "Hittable.h"
#include "../utils/Ray.h"
#include "../utils/aabb.h"
#include "../utils/Functions.h"

namespace prims
{

    // Divides a list of objects into several bounding boxes. It does this by randomly selecting an axis to divide and then sorting the objects with respect to the axis.
    // Future: determine a better way to divide objects. Octrees/k-d trees would be applicable I think?
    BVHNode::BVHNode(const std::vector<Hittable *> &objects, size_t start, size_t end, double t0, double t1)
    {
        std::vector<Hittable *> objs = objects; // can now modify objects - it will modify objects (despite const), as these are references
        // Direction to cut
        int axis = math::randomNum(0, 3);
        // Lambda function to compare boxes
        auto boxCompare = [axis](Hittable *a, Hittable *b)
        {
            aabb boxA;
            aabb boxB;
            if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
                printf("Bounding box not possible for an object\n");
            if (axis == 0) // X
            {
                return boxA.min.x < boxB.min.x;
            }
            else if (axis == 1) // Y
            {
                return boxA.min.y < boxB.min.y;
            }
            else // Z
            {
                return boxA.min.z < boxB.min.z;
            }
        };

        size_t size = end - start; // size of the list to be sorted
        // std::cout << size << std::endl;
        // Only one item in the list. Should only happen if there is only one
        if (size == 1)
        {
            left = right = objs[start];
        }
        else if (size == 2)
        {
            left = objs[start];
            right = objs[start + 1];
        }
        else if (size == 3)
        {
            left = objs[start];
            right = new BVHNode(objs, start + 1, start + 3, t0, t1);
        }
        else
        {
            // Sort into two boxes
            std::sort(objs.begin() + start, objs.begin() + end, boxCompare);
            size_t mid = start + size / 2;
            // std::cout << "mid " << end - (mid + 1) << std::endl;

            // aabb testBox;
            // // std::cout << "iteration from " << start << " to " << end << std::endl;
            // for (size_t i = start; i < end; i++)
            // {
            //     objs[i]->boundingBox(t0, t1, testBox);
            //     // std::cout << testBox.max.x << std::endl;
            // }

            // Recursively define children nodes
            left = new BVHNode(objs, start, mid, t0, t1);
            right = new BVHNode(objs, mid, end, t0, t1);
        }

        aabb leftBox, rightBox;

        if (!left->boundingBox(t0, t1, leftBox) || !right->boundingBox(t0, t1, rightBox))
            printf("Bounding box is not possible for an object\n");
        box = surroundingBox(leftBox, rightBox);
    }

    // Stores the node's bounding box in outputBox and returns true
    bool BVHNode::boundingBox(double t0, double t1, aabb &outputBox) const
    {
        outputBox = box;
        return true;
    }

    // Returns true if a hittable's bounding box intersects with the ray, and if that hittable's hit function will return true (e.g. it hits an object). It checks its children's boxes (recursively if it is also a BVHNode). Stores information in rec.
    bool BVHNode::hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const
    {
        if (!box.hit(r, tMin, tMax))
            return false;

        bool hitLeft = left->hit(r, rec, tMin, tMax);
        bool hitRight = right->hit(r, rec, tMin, hitLeft ? rec.t : tMax);

        // std::cout << ((hitLeft) ? "true" : "false") << " " << ((hitRight) ? "true" : "false") << std::endl;
        return hitLeft || hitRight;
    }

    // Two children and the box that encapsulates them.
    Hittable *left;
    Hittable *right;
    aabb box;
}