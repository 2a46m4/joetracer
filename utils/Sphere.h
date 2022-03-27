#ifndef _SPHERE_H
#define _SPHERE_H

#include "Point.h"

namespace utils
{
    class Sphere
    {
    public:
        Point location;
        double specular = 0.2;
        double lambert = 0.7;
        double ambient = 0.1;
        Point color;
        int rad;

        Sphere();

        Sphere(int rad, Point col, Point loc);

    private:
        // type of Object.
        //  s : sphere
        char type;
    };
}

#endif