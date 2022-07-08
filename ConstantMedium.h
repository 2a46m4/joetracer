#ifndef _CONSTANT_MEDIUM_H
#define _CONSTANT_MEDIUM_H

#include "Hittable.h"
#include "Textures/Texture.h"

// A hittable object composed of a constant density medium. Light is able to pass through but scatters inside. 
class ConstantMedium : public Hittable {
   public:
  ConstantMedium(Hittable* hittablePtr, double d, Texture* texturePtr) {
    boundary = hittablePtr;
    negativeInvertedDensity = -1 / d;
    phaseFunction = new Isotropic(texturePtr);
  }

  ConstantMedium(Hittable* hittablePtr, double d, Point* col) {
    
  }
  
  Materials* phaseFunction;
  Hittable* boundary;
  double negativeInvertedDensity;
}

#endif
