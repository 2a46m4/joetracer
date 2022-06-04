#ifndef _DIELECTRIC_H
#define _DIELECTRIC_H

#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../Functions.h"

class Dielectrics : public Materials
{
public:
    Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

    virtual bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        attenuation = Point(1, 1, 1);
        // Ray is going out of a dielectric
        if (dotProduct(ray.direction, rec.normal) > 0.0)
        {
            float cosine = refractIdx * dotProduct(unitVec(ray.direction), rec.normal);
            float sine = sqrt(1.0 - cosine * cosine);
            if ((refractIdx * sine > 1.0) || drand48() < schlick(cosine, refractIdx))
                scattered = Ray(rec.p, reflection(scale(-1, rec.normal), ray.direction));
            else
                scattered = Ray(rec.p, refract(ray.direction, scale(-1, rec.normal), refractIdx));
        }
        else
        {
            float cosine = -dotProduct(unitVec(ray.direction), rec.normal);
            float sine = sqrt(1.0 - cosine * cosine);
            // If there is total internal reflection || fresnel effect on glancing edges
            if (((1.0f / refractIdx) * sine > 1.0) || drand48() < schlick(cosine, (1.0f / refractIdx)))
                scattered = Ray(rec.p, reflection(rec.normal, ray.direction));                
            else
                scattered = Ray(rec.p, refract(ray.direction, rec.normal, (1.0f / refractIdx)));
        }
        return true;
    }

    float refractIdx;
};

#endif