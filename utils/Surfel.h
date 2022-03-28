#ifndef _SURFEL_H
#define _SURFEL_H

#include "Point.h"
#include "Vec.h"

namespace utils
{
    class Surfel
    {
    public:
        float x, y, z;

        Point position;

        Vec shadingNormal;

        Surfel();

        Point emittedRadiance(const Vec& wo);

        Point finiteScatteringDensity(const Vec& wi, const Vec& wo);
    };
}

#endif