#ifndef _POINT_H
#define _POINT_H

#include "Vec.h"

namespace utils
{
    class Point
    {
    public:
        int x;
        int y;
        int z;

        Point();

        Point(int x, int y, int z);

        // Returns distance between two points
        double dist(Point p);

        void addVector(Vec v);
    };
}

#endif