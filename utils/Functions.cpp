#include "Functions.h"
#include <cmath>

using namespace utils;

namespace math
{
	Vec add3(Vec &a, Vec &b, Vec &c)
	{
		return Vec(a.x + b.x + c.z,
				   a.y + b.y + c.z,
				   a.z + b.z + c.z);
	}

	Vec unitVec(Vec &a)
	{
		return scale((1 / length(a)), a);
	}

	const Vec unitVec(const Vec &a)
	{
		return scale((1 / length(a)), a);
	}

	const double length(const Vec &a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	const double sqrlen(const Vec &a)
	{
		return a.x * a.x + a.y * a.y + a.z * a.z;
	}

	double length(Vec &a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	double dotProduct(const Vec &a, const Vec &b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	Point vecToPoint(Vec &a)
	{
		return Point(a.x, a.y, a.z);
	}

	Vec power(const Vec &a, int power)
	{
		Vec b = a;
		while (--power)
		{
			b.x *= a.x;
			b.y *= a.y;
			b.z *= a.z;
		}
		return b;
	}

	Point point(const Vec &a)
	{
		return Point(a.x, a.y, a.z);
	}

	// Schlick's approximation for the Fresnel factor between two media
	float schlick(const float cosine, const float refractIdx)
	{
		float r0 = (1 - refractIdx) / (1 + refractIdx);
		r0 *= r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

	// Returns a random ray for a perfect lambertian surface
	Vec randomRayInSphere(const Vec &n)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1, 1);
		Vec w;
		do
		{
			w = Vec(dis(gen), dis(gen), dis(gen));
		} while (math::length(w) >= 1.0);
		if (dotProduct(w, n) > 0.0) // in the same hemisphere as the normal
			return w;
		else
			return -w;
	}

	// Returns true if there is refraction (and not reflection), and finds the direction of the ray.
	Vec refract(const Vec &v, const Vec &n, float etaRatio)
	{
		double cosTheta = fmin(dotProduct(-v, n), 1.0);
		Vec rPerpen = scale(etaRatio, (add(v, scale(cosTheta, n))));
		Vec rParall = -(scale(sqrt(fabs(1.0 - (length(rPerpen) * length(rPerpen)))), n));
		return add(rParall, rPerpen);
	}

	double clamp(double val, double low, double high)
	{
		if (val > high)
			return high;
		if (val < low)
			return low;
		else
			return val;
	}

}
