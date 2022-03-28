#include "TriangleList.h"
#include "Point.h"
#include "Triangle.h"

namespace utils
{
    prims::Triangle TriangleList::triangle(int i) const
    {
        return prims::Triangle(
            vertexArray[indexArray[i * 3]],
            vertexArray[indexArray[i * 3 + 1]],
            vertexArray[indexArray[i * 3 + 2]]);
    }

    int TriangleList::size() const {
        return indexArray.size() / 3;
    }
}