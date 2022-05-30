#ifndef _LAMBERTIAN_H
#define _LAMBERTIAN_H

#include "../Hittable.h"
#include "../../utils/Vec.h"
#include "../../utils/Ray.h"
#include "../../utils/Functions.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"

using namespace math;

class Lambertian : public prims::Materials
{
public:
    Lambertian(const Point &a) : albedo(new prims::SolidColour(a)) {}
	Lambertian(const prims::Texture* a) : albedo(a){};
    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Vec w = randomRayInSphere(rec.normal);
        scattered = Ray(rec.p, w);
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }

    const prims::Texture* albedo;
};

#endif