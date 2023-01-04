#ifndef _PERLIN_TEXTURE_H
#define _PERLIN_TEXTURE_H

#include "../Functions.h"
#include "../Point.h"
#include "../RandomGenerator.h"
#include "../Vector.h"
#include "SolidColour.h"
#include "Texture.h"
#include <cmath>
#include <iostream>

class PerlinTexture : public Texture {
public:
  PerlinTexture(int sc) {
    this->sc = sc;
    randomVectors = new Vector3[points];
    for (int i = 0; i < points; i++) {
      *(randomVectors + i) = Vector3(randomgen::randomNum(-1.0, 1.0),
                                     randomgen::randomNum(-1.0f, 1.0f),
                                     randomgen::randomNum(-1.0f, 1.0f))
                                 .normalized();
    }

    permX = perlinGeneratePermutation();
    permY = perlinGeneratePermutation();
    permZ = perlinGeneratePermutation();
  }

  double noise(const Point3 &p) const {
    double u = p.x() - floor(p.x());
    double v = p.y() - floor(p.y());
    double w = p.z() - floor(p.z());

    // Scaling for the perlin noise texture, and wrapping
    int i = (int)floor(p.x());
    int j = (int)floor(p.y());
    int k = (int)floor(p.z());

    Vector3 c[2][2][2];
    for (int di = 0; di < 2; di++) {
      for (int dj = 0; dj < 2; dj++) {
        for (int dk = 0; dk < 2; dk++) {
          // Generates pseudo-random vectors
          c[di][dj][dk] =
              randomVectors[permX[(i + di) & 255] ^ permY[(j + dj) & 255] ^
                            permZ[(k + dk) & 255]];
        }
      }
    }

    return perlinInterpolation(c, u, v, w);
  }

  Point3 value(double u, double v, const Point3 p) const override {
    return (1 + noise(sc * p)) / 2 * Point3(1, 1, 1);
  }

  ~PerlinTexture() {
    delete[] randomVectors;
    delete[] permX;
    delete[] permY;
    delete[] permZ;
  }

private:
  int sc;
  static const int points = 256;
  // The lattice of random values to be used (is tiled)
  Vector3 *randomVectors;

  // randomize x, y, z, hashing?
  int *permX;
  int *permY;
  int *permZ;

  // Given coordinates u, v, w, and gradient vector grid c, returns the
  // interpolated result
  static double perlinInterpolation(Vector3 c[2][2][2], double u, double v,
                                    double w) {
    double accumulation = 0;
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          // this is the vector away from the lattice point.. gets bigger as it
          // gets farther away from the point
          Vector3 weightV(u - i, v - j, w - k);
          accumulation +=
              (i * u + (1 - i) * (1 - u)) * (j * v + (1 - j) * (1 - v)) *
	    (k * w + (1 - k) * (1 - w)) * c[i][j][k].dot(weightV);
        }
      }
    }
    return accumulation;
  }

  static double trilinearInterpolation(double c[2][2][2], double u, double v,
                                       double w) {
    double accumulation = 0;
    // cubic hermite interpolation... need to read more on this
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);
    // I think this is the interpolation step, which basically interpolates
    // three dimensions according to their nearest grid
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          accumulation += (i * u + (1 - i) * (1 - u)) *
                          (j * v + (1 - j) * (1 - v)) *
                          (k * w + (1 - k) * (1 - w)) * c[i][j][k];
        }
      }
    }
    return accumulation;
  }

  // Generates a new permutation
  static int *perlinGeneratePermutation() {
    int *p = new int[points];

    for (int i = 0; i < points; i++)
      p[i] = i;

    permute(p);

    return p;
  }

  // Randomized the elements into a different permutation of the array
  static void permute(int *p) {
    for (int i = points - 1; i > 0; i--) {
      int target = randomgen::randomInt(0, i);
      int tmp = p[i];
      p[i] = p[target];
      p[target] = tmp;
    }
  }
};

#endif
