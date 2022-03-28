#ifndef _LIGHT_H
#define _LIGHT_H

#include "Point.h"

using namespace utils;

namespace prims
{
    class Light
    {
        public:
            Point position;
            
            Point& biradiance(Point X);
        private:

    };
}

#endif