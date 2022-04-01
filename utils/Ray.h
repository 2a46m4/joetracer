#ifndef _RAY_H
#define _RAY_H

#include "Point.h"
#include "Vec.h"

namespace utils
{
    class Ray
    {
    public:
        Point origin;

        Vec direction;

        Ray();

        Ray(Point& origin, Vec& direction);

        Vec pointAtTime(float t) const;
    };
}

#endif