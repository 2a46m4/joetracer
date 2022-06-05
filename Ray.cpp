#include "Ray.h"
#include "Point.h"
#include "Vec.h"
#include "Functions.h"
#include <cmath>
#include <iostream>

Ray::Ray()
{
	origin = Point();
	direction = Vec();
}

Ray::Ray(Point &origin, Vec &direction)
{
	this->origin = origin;
	this->direction = direction;
}

Ray::Ray(const Point &origin, const Vec &direction)
{
	this->origin = origin;
	this->direction = direction;
}

Point Ray::pointAtTime(float t) const
{
	return add(point(scale(t, direction)), origin);
}

std::ostream &operator<<(std::ostream &out, const Vec &point)
{
	std::cout << "Vector(" << point.x << ", " << point.y << ", " << point.z << ')'; // actual output done here

	return out;
}
