#include "Surfel.h"
#include "Point.h"
#include "Vec.h"

#define PI 3.14159265358979323846264338327950288419716939937510582097

namespace utils
{
    // Local surface geometry + BSDF + emission function
    // Should be used in conjunction with a surface map as that will give the shading normal (the angle of the surface) via a map
    Surfel::Surfel() {}

    // Temp function, does not have any radiance
    Point Surfel::emittedRadiance(const Vec &wo) {
        return Point(0, 0, 0);
    }

    Point Surfel::finiteScatteringDensity(const Vec &wi, const Vec &wo)
    {
        // Ideal matte surface
        return Point(1/(2*PI), 1/(2*PI), 1/(2*PI));
    }
};
