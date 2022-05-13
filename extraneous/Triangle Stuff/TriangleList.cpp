#include "TriangleList.h"
#include "Point.h"
#include "Triangle.h"

#include <algorithm>
#include <vector>

namespace utils
{
    // Zero-based index. Finds the ith triangle
    prims::Triangle TriangleList::triangle(int i) const
    {
        return prims::Triangle(
            vertexArray[indexArray[i * 3]],
            vertexArray[indexArray[i * 3 + 1]],
            vertexArray[indexArray[i * 3 + 2]]);
    }

    // Number of triangles in the list
    int TriangleList::size() const
    {
        return indexArray.size() / 3;
    }

    // Adds a new triangle to the list
    void TriangleList::addTriangle(prims::Triangle tri)
    {
        int i = 0;
        for (Point p : tri.m_vertex)
        {
            // Should consider using a map for this?
            const std::vector<Point>::iterator it = find(vertexArray.begin(), vertexArray.end(), p);
            if (it == vertexArray.end())
            {
                vertexArray.push_back(p);
                indexArray.push_back(vertexArray.size() - 1);
            }
            else 
            {
                indexArray.push_back(it - vertexArray.begin());
            }
        }
    }
}