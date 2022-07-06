#ifndef _SCENE_H
#define _SCENE_H

#include "./BVHNode.h"
#include "./Functions.h"
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "./Vec.h"
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

  // unsigned char *pixels;

public:
  PinholeCamera camera;

  int samples = 12;
  int bounces = 4;
  Point background;

  Scene();

  Scene(int w, int h, PinholeCamera camera, Point background);

  unsigned char *render() const;

  // Inserts a pointer to a hittable object into the list
  void addObject(Hittable *o);

  void debugAddCube();

  void newCamera(PinholeCamera p);

  // Removes based on the id of the Object
  // True if success
  void removeObject(int i);

  void deleteScene();

  // Sphere stuff

  Point Colour(Ray r, int limit, BVHNode &sceneBox) const;

  std::vector<Hittable *> getObjects() const;

  int getWidth();

  int getHeight();

  HittableList* getHittables();
};

#endif
