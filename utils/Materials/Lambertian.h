#include "../Materials.h"
#include "utils/Vec.h"
#include "utils/Ray.h"
#include "utils/VectorOps.h"
#include "utils/Functions.h"

class Lambertian : public utils::Materials
{
public:
    Lambertian(const Point &a) : albedo(a) {}
    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Point P = rec.p;
        Vec w = randomRayInSphere();
        w = math::add(w, rec.normal);
        scattered = Ray(rec.p, w);
        attenuation = albedo;
        return true;
    }

    Point albedo;
};