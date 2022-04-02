#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "Point.h"
#include "Vec.h"
#include "Ray.h"

using namespace utils;

namespace prims
{
    class Materials;

    struct hitRecord
    {
        float t;
        Point p;
        Vec normal;
        Materials *matPtr;
    };

    class Hittable
    {
    public:
        virtual bool hit(const Ray &r, hitRecord &rec) const = 0;

    private:
    };

    class Materials
    {
    public:
        virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point& attenuation, Ray &scattered) const = 0;

        Point emittedRadiance(const Vec &wo);

        // Returns the scattering density, for now just assumes that all materials are matte
        Point finiteScatteringDensity(const Vec &wi, const Vec &wo);

        // Approximate reflectivity of surface, returns colour
        Point reflectivity();
    };
}

#endif