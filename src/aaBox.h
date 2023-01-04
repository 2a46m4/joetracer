#ifndef _AA_BOX_H
#define _AA_BOX_H

#include <cmath>

#include "Point.h"
#include "Ray.h"
#include "Hittable.h"
#include "Ray.h"
#include "aaRect.h"

// Axis aligned rectangle
class Box : public Hittable
{
public:
	// The two corners that define the box, and the material
	Box(const Point3 p0, const Point3 p1, Materials *mat);

	// Takes ray to be examined, the interval tmin and tmax and returns if the ray has intersected the bounding box or not
	virtual bool hit(const Ray3 &r, hitRecord &rec, double tMin, double tMax) const override;

	virtual bool boundingBox(double t0, double t1, aabb &outputBox) const override;

private:
	Materials *mat;
	Point3 p0, p1;
	HittableList sides;
};

#endif 
