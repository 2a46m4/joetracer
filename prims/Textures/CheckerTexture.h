#ifndef _CHECKER_TEXTURE_H
#define _CHECKER_TEXTURE_H

#include "../../utils/Point.h"
#include "Texture.h"
#include "SolidColour.h"
#include <cmath>

using namespace utils;

namespace prims
{
	class CheckerTexture : public Texture
	{
	public:
		CheckerTexture() {}

		CheckerTexture(Texture* tex1, Texture* tex2) : even(tex1), odd(tex2){}

		CheckerTexture(Point col1, Point col2) :
			even(new SolidColour(col1)),
			odd(new SolidColour(col2)) {}

		Point value(double u, double v, const Point p) const override {
			double val = sin(10*p.x) * sin(10*p.y) * sin(10*p.z);
			if(val < 0) {
				return even->value(u, v, p);
			} else return odd->value(u, v, p);
		}

	private:
		Texture* even;
		Texture* odd;
	};

}

#endif