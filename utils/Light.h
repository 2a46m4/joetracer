#ifndef _LIGHT_H
#define _LIGHT_H

#include "Point.h"

using namespace utils;

namespace prims
{
    class Light
    {
    public:
        Light(Point loc, float pow, Point col);

        Point biradiance(Point X);

        const Point biradiance(const Point X) const;

        Point &getPosition();
        
        const Point &getPosition() const;

    private:
        Point position;

        float power;

        Point colour;
    };
}

#endif