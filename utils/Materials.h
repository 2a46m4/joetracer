#ifndef _MATERIALS_H
#define _MATERIALS_H

#include "Point.h"
#include "Vec.h"
#include "Hittable.h"

namespace utils
{
    class Materials
    {
    public:
        virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point attenuation, Ray &scattered) const = 0;

        Point emittedRadiance(const Vec &wo);

        // Returns the scattering density, for now just assumes that all materials are matte
        Point finiteScatteringDensity(const Vec &wi, const Vec &wo);

        // Approximate reflectivity of surface, returns colour
        Point reflectivity();
    };


}

#endif