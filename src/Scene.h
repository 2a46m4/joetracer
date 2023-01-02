#ifndef _SCENE_H
#define _SCENE_H

#include "./BVHNode.h"
#include "./Functions.h"
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "Colour.h"
#include "PinholeCamera.h"

#include <math.h>
#include <memory>
#include <utility>
#include <vector>

class Scene {

private:
  int height;
  int width;

  HittableList hittables;

  HittableList *focusableList;

  // A box that includes all items in the scene.
  BVHNode* box;

public:
  PinholeCamera camera;

  unsigned char *pixels;

  double *raw;

  int samples = 12;
  int bounces = 4;
  Point3 background;

  Scene();

  Scene(int w, int h, PinholeCamera camera, Point3 background);

  Scene(int w, int h, PinholeCamera cam, Point3 bg, double *rawPixelPtr);

  void createBVHBox();

  void render() const;

  // Inserts a pointer to a hittable object into the list
  void addObject(Hittable *o);

  void debugAddCube();

  void newCamera(PinholeCamera p);

  // Removes based on the id of the Object
  // True if success
  void removeObject(unsigned int i);

  void deleteScene();

  // Sphere stuff

  Point3 Colour(Ray3& r, int limit) const;

  std::vector<Hittable *> getObjects() const;

  int getWidth();

  int getHeight();

  HittableList *getHittables();

  void setFocusable(Hittable *);

  void resetRaw() {
    delete this->raw;
    raw = new double[height * width * 3];
  }
};

#endif
