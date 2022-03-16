#ifndef _CAMERA_H
#define _CAMERA_H

#include "Point.h"
#include "Vec.h"

namespace utils
{

    typedef struct camera
    {
        // Location
        Point p;
        // Direction relative to the camera
        Vec v;
        int fov;
    } camera;

}

#endif