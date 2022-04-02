#ifndef _HITTABLE_H
#define _HITTABLE_H

#include "Point.h"
#include "Vec.h"
#include "Ray.h"

using namespace utils;

class Materials;
namespace prims
{
    struct hitRecord
    {
        float t;
        Point p;
        Vec normal;
        utils::Materials *matPtr;
    };

    class Hittable
    {
    public:
        virtual bool hit(const Ray &r, float minTime, float maxTime, hitRecord &rec) const = 0;

    private:
    };

}

#endif