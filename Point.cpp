#include "Point.h"
#include "Vec.h"
#include <cmath>

	Point::Point()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Point::Point(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Uses sqrt distance
	double Point::dist(Point p)
	{
		double a = (x - p.x) * (x - p.x);
		double b = (y - p.y) * (y - p.y);
		double c = (z - p.z) * (z - p.z);

		return sqrt(a + b + c);
	}

	Point Point::one()
	{
		return Point(1, 1, 1);
	}

	Point Point::zero()
	{
		return Point(0, 0, 0);
	}

	Point Point::char_max()
	{
		return Point(255, 255, 255);
	}

	Vec Point::direction()
	{
		return Vec(x, y, z);
	}

	const Vec Point::direction() const
	{
		return Vec(x, y, z);
	}

	Point Point::operator+(Point a)
	{
		return Point(x + a.x, y + a.y, z + a.z);
	}

	Point Point::operator-(Point a)
	{
		return Point(x - a.x, y - a.y, z - a.z);
	}

	Point Point::operator*(Point a)
	{
		return Point(x * a.x, y * a.y, z * a.z);
	}

	const Point Point::operator*(const Point &a) const
	{
		return Point(x * a.x, y * a.y, z * a.z);
	}

	bool Point::operator==(const Point &a) const
	{
		return ((x == a.x) && (y == a.y) && (z == a.z));
	}

	float &Point::operator[](int idx)
	{
		if (idx == 1)
		{
			return x;
		}
		else if (idx == 2)
		{
			return y;
		}
		else
		{
			return z;
		}
	}

	std::ostream &operator<<(std::ostream &out, const Point &point)
	{
		out << "Point(" << point.x << ", " << point.y << ", " << point.z << ')'; // actual output done here

		return out;
	}
