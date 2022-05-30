#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../../utils/Point.h"

using namespace utils;

namespace prims
{
	class Texture
	{
	public:
		virtual Point value(double u, double v, const Point p) const = 0;
	};

}

#endif