#include "Object.h"
#include <cmath>

namespace utils {

        Object::Object() {
            x = 0;
            y = 0;
            z = 0;
            type = 's';
            rad = 5;
            r = 200;
            g = 0;
            b = 0;
        }

        Object::Object(int rad, int x, int y, int z, int r, int g, int b) {
            this->rad = rad;
            this->x = x;
            this->y = y;
            this->z = z;
            this->r = r;
            this->g = g;
            this->b = b;
            type = 's';
        }

        Object::Object(int w, int h, int l, int x, int y, int z, int r, int g, int b) {
            // Implement rectangle
        }
}