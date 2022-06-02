#ifndef _PERLIN_TEXTURE_H
#define _PERLIN_TEXTURE_H

#include "../../utils/Point.h"
#include "Texture.h"
#include "SolidColour.h"
#include "../../utils/Functions.h"
#include <cmath>
#include <iostream>

using namespace utils;

namespace prims
{
	class PerlinTexture : public Texture
	{
	public:
		PerlinTexture()
		{
			randomFloat = new float[points];
			for (int i = 0; i < points; i++)
			{
				*(randomFloat + i) = math::randomNum(0.0f, 1.0f);
			}

			permX = perlinGeneratePermutation();
			permY = perlinGeneratePermutation();
			permZ = perlinGeneratePermutation();
		}

		double noise(const Point &p) const
		{
			int i = (int)(4 * p.x) & 255;
			int j = (int)(4 * p.y) & 255;
			int k = (int)(4 * p.z) & 255;
			return randomFloat[permX[i] ^ permY[j] ^ permZ[k]];
		}

		Point value(double u, double v, const Point p) const override
		{
			return math::scale(noise(math::scale(2, p)), Point(1, 1, 1));
		}

		~PerlinTexture()
		{
			delete[] randomFloat;
			delete[] permX;
			delete[] permY;
			delete[] permZ;
		}

	private:
		static const int points = 256;
		float *randomFloat;

		int *permX;
		int *permY;
		int *permZ;

		// Generates a new permutation
		static int *perlinGeneratePermutation()
		{
			int *p = new int[points];

			for (int i = 0; i < points; i++)
				p[i] = i;

			permute(p);

			return p;
		}

		// Randomized the elements into a different permutation of the array
		static void permute(int *p)
		{
			for (int i = points - 1; i > 0; i--)
			{
				int target = math::randomNum(0, i + 1);
				int tmp = p[i];
				p[i] = p[target];
				p[target] = tmp;
			}
		}
	};

}

#endif