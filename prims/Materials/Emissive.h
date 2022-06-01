#ifndef _EMISSIVE_H
#define _EMISSIVE_H

#include "../Hittable.h"
#include "../../utils/Vec.h"
#include "../../utils/Ray.h"
#include "../../utils/Functions.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"

using namespace math;

class Emissive : public prims::Materials
{
public:
    Emissive(const Point &a) : emit(new prims::SolidColour(a)) {}
	Emissive(const prims::Texture* a) : emit(a){};
    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Vec w = randomRayInSphere(rec.normal);
        scattered = Ray(rec.p, w);
        attenuation = emit->value(rec.u, rec.v, rec.p);
        return true;
    }

    const prims::Texture* emit;
};

#endif