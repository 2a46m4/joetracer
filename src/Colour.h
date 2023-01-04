#ifndef COLOUR_H
#define COLOUR_H

// An RGB colour class.
#include "Point.h"
class ColourRGB {
 public:
  ColourRGB() : red(0), green(0), blue(0) {};
  
  ColourRGB(float r, float g, float b) : red(r), green(g), blue(b){};

  ColourRGB(Point3 p) : red(p(0)), green(p(1)), blue(p(2)) {};
  
  ColourRGB operator+(ColourRGB& colour);

  static ColourRGB pointToColour(const Point3&);

  static Point3 colourToPoint(const ColourRGB&);
  
  float red;
  float green;
  float blue;
};

#endif
