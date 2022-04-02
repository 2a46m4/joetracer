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

            Ray(Point &origin, Vec &direction);

            Ray(const Point &origin, const Vec &direction);

            Point pointAtTime(float t) const;
    };
}

#endif