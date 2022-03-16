#ifndef _VEC_H
#define _VEC_H

namespace utils
{
    class Vec
    {
    public:
        double dx;
        double dy;
        double dz;

        Vec();

        Vec(double dx, double dy, double dz);

        Vec &operator=(const Vec &a);

        void sub(Vec a);

        void add(Vec a);

        void add(Vec a, Vec b);

        void scale(double m);

        Vec *getUnitVec();

        double length();

        double dotProduct(Vec a);

        Vec* crossProduct(Vec a);

        Vec* crossProduct(double dx, double dy, double dz);

        Vec reflection(double normal);
    };
}

#endif