#ifndef _VEC_H
#define _VEC_H

namespace utils
{
    class Vec
    {
    public:
        float x, y, z;

        Vec();

        Vec(const float dx, const float dy, const float dz);

        Vec operator-() const;
    };
}

#endif