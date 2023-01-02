#include "Scene.h"
#include "./BVHNode.h"
#include "./Functions.h"
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "PinholeCamera.h"
#include "RandomGenerator.h"
#include "Vec3.h"
#include "pdf/HittablePDF.h"

#include "Compute.h"
#include "pdf/CosineONB_PDF.h"
#include "pdf/CosinePDF.h"
#include "pdf/MixturePDF.h"
#include <cmath>
#include <eigen3/Eigen/src/Core/Matrix.h>
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
  focusableList = new HittableList();
}

Scene::Scene(int w, int h, PinholeCamera camera, Point3 background) {
  width = w;
  height = h;
  this->camera = camera;
  this->background = background;
  pixels = new unsigned char[height * width * 3];
  focusableList = new HittableList();
}

Scene::Scene(int w, int h, PinholeCamera cam, Point3 bg, double *rawPixelPtr) {
  width = w;
  height = h;
  camera = cam;
  background = bg;
  raw = rawPixelPtr;
  pixels = new unsigned char[height * width * 3];
  focusableList = new HittableList();
}

void Scene::createBVHBox() { this->box = new BVHNode(hittables, 0, FLT_INF); }

// main rendering loop
void Scene::render() const {
#pragma omp parallel
  {
#pragma omp for nowait

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width * 3; x += 3) {
        Ray3 r;
        Point col;

        for (int i = 0; i < samples; i++) {
          camera.getPrimaryRay(float(x) / 3 + randomgen::randomOne(),
                               float(y) + randomgen::randomOne(), r);

          col = col + Point3ToPoint(Colour(r, bounces));
        }

        raw[y * (width * 3) + x] += col.x;
        raw[y * (width * 3) + x + 1] += col.y;
        raw[y * (width * 3) + x + 2] += col.z;
      }
    }
  }
}

void Scene::newCamera(PinholeCamera p) { camera = p; }

std::vector<Hittable *> Scene::getObjects() const { return hittables.objects; }

void Scene::removeObject(unsigned int i) {
  if (i < hittables.objects.size())
    hittables.objects.erase(hittables.objects.begin() + i);
}

// Given a ray and a bounce limit, returns the colour of the ray after its
// interaction with the scene.
Point3 Scene::Colour(Ray3 &r, int limit) const {
  hitRecord rec;

  // Checks for intersections
  if (limit > 0 && box->hit(r, rec, 0, DBL_INF)) {

    // Scattered ray
    Ray3 scattered;

    // Emission
    Point3 emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p, rec, r);

    // PDF of the ray
    double pdfValue;

    // Fractional reflectance value
    Point3 albedo;

    // The scatter record
    scatterRecord srec;

    // returns the emitted value if the object doesn't scatter
    if (!rec.matPtr->scatter(r, rec, srec))
      return emitted;

    // Specular ray. In this case, return the colour and the scattered ray,
    // since the PDF is infinite in the direction of the specular ray, and zero
    // everywhere else.
    if (srec.isSpecular) {
      delete srec.pdfptr;
      Point3 attentuation3 = PointToPoint3(srec.attenuation);
      Point3 col = Colour(srec.specularRay, limit - 1);

      return col.cwiseProduct(attentuation3);
    }

    // Generates a PDF that is 50/50 of the focusable list and the object being
    // hit
    HittablePDF focusablePDF(focusableList, PointToPoint3(rec.p));
    MixturePDF mixPDF(&focusablePDF, srec.pdfptr);
    scattered = Ray3(rec.p, mixPDF.generate());

    pdfValue = mixPDF.value(scattered.direction);

    delete srec.pdfptr;

    // emission + albedo * scattering PDF * colour of next
    // rays / sampling pdf

    Point3 colour =
        emitted +
        (rec.matPtr->scatteringPDF(
             r, rec, scattered) * // PDF of the scattered ray on the material
         srec.attenuation.cwiseProduct(      // generated colour
             Colour(scattered, limit - 1)) / // bounced rays
         pdfValue);                          // sampling pdf

    // Checks for INF/NAN values, discards them
    if (colour.x() != colour.x()) {
      colour.x() = 0;
    }
    if (colour.y() != colour.y()) {
      colour.y() = 0;
    }
    if (colour.z() != colour.z()) {
      colour.z() = 0;
    }

    return PointToPoint3(colour);
  } else // the ray hit nothing
    return background;
}

void Scene::addObject(Hittable *o) { hittables.objects.push_back(o); }

int Scene::getWidth() { return width; }

int Scene::getHeight() { return height; }

HittableList *Scene::getHittables() { return &hittables; }

void Scene::setFocusable(Hittable *focusable) {
  this->focusableList->add(focusable);
}
