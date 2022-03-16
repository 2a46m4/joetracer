#include "Point.h"
#include <cmath>

namespace utils
{
    Point::Point()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Point::Point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Uses sqrt distance
    double Point::dist(Point p)
    {
        double a = (x - p.x) * (x - p.x);
        double b = (y - p.y) * (y - p.y);
        double c = (z - p.z) * (z - p.z);

        return sqrt(a + b + c);
    }

    void Point::addVector(Vec v) {
        x += v.dx;
        y += v.dy;
        z += v.dz;
    }

}