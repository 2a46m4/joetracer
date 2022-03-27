#include "Vec.h"
#include <cmath>

namespace utils
{

    Vec::Vec()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vec::Vec(const float dx, const float dy, const float dz)
    {
        this->x = dx;
        this->y = dy;
        this->z = dz;
    }

    // Vec &Vec::operator=(const Vec &a)
    // {
    //     Vec b = Vec(a.x, a.y, a.z);
    //     return b;
    // }

}