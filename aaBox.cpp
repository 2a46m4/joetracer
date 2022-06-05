#include "aaBox.h"
#include "Point.h"
#include "Ray.h"
#include "aabb.h"
#include "aaRect.h"

// The two corners that define the box, and the material
Box::Box(const Point p0, const Point p1, Materials *mat)
{
	this->p0 = p0;
	this->p1 = p1;

	sides.add(new XYRectangle(p0.x, p1.x, p0.y, p1.y, p1.z, mat));
	sides.add(new XYRectangle(p0.x, p1.x, p0.y, p1.y, p0.z, mat));
	sides.add(new XZRectangle(p0.x, p1.x, p0.z, p1.z, p1.y, mat));
	sides.add(new XZRectangle(p0.x, p1.x, p0.z, p1.z, p0.y, mat));
	sides.add(new YZRectangle(p0.y, p1.y, p0.z, p1.z, p1.x, mat));
	sides.add(new YZRectangle(p0.y, p1.y, p0.z, p1.z, p0.x, mat));
}

// Takes ray to be examined, the interval tmin and tmax and returns if the ray has intersected the bounding box or not
bool Box::hit(const Ray &r, hitRecord &rec, double tMin, double tMax) const
{
	return sides.hit(r, rec, tMin, tMax);
}

bool Box::boundingBox(double t0, double t1, aabb &outputBox) const
{
	outputBox = aabb(p0, p1);
	return true;
}
