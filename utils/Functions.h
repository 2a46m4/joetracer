#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Vec.h"
#include "Point.h"
#include "VectorOps.h"
#include <random>
#include <cmath>

namespace utils
{
    Vec randomRayInSphere();

    bool refract(const Vec& v, const Vec& n, float refractind, Vec& refracted);
}

#endif