#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../Functions.h"

using namespace math;

class Dielectrics : public prims::Materials
{
public:
    Dielectrics(float refractIdx) : refractIdx(refractIdx) {}

    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Vec reflected = math::reflection(rec.normal, ray.direction);
        float coeff;
        float cosine = math::dotProduct(math::unitVec(ray.direction), rec.normal);
        float sine = sqrt(1.0 - cosine * cosine);
        attenuation = Point(1, 1, 1);
        // If the ray is going into a dielectric
        if (math::dotProduct(ray.direction, rec.normal) > 0.0)
        {
            if ((coeff * sine > 1.0) || drand48() < math::schlick(cosine, refractIdx))
                scattered = Ray(rec.p, math::refract(ray.direction, scale(-1, rec.normal), coeff));
            else
                scattered = Ray(rec.p, math::reflection(scale(-1, rec.normal), ray.direction));
        }
        else
        {
            // The ray is going out of a dielectric
            coeff = 1.0f / refractIdx;
            // If there is total internal reflection || fresnel takes over
            if ((coeff * sine > 1.0) || drand48() < math::schlick(cosine, coeff))
                scattered = Ray(rec.p, math::refract(ray.direction, rec.normal, coeff));
            else
                scattered = Ray(rec.p, math::reflection(rec.normal, ray.direction));
        }
        return true;
    }

    float refractIdx;
};