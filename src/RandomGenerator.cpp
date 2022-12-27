#include "RandomGenerator.h"
#include "Const.h"
#include <iostream>
#include <random>
#include <thread>

// fast prng
namespace randomgen {

thread_local static unsigned int seed = 12493048;

unsigned int xorShiftGenerator() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

// prng for floats between 0 and 1
float randomOne() { return (float)xorShiftGenerator() / (float)UINT_INF; }

// prng for floats between min and max, inclusive
float randomNum(float min, float max) {
  float num = (float)xorShiftGenerator() / (float)UINT_INF;
  return (num * (max - min)) + min;
}

// prng for ints between min and max, inclusive
int randomInt(int min, int max) {
  return (xorShiftGenerator() % (max + 1)) + min;
}

} // namespace joetracer
