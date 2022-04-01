#ifndef _MATERIALS_H
#define _MATERIALS_H

#include "Point.h"
#include "Vec.h"

namespace utils
{
    class Materials
    {
        // Let's have this as a virtual function and have separate classes for different materials, which all derive from this virtual function
    public:
        Point emittedRadiance(const Vec &wo);

        // Returns the scattering density, for now just assumes that all materials are matte
        Point finiteScatteringDensity(const Vec &wi, const Vec &wo);

        // Approximate reflectivity of surface, returns colour
        Point reflectivity();
    };
}

#endif