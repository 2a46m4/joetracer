#include "Ray.h"
#include "Point.h"
#include "Vec.h"
#include "VectorOps.h"
#include <cmath>

namespace utils
{

    Ray::Ray(Point &origin, Vec &direction) {
        this->origin = origin;
        this->direction = direction;
    }

    Vec Ray::pointAtTime(float t) const {
        return math::add(math::scale(t, direction), origin.direction());
    }
}