#include "Point.h"
#include "Vec.h"
#include <cmath>

namespace utils
{
    Point::Point()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Point::Point(float x, float y, float z)
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
    
    Vec Point::direction() {
        return Vec(x, y, z);
    }
}