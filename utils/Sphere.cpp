#include "Sphere.h"
#include "Point.h"
#include <cmath>

namespace utils {

        Sphere::Sphere() {
            type = 's';
            rad = 5;
            location = Point(0, 0, -5);
        }

        Sphere::Sphere(int rad, Point col, Point loc) {
            this->rad = rad;
            type = 's';
            location = loc;
            color = col;
        }
}