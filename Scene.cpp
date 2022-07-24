#include "Scene.h"
#include "./BVHNode.h"
#include "./Functions.h"
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "./Vec.h"
#include "PinholeCamera.h"

#include "Compute.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>
#include <vector>

Scene::Scene() {
  width = 1000;
  height = 800;
  pixels = new unsigned char[height * width * 3];
}

Scene::Scene(int w, int h, PinholeCamera camera, Point background) {
  width = w;
  height = h;
  this->camera = camera;
  this->background = background;
  pixels = new unsigned char[height * width * 3];
}

unsigned char *Scene::render() const {

  BVHNode box = BVHNode(hittables, 0, FLT_INF);
// #pragma omp parallel for	
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width * 3; x += 3) {
      Ray r;
      Point col;

      std::random_device device;
      std::mt19937 gen(device());
      std::uniform_real_distribution<> realrand(0, 1);

      for (int i = 0; i < samples; i++) {
        camera.getPrimaryRay(float(x / 3) + realrand(device),
                             float(y) + realrand(device), r);
        col = add(col, Colour(r, bounces, box));
      }
      // R channel
      pixels[y * (width * 3) + x] =
          (col.x / samples >= 255) ? 255 : col.x / samples;
      // G channel
      pixels[y * (width * 3) + x + 1] =
          (col.y / samples >= 255) ? 255 : col.y / samples;
      // B channel
      pixels[y * (width * 3) + x + 2] =
          (col.z / samples >= 255) ? 255 : col.z / samples;
    }
  }
  return pixels;
}

void Scene::newCamera(PinholeCamera p) { camera = p; }

std::vector<Hittable *> Scene::getObjects() const { return hittables.objects; }

void Scene::removeObject(unsigned int i) {
  if (i < hittables.objects.size())
    hittables.objects.erase(hittables.objects.begin() + i);
}

Point Scene::Colour(Ray r, int limit, BVHNode &sceneBox) const {
  hitRecord rec;

  // Checks all objects
  if (sceneBox.hit(r, rec, 0, DBL_INF) && limit > 0) {
    Ray scattered;
    Point attenuation; // colour value of the ray
    Point emitted = rec.matPtr->emitted(
        rec.u, rec.v, rec.p); // emitted value of the rendering equation
    double pdf;
    Point albedo; // fractional reflectance value
    if (!rec.matPtr->scatter(r, rec, albedo, scattered, pdf)) {
      return emitted; // returns the emitted value if the object doesn't scatter
    }

    // Point lightPoint = Point(randomNum(T min, T max))

    // emission + fractional reflectance value * scattering PDF * colour of next
    // rays / what;  we are sampling the most of pdf

    Point colour =
        emitted +
        scale(1 / pdf,
              scale(rec.matPtr->scatteringPDF(r, rec, scattered), albedo) *
                  Colour(scattered, limit - 1, sceneBox));
    return colour;
  } else
    return background;
}

void Scene::addObject(Hittable *o) { hittables.objects.push_back(o); }

int Scene::getWidth() { return width; }

int Scene::getHeight() { return height; }

HittableList *Scene::getHittables() { return &hittables; }
