#ifndef _TRIANGLE_LIST_H
#define _TRIANGLE_LIST_H

#include <vector>

#include "Point.h"
#include "Triangle.h"

namespace utils
{
    class TriangleList
    {
    public:

        prims::Triangle triangle(int i) const;

        // Number of triangles
        int size() const;

        std::vector<Point> vertexArray;
        std::vector<int> indexArray;

        void addTriangle(prims::Triangle tri); 

    private:
        // int vertexIterator = 0;
        // int indexIterator = 0;

        // Using vectors for now, could switch to map
        // std::unordered_map<int, Point> vertexMap;

        // // Limit: 30000 indexes
        // int indexArray[30000];

        // // Pushes back the point vertex
        // void vertexPushBack(Point p);

        // // Pops back the point vertex
        // Point vertexPopBack();

        // // Pushes back the 3 locations through a point
        // void indexPushBack(Point i);

        // // Pops back the 3 locations through a point
        // Point indexPopBack();
    };
}

#endif