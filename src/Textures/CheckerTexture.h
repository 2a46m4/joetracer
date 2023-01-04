#ifndef _CHECKER_TEXTURE_H
#define _CHECKER_TEXTURE_H

#include "../Point.h"
#include "Texture.h"
#include "SolidColour.h"
#include <cmath>

	class CheckerTexture : public Texture
	{
	public:
		CheckerTexture() {}

		CheckerTexture(Texture* tex1, Texture* tex2) : even(tex1), odd(tex2){}

		CheckerTexture(Point3 col1, Point3 col2) :
			even(new SolidColour(col1)),
			odd(new SolidColour(col2)) {}

		Point3 value(double u, double v, const Point3 p) const override {
		  double val = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
			if(val < 0) {
				return even->value(u, v, p);
			} else return odd->value(u, v, p);
		}

	private:
		Texture* even;
		Texture* odd;
	};


#endif
