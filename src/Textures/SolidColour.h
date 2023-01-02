#ifndef _SOLID_COLOUR_H
#define _SOLID_COLOUR_H

#include "../Point.h"
#include "Texture.h"

	class SolidColour : public Texture
	{
	public:
		SolidColour() {}

		SolidColour(Point3 c) : Colour(c) {}

		SolidColour(double r, double g, double b)
		{
			Colour = Point3(r, g, b);
		}

		Point3 value(double u, double v, const Point3 p) const override {
			return Colour;
		}

	private:
		Point3 Colour;
	};

#endif
