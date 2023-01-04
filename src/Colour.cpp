#include "Colour.h"
#include "Point.h"

ColourRGB ColourRGB::operator+(ColourRGB& colour) {
  return ColourRGB(this->red + colour.red, this->green + colour.green, this->blue + colour.blue);
}

ColourRGB ColourRGB::pointToColour(const Point3& p) {
  return ColourRGB(p(0), p(1), p(2));
}
Point3 ColourRGB::colourToPoint(const ColourRGB& c) {
  return Point3(c.red, c.green, c.blue);
}
