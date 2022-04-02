#include "Ray.h"
#include "Point.h"
#include "Vec.h"
#include "VectorOps.h"
#include <cmath>

namespace utils
{
    Ray::Ray()
    {
        origin = Point();
        direction = Vec();
    }

    Ray::Ray(Point &origin, Vec &direction)
    {
        this->origin = origin;
        this->direction = direction;
    }

    Ray::Ray(const Point &origin, const Vec &direction)
    {
        this->origin = origin;
        this->direction = direction;
    }

    Point Ray::pointAtTime(float t) const
    {
        return math::add(math::point(math::scale(t, direction)), origin);
    }
}