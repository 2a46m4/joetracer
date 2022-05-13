#ifndef _METAL_H
#define _METAL_H

#include "../Hittable.h"
#include "../../utils/Vec.h"
#include "../../utils/Ray.h"
#include "../../utils/Functions.h"

// using namespace math;

class Metal : public prims::Materials {
    public:
        Metal(const Point& a, float f) : albedo(a) {
            if (f < 1) fuzz = f;
            else fuzz = 1;
        }
        virtual bool scatter(const Ray& ray, const prims::hitRecord& rec, Point& attenuation, Ray& scattered) const {
            const Vec reflected = math::reflection(rec.normal, ray.direction);
            scattered = Ray(rec.p, math::add(reflected, math::scale(fuzz, randomRayInSphere(rec.normal))));
            attenuation = albedo;
            return (math::dotProduct(scattered.direction, rec.normal) > 0);
        }

        Point albedo;
        float fuzz;
};

#endif