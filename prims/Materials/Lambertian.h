#ifndef _LAMBERTIAN_H
#define _LAMBERTIAN_H

#include "../Hittable.h"
#include "../../utils/Vec.h"
#include "../../utils/Ray.h"
#include "../../utils/Functions.h"

using namespace math;

class Lambertian : public prims::Materials
{
public:
    Lambertian(const Point &a) : albedo(a) {}
    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Point P = rec.p;
        Vec w = randomRayInSphere(rec.normal);
        scattered = Ray(rec.p, w);
        attenuation = albedo;
        return true;
    }

    Point albedo;
};

#endif