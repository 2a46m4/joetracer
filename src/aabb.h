#ifndef _AABB_H
#define _AABB_H

#include <cmath>

#include "Point.h"
#include "Ray.h"
    // Axis aligned bounding box
    class aabb
    {
    public:
        aabb();

        // The closest and farthest point in the bounding box volume. Closest and farthest from the origin
        aabb(const Point &a, const Point &b);

        // Takes ray to be examined, the interval tmin and tmax and returns if the ray has intersected the bounding box or not
        bool hit(const Ray &r, double tMin, double tMax) const;

        Point min;
        Point max;
    };

    // Returns the bounding box for two bounding boxes
    aabb surroundingBox(aabb box0, aabb box1);


#endif