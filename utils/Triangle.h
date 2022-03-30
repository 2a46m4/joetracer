#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Point.h"

using namespace utils;

namespace prims
{
    class Triangle
    {
    public:
        Triangle();
        
        Triangle(const Point &P0, const Point &P1, const Point &P2);

        // Input: 0 < i < 2
        const Point &vertex(int i) const;

        Point m_vertex[3];

    private:
    };
}

#endif