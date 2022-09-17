#ifndef _IMAGE_TEXTURE_H
#define _IMAGE_TEXTURE_H

#include "../Functions.h"
#include "../Point.h"
#include "SolidColour.h"
#include "Texture.h"
#include <cmath>
#include <iostream>

class ImageTexture : public Texture {
public:
  ImageTexture() {}

  ImageTexture(unsigned char *p, int _width, int _height)
      : pixels(p), width(_width), height(_height), pitch(3 * _width) {}

  Point value(double u, double v, const Point p) const override {
    if (pixels == nullptr)
      return Point(0, 1, 1);
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);

    int i = (int)(u * width);
    int j = (int)(v * height);

    if (i >= width)
      i = width - 1;
    if (j >= height)
      j = height - 1;

    unsigned char *pixel = pixels + (j * pitch) + (i * 3);
    return Point((float)pixel[0] / 255, (float)pixel[1] / 255,
                 (float)pixel[2] / 255);
  }

  ~ImageTexture() { delete pixels; }

private:
  unsigned char *pixels;
  int width;
  int height;
  int pitch;
};

#endif
