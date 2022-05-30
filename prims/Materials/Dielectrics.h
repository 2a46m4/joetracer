#ifndef _DIELECTRIC_H
#define _DIELECTRIC_H

#include "../Hittable.h"
#include "../../utils/Vec.h"
#include "../../utils/Ray.h"
#include "../../utils/Functions.h"

class Dielectrics : public prims::Materials
{
public:
    Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        attenuation = Point(1, 1, 1);
        // Ray is going out of a dielectric
        if (math::dotProduct(ray.direction, rec.normal) > 0.0)
        {
            float cosine = refractIdx * math::dotProduct(math::unitVec(ray.direction), rec.normal);
            float sine = sqrt(1.0 - cosine * cosine);
            if ((refractIdx * sine > 1.0) || drand48() < math::schlick(cosine, refractIdx))
                scattered = Ray(rec.p, math::reflection(scale(-1, rec.normal), ray.direction));
            else
                scattered = Ray(rec.p, math::refract(ray.direction, scale(-1, rec.normal), refractIdx));
        }
        else
        {
            float cosine = -math::dotProduct(math::unitVec(ray.direction), rec.normal);
            float sine = sqrt(1.0 - cosine * cosine);
            // If there is total internal reflection || fresnel effect on glancing edges
            if (((1.0f / refractIdx) * sine > 1.0) || drand48() < math::schlick(cosine, (1.0f / refractIdx)))
                scattered = Ray(rec.p, math::reflection(rec.normal, ray.direction));                
            else
                scattered = Ray(rec.p, math::refract(ray.direction, rec.normal, (1.0f / refractIdx)));
        }
        return true;
    }

    float refractIdx;
};

#endif