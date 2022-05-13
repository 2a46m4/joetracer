#include "Triangle.h"
#include "Point.h"

using namespace utils;

namespace prims
{
    Triangle::Triangle(){}

    Triangle::Triangle(const Point &P0, const Point &P1, const Point &P2)
    {
        m_vertex[0] = P0;
        m_vertex[1] = P1;
        m_vertex[2] = P2;
    }

    const Point &Triangle::vertex(int i) const
    {
        return m_vertex[i];
    }
}