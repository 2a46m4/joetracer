#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Point.h"
#include "Surfel.h"
#include "Materials.h"

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

        // For now, we'll just assign a material to every triangle. Soon after we should assign it to every object instead
        // Materials material;

    private:
        

    };
}

#endif