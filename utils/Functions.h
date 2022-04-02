#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "Vec.h"
#include "Point.h"
#include "VectorOps.h"
#include <random>
#include <cmath>

using namespace utils;

Vec randomRayInSphere()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1, 1);
    Vec w;
    do
    {
        w = Vec(dis(gen), dis(gen), dis(gen));
    } while (math::length(w) >= 1.0);
    return w;
}

#endif