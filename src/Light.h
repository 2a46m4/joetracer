#ifndef _LIGHT_H
#define _LIGHT_H

#include "./Point.h"

    class Light
    {
    public:
        Light(Point3 loc, float pow, Point3 col);

        Point3 biradiance(Point3 X);

        const Point3 biradiance(const Point3 X) const;

        Point3 &getPosition();
        
        const Point3 &getPosition() const;

    private:
        Point3 position;

        float power;

        Point3 colour;
    };


#endif
