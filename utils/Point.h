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

        static Point one();

        static Point zero();

        static Point char_max();

        Vec direction();
    };
}

#endif