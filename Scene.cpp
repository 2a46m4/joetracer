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
#include "RandomGenerator.h"
#include "pdf/HittablePDF.h"

#include "Compute.h"
#include "pdf/CosineONB_PDF.h"
#include "pdf/CosinePDF.h"
#include "pdf/MixturePDF.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>
#include <vector>

#include <SDL2/SDL.h>

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

Scene::Scene(int w, int h, PinholeCamera cam, Point bg, double *rawPixelPtr) {
  width = w;
  height = h;
  camera = cam;
  background = bg;
  raw = rawPixelPtr;
}

void Scene::createBVHBox() {
  box = new BVHNode(hittables, 0, FLT_INF); }

void Scene::render() const {
#pragma omp parallel for
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width * 3; x += 3) {
      Ray r;
      Point col;

      for (int i = 0; i < samples; i++) {
        camera.getPrimaryRay(float(x) / 3 + joetracer::randomOne(),
                             float(y) + joetracer::randomOne(),
                             r);
        col = add(col, Colour(r, bounces));
      }

      raw[y * (width * 3) + x] += col.x;
      raw[y * (width * 3) + x + 1] += col.y;
      raw[y * (width * 3) + x + 2] += col.z;

      // // R channel
      // pixels[y * (width * 3) + x] =
      //     (col.x / samples >= 255) ? 255 : col.x / samples;
      // // G channel
      // pixels[y * (width * 3) + x + 1] =
      //     (col.y / samples >= 255) ? 255 : col.y / samples;
      // // B channel
      // pixels[y * (width * 3) + x + 2] =
      //     (col.z / samples >= 255) ? 255 : col.z / samples;
    }
  }
}

void Scene::newCamera(PinholeCamera p) { camera = p; }

std::vector<Hittable *> Scene::getObjects() const { return hittables.objects; }

void Scene::removeObject(unsigned int i) {
  if (i < hittables.objects.size())
    hittables.objects.erase(hittables.objects.begin() + i);
}

Point Scene::Colour(Ray r, int limit) const {
  hitRecord rec;

  // Checks all objects
  if (limit > 0 && box->hit(r, rec, 0, DBL_INF)) {
    Ray scattered;
    Point attenuation; // colour value of the ray
    Point emitted = rec.matPtr->emitted(
        rec.u, rec.v, rec.p, rec, r); // emitted value of the rendering equation
    double pdfValue;
    Point albedo; // fractional reflectance value
    if (!rec.matPtr->scatter(r, rec, albedo, scattered, pdfValue)) {
      return emitted; // returns the emitted value if the object doesn't scatter
    }

    HittablePDF lightPDF(lights, rec.p);
    CosineONB_PDF cosinePDF(rec.normal);
    MixturePDF mixPDF(&cosinePDF, &lightPDF);
    scattered = Ray(rec.p, mixPDF.generate());
    pdfValue = mixPDF.value(scattered.direction);

    // scattered = Ray(rec.p, lightPDF.generate());
    // pdfValue = lightPDF.value(scattered.direction);

    // scattered = Ray(rec.p, cosinePDF.generate());
    // pdfValue = cosinePDF.value(scattered.direction);

    // emission + fractional reflectance value * scattering PDF * colour of next
    // rays / pdf

    // For matte objects the scattering pdf is cosine (things are most likely to
    // scatter around the middle) the other pdf is the probability that we
    // sample that direction (acts as scaling) In this case sampling pdf is the
    // same as scattering pdf

    // Point onLight =
    // Point(randomNum(213.0, 343.0), 554, randomNum(-332.0, -227.0));
    // Vec toLight = sub(onLight, rec.p).direction();
    // float distanceSquared = length(toLight) * length(toLight);
    // toLight = unitVec(toLight);

    // // if the ray is going up, we can hit either the light or the top black
    // box if (dotProduct(toLight, rec.normal) < 0)
    //   return emitted;

    // double lightArea = (343 - 213) * (332 - 227);
    // float lightCosine = fabs(toLight.y);
    // grazing edge
    // if (lightCosine < 0.000001)
    // return emitted;

    // pdfValue = distanceSquared / (lightCosine * lightArea);
    // scattered = Ray(rec.p, toLight);

    return emitted +
           scale(1 / pdfValue,
                 scale(rec.matPtr->scatteringPDF(r, rec, scattered), albedo) *
                     Colour(scattered, limit - 1));
  } else // the ray hit nothing
    return background;
}

void Scene::addObject(Hittable *o) { hittables.objects.push_back(o); }

int Scene::getWidth() { return width; }

int Scene::getHeight() { return height; }

HittableList *Scene::getHittables() { return &hittables; }

void Scene::setLight(Hittable *light) { lights = light; }
