#ifndef _AABB_H
#define _AABB_H

#include <cmath>

#include "Point.h"
#include "Ray.h"

namespace utils
{
    // Axis aligned bounding box
    class aabb
    {
    public:
        aabb() {}

        // The closest and farthest point in the bounding box volume. Closest and farthest from the origin
        aabb(const Point &a, const Point &b)
        {
            min = a;
            max = b;
        }

        // Takes ray to be examined, the interval tmin and tmax and returns if the ray has intersected the bounding box or not
        bool hit(const Ray &r, double tMin, double tMax) const
        {
            // Checks if there is an interval within the three dimensions that overlap each other

            // The "speed" of the x vector
            double dirX = 1.0 / r.direction.x;
            // X dimension. If coming from behind, max will be smaller, so return the smaller of the two.
            double t0x = fmin((min.x - r.origin.x) * dirX,
                              (max.x - r.origin.x) * dirX);
            // Similarly, return the greater of the two.
            double t1x = fmax((min.x - r.origin.x) * dirX,
                              (max.x - r.origin.x) * dirX);

            // gets the interval of this dimension.
            // If the rays is parallel with a dimension but outside the box, one of them will be infinity or negative infinity, and will fail the next check
            tMin = fmax(t0x, tMin);
            tMax = fmin(t1x, tMin);

            // If the max time possible for a interval in a certain dimension is less than the min time possible for an interval in a certain dimension
            // It is not possible for the two to intersect. Therefore, return false.
            // Or, if one of them is parallel, then this condition will also fail.
            // If they are equal, then the ray is grazing the corner of the box.
            if (tMax <= tMin)
                return false;

            // Y dimension.
            double dirY = 1.0 / r.direction.y;
            double t0y = fmin((min.y - r.origin.y) * dirY,
                              (max.y - r.origin.y) * dirY);
            double t1y = fmax((min.y - r.origin.y) * dirY,
                              (max.y - r.origin.y) * dirY);
            tMin = fmax(t0y, tMin);
            tMax = fmin(t1y, tMin);

            if (tMax <= tMin)
                return false;

            // Z dimension.
            double dirZ = 1.0 / r.direction.z;
            double t0z = fmin((min.z - r.origin.z) * dirZ,
                              (max.z - r.origin.z) * dirZ);
            double t1z = fmax((min.z - r.origin.z) * dirZ,
                              (max.z - r.origin.z) * dirZ);
            tMin = fmax(t0z, tMin);
            tMax = fmin(t1z, tMin);

            if (tMax <= tMin)
                return false;
            else
                return true;
        }

        Point min;
        Point max;
    };

    // Returns the bounding box for two bounding boxes
    aabb surroundingBox(aabb box0, aabb box1)
    {
        return aabb(Point(fmin(box0.min.x, box1.min.x),
                          fmin(box0.min.y, box1.min.y),
                          fmin(box0.min.z, box1.min.z)),
                    Point(fmax(box0.max.x, box1.max.x),
                          fmax(box0.max.y, box1.max.y),
                          fmax(box0.max.z, box1.max.z)));
    }

}

#endif