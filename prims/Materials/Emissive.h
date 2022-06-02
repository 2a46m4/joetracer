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
	Emissive(const prims::Texture *a) : emit(a){};
	bool scatter(const Ray &ray, const prims::hitRecord &rec, Point &attenuation, Ray &scattered) const
	{
		return false; // never scatters, duh
	}
	Point emitted(double u, double v, const Point &p) const override
	{
		return emit->value(u, v, p);
	}

	~Emissive() {
		delete emit;
	}

	const prims::Texture *emit;
};

#endif