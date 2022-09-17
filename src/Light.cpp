#include "Light.h"
#include "./Point.h"
#include "./Functions.h"

#define PI 3.1415926535
    Light::Light(Point loc, float pow, Point col) {
        position = loc;
        power = pow;
        colour = col;
    }

    // The biradiance of the light at a given point
    Point Light::biradiance(Point X)
    {
        Vec v = sub(position, X).direction();
        float dist = length(v);
        float birad = power / (4 * PI * dist * dist);
        Point p = Point(birad * colour.x, birad * colour.y, birad * colour.z);
        return p;
    }

    // The biradiance of the light at a given point
    const Point Light::biradiance(const Point X) const
    {
        Vec v = sub(position, X).direction();
        float dist = length(v);
        float birad = power / (4 * PI * dist * dist);
        Point p = Point(birad * colour.x, birad * colour.y, birad * colour.z);
        return p;
    }

    Point &Light::getPosition()
    {
        return this->position;
    }
    
    const Point &Light::getPosition() const
    {
        return this->position;
    }
