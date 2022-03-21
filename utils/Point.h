#ifndef _POINT_H
#define _POINT_H

#include "Vec.h"

namespace utils
{
    class Point
    {
    public:
        float x, y, z;

        Point();

        Point(float x, float y, float z);

        // Returns distance between two points
        double dist(Point p);

        Vec direction();
    };
}

#endif