#include "RandomGenerator.h"
#include "Const.h"
#include <iostream>
#include <random>

namespace joetracer {

static unsigned int seed = 12493048;

  ;unsigned int xorShiftGenerator() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

float randomOne() { return (float)xorShiftGenerator() / (float)UINT_INF; }

float randomNum(float min, float max) {
  float num = (float)xorShiftGenerator() / (float)UINT_INF;
  return (num * (max - min)) + min;
}

int randomInt(int min, int max) {
  return (xorShiftGenerator() % (max + 1)) + min;
}

} // namespace joetracer
