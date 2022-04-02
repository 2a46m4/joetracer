#ifndef _METAL_H
#define _METAL_H

#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../VectorOps.h"

class Metal : public prims::Materials {
    public:
        Metal(const Point& a) : albedo(a) {}
        virtual bool scatter(const Ray& ray, const prims::hitRecord& rec, Point& attenuation, Ray& scattered) const {
            const Vec reflected = math::reflection(rec.normal, ray.direction);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (math::dotProduct(scattered.direction, rec.normal) > 0);
        }

        Point albedo;
};

#endif