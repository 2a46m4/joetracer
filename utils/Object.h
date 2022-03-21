#ifndef _OBJECT_H
#define _OBJECT_H

#include "Point.h"

namespace utils
{
    class Object
    {
    public:
        Point location;
        int x;
        int y;
        int z;
        double specular = 0.2;
        double lambert = 0.7;
        double ambient = 0.1;
        int r;
        int g;
        int b;
        int rad;

        Object();

        Object(int rad, int x, int y, int z, int r, int g, int b);

        Object(int w, int h, int l, int x, int y, int z, int r, int g, int b);

    private:
        // type of Object.
        //  r : rectangle
        //  s : sphere
        char type;
    };
}

#endif