#include "Vec.h"
#include <cmath>

namespace utils
{

    Vec::Vec()
    {
        dx = 0;
        dy = 0;
        dz = 0;
    }

    Vec::Vec(double dx, double dy, double dz)
    {
        this->dx = dx;
        this->dy = dy;
        this->dz = dz;
    }

    Vec &Vec::operator=(const Vec &a)
    {
        dx = a.dx;
        dy = a.dy;
        dz = a.dz;
    }

    void Vec::sub(Vec a)
    {
        dx -= a.dx;
        dy -= a.dy;
        dz -= a.dz;
    }

    void Vec::add(Vec a)
    {
        dx += a.dx;
        dy += a.dy;
        dz += a.dz;
    }

    void Vec::add(Vec a, Vec b)
    {
        dx += a.dx + b.dx;
        dy += a.dy + b.dy;
        dz += a.dz + b.dz;
    }

    void Vec::scale(double m)
    {
        dx *= m;
        dy *= m;
        dz *= m;
    }

    Vec *Vec::getUnitVec()
    {
        Vec *r = new Vec();
        r->scale(1 / r->length());
        return r;
    }

    double Vec::length()
    {
        double a = dx * dx;
        double b = dy * dy;
        double c = dz * dz;

        return sqrt(a + b + c);
    }

    double Vec::dotProduct(Vec a)
    {
        return (dx * a.dx) + (dy * a.dy) + (dz * a.dz);
    }

    Vec *Vec::crossProduct(Vec a)
    {

        Vec *r = new Vec();

        r->dx = (dy * a.dz) - (dz * a.dy);
        r->dy = (dz * a.dx) - (dx * a.dz);
        r->dz = (dx * a.dy) - (dy * a.dx);

        return r;
    }

    Vec *Vec::crossProduct(double dx, double dy, double dz)
    {
        Vec *r = new Vec();

        r->dx = (this->dy * dz) - (this->dz * dy);
        r->dy = (this->dz * dx) - (this->dx * dz);
        r->dz = (this->dx * dy) - (this->dy * dx);

        return r;
    }

    Vec Vec::reflection(double normal)
    {
    }
}