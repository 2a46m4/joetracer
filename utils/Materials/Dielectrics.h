#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../VectorOps.h"
#include "../Functions.h"

class Dielectrics : public prims::Materials
{
public:
    Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Vec outwardNormal;
        Vec reflected = math::reflection(rec.normal, ray.direction);
        float coeff;
        float cosine;
        attenuation = Point(1, 1, 1);
        float reflectProb;
        // If the ray is going into a dielectric
        if (math::dotProduct(ray.direction, rec.normal) > 0)
        {
            outwardNormal = -rec.normal;
            coeff = refractIdx;
            cosine = refractIdx * math::dotProduct(ray.direction, rec.normal) / math::length(ray.direction);
        }
        else
        {
            // The ray is going out of a dielectric
            outwardNormal = rec.normal;
            coeff = 1.0f / refractIdx;
            cosine = -math::dotProduct(ray.direction, rec.normal) / math::length(ray.direction);
        }
        Vec refracted;
        // Checks for reflection or refraction at large angles
        if (refract(ray.direction, outwardNormal, coeff, refracted))
        {
            reflectProb = math::schlick(cosine, refractIdx);
        }
        else
        {
            reflectProb = 1.0;
        }
        if (drand48() < reflectProb)
            scattered = Ray(rec.p, refracted);
        else
            scattered = Ray(rec.p, reflected);
        return true;
    }

    float refractIdx;
};