#include "PinholeCamera.h"
#include "./Functions.h"
#include "./Ray.h"

#include <iostream>

#define PI 3.14159265358979323846264338327950288419716939937510582097


PinholeCamera::PinholeCamera()
{
}

// http://fastgraph.com/makegames/3drotation/

// TODO: implement rotation matrices
PinholeCamera::PinholeCamera(int width, int height, float verticalFOV, Point location, Point view)
{
    this->verticalFOV = verticalFOV;
    this->location = location;
    this->view = view;
    this->width = width;
    this->height = height;

    // Reference
    vUp = Vec(0, 1, 0); 
	
    // Get u, v, w
    w = unitVec(sub(location, view).direction());
    u = unitVec(crossProduct(vUp, w));
    v = crossProduct(w, u);

    theta = verticalFOV * PI / 360.0f;
    h = tan(theta / 2);                                                                                     // dist from out vector to top of virtual plane
    viewportHeight = 2.0 * h;                                                                               // magnitude of the height
    viewportWidth = viewportHeight * width / height;                                                        // magnitude of the width
    horizontal = scale(viewportWidth, u);                                                                   // width scaled to the direction of the u vector
    vertical = scale(viewportHeight, v);                                                                    // height scaled to the direction of the v vector
    lowerLeftCorner = sub(location.direction(), add(w, add(scale(0.5, horizontal), scale(0.5, vertical)))); // add focal distance (currently w = 1 so focal distance is 1)

}

void PinholeCamera::getPrimaryRay(float x, float y, Ray &r) const
{

    // the scaling that depends on the fov of the camera; greater values means that the rays are projected farther away from the centre of the screen
    // const float side = -2 * tan(verticalFOV * PI / 360.0f);

    // float rot_mtx[4][4][4][4];
    // float trans_mtx[4][4][4][4];
    // std::cout << x << " " << width << std::endl;

    r.origin = location;
    r.direction = sub(add(lowerLeftCorner, add(scale(x / width, horizontal), scale((height  - y) / height, vertical))), location.direction()); 
}

void PinholeCamera::changeLocation(Point p) { location = p; }

void PinholeCamera::changeView(Point P) {
  view = P;
}
