#include "Functions.h"

namespace utils
{
    Vec randomRayInSphere()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1, 1);
        Vec w;
        do
        {
            w = Vec(dis(gen), dis(gen), dis(gen));
        } while (math::length(w) >= 1.0);
        return w;
    }

    // Returns true if there is refraction (and not total internal reflection), and finds the direction of the ray.
    bool refract(const Vec& v, const Vec& n, float coeff, Vec& refracted) {
        Vec uv = math::getUnitVec(v);
        float angle = math::dotProduct(uv, n);
        float discriminant = 1.0 - coeff * coeff * (1 - angle * angle);
        if(discriminant > 0) {
            refracted = math::sub(math::scale(coeff, math::sub(uv, math::scale(angle, n))), math::scale(sqrt(discriminant), n));
            return true;
        } else return false;
    }
}
