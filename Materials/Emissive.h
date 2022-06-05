#ifndef _EMISSIVE_H
#define _EMISSIVE_H

#include "../Hittable.h"
#include "../Vec.h"
#include "../Ray.h"
#include "../Functions.h"
#include "../Textures/SolidColour.h"
#include "../Textures/Texture.h"

class Emissive : public Materials
{
public:
	Emissive(const Point &a) : emit(new SolidColour(a)) {}
	Emissive(const Texture *a) : emit(a){};
	bool scatter(const Ray &ray, const hitRecord &rec, Point &attenuation, Ray &scattered) const
	{
		return false; // never scatters, duh
	}
	Point emitted(double u, double v, const Point &p) const override
	{
		return emit->value(u, v, p);
	}

	const Texture *emit;
};

#endif