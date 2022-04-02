#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../VectorOps.h"
#include "../Functions.h"

class Lambertian : public prims::Materials
{
public:
    Lambertian(const Point &a) : albedo(a) {}
    virtual bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
    {
        Point P = rec.p;
        Vec w = utils::randomRayInSphere();
        w = math::add(w, rec.normal);
        scattered = Ray(rec.p, w);
        attenuation = albedo;
        return true;
    }

    Point albedo;
};