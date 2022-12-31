// Materials
#include "Materials/Dielectrics.h"
#include "Materials/Emissive.h"
#include "Materials/Isotropic.h"
#include "Materials/Lambertian.h"
#include "Materials/Lambertian_ONB.h"
#include "Materials/Metal.h"


// Textures
#include "Textures/CheckerTexture.h"
#include "Textures/ImageTexture.h"
#include "Textures/PerlinTexture.h"
#include "Textures/SolidColour.h"

// Scene Functions and Primitives
#include "ConstantMedium.h"
#include "Hittable.h"
#include "Light.h"
#include "Move.h"
#include "PinholeCamera.h"
#include "Point.h"
#include "RandomGenerator.h"
#include "Rotation.h"
#include "Scene.h"
#include "Sphere.h"
#include "Translate.h"
#include "Vec3.h"
#include "aaBox.h"
#include "aaRect.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>

void addSampleScene(Scene &s) {
  Metal *mwhite = new Metal(Point(0.9, 0.9, 0.9), 0.5);
  Metal *mirror = new Metal(Point(0.9, 0.9, 0.9), 0.0);
  // Lambertian *lwhite = new Lambertian(Point(0.9, 0.9, 0.9));
  Lambertian *lchecker = new Lambertian(
      new CheckerTexture(Point(0.9, 0.9, 0.9), Point(0.7, 0, 0.7)));
  Metal *mgold = new Metal(Point(0.9, 0.9, 0.6), 0.2);
  Lambertian *lred = new Lambertian(Point(0.9, 0.0, 0.0));
  Lambertian *lblue = new Lambertian(Point(0.0, 0.0, 0.9));
  Dielectrics *glass = new Dielectrics(1.3);
  Lambertian *perlin = new Lambertian(new PerlinTexture(5));

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load("earthmap.jpg");
  if (loadedSurface == NULL) {
    printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
  }

  Lambertian *earth =
      new Lambertian(new ImageTexture(((unsigned char *)loadedSurface->pixels),
                                      loadedSurface->w, loadedSurface->h));
  Hittable *earthSphere2 = new Sphere(1, Point(1, 2, -10), earth);
  Hittable *earthSphere = new Sphere(2, Point(-10, 4, -40), glass);
  Hittable *metallicSphere = new Sphere(3, Point(-18, 6, -40), mwhite);
  Hittable *mirrorSphere = new Sphere(4, Point(-8, 18, -70), mirror);
  Hittable *glassSphere = new Sphere(5, Point(28, 10, -80), glass);
  Hittable *glassSphere2 = new Sphere(6, Point(-0, 12, -80), glass);
  Hittable *redSphere = new Sphere(7, Point(-30, 14, -60), lred);
  Hittable *blueSphere = new Sphere(8, Point(32, 16, -90), lblue);
  Hittable *goldSphere = new Sphere(9, Point(22, 18, -50), mgold);
  Hittable *ground = new Sphere(1100, Point(0, -1100.5, 0), lchecker);
  Hittable *perlinSphere = new Sphere(3, Point(2, 16, -30), perlin);
  Hittable *emitterSphere =
      new Sphere(3, Point(2, 8, -20), new Emissive(Point(255, 255, 255)));

  Hittable *cube = new Box(Point(-5, 0, -20), Point(-3, 2, -22), perlin);
  // cube = new Rotation(cube, Point(15, 0, 0));
  // cube = new Translate(cube, Vec3(-5, 5, -25));

  s.addObject(cube);
  s.addObject(earthSphere);
  s.addObject(earthSphere2);
  s.addObject(metallicSphere);
  s.addObject(mirrorSphere);
  s.addObject(glassSphere);
  s.addObject(glassSphere2);
  s.addObject(redSphere);
  s.addObject(blueSphere);
  s.addObject(goldSphere);
  s.addObject(ground);
  s.addObject(perlinSphere);
  s.addObject(emitterSphere);
  // s.camera.changeLocation(Point(0, 0, 0));
  // s.camera.changeView(Point(0, 0, -1));
}

void addDebugScene(Scene &s) {
  Lambertian *green = new Lambertian(Point(.12, .45, .15));
  Lambertian *red = new Lambertian(Point(.65, .05, .05));
  Lambertian *white = new Lambertian(Point(1, 1, 1));

  Emissive *emission = new Emissive(Point(500, 500, 500));

  Hittable *floor = new XZRectangle(-100, 100, -100, 100, -0.5, white, 0);
  Hittable *sphere = new Sphere(1, Point(1, 0.5, -5), green);
  Hittable *cube = new Box(Point(-1, -0.5, -6), Point(-0.5, 0, -5.5), red);

  cube = new Rotation(cube, Point(45, 0, 0));
  // cube = new Translate(cube, Vec3(-1, 1, 1));
  cube = new Move(cube, Point(-1, 1, -6));

  Hittable *light = new XZRectangle(-50, 50, -50, 50, 50, emission, 0);
  s.addObject(floor);
  s.addObject(light);
  s.addObject(sphere);
  s.addObject(cube);
}

void addCornellBox(Scene &s) {
  Lambertian_ONB *green = new Lambertian_ONB(Point(.12, .45, .15));
  Lambertian_ONB *red = new Lambertian_ONB(Point(.65, .05, .05));
  Lambertian_ONB *white = new Lambertian_ONB(Point(.73, .73, .73));
  Emissive *light = new Emissive(Point(10000, 10000, 10000));
  Emissive *lightbig = new Emissive(Point(1500, 1500, 1500));
  Dielectrics *glass = new Dielectrics(1.5);
  Metal *aluminum = new Metal(Point(0.8, 0.85, 0.88), 0.0);
  Lambertian_ONB *perlin = new Lambertian_ONB(new PerlinTexture(5));
  Lambertian *fogMat = new Lambertian(Point(0.73, 0.73, 0.73));

  // Left wall
  Hittable *rect1 = new YZRectangle(0, 555, -555, 0, 555, green, 1);
  // Right wall
  Hittable *rect2 = new YZRectangle(0, 555, -555, 0, 0, red, 0);
  // Lights
  Hittable *rect3 = new XZRectangle(213, 343, -332, -227, 554.5, light, 1);
  /* Hittable *rect3 = new XZRectangle(113, 443, -432, -127, 554, lightbig, 1); */
  s.setFocusable(rect3);
  // s.setFocusable(rect1);
  // Bottom wall (floor)
  Hittable *rect4 = new XZRectangle(0, 555, -555, 0, 0, white, 0);
  // Top wall
  Hittable *rect5 = new XZRectangle(0, 555, -555, 0, 555, white, 1);
  // Front wall
  Hittable *rect6 = new XYRectangle(0, 555, 0, 555, -555, white, 0);

  Hittable *rect7 = new XYRectangle(0, 555, 0, 555, 0, white, 0);

  Hittable *fogBoundary =
      new Box(Point(0, 0, -555), Point(555, 555, 0), fogMat);
  Point fogCol = Point(1, 1, 1);
  Hittable *fog = new ConstantMedium(fogBoundary, 0.001, fogCol);

  Hittable *testRect = new XYRectangle(0, 165, 0, 330, 0, white, 0);
  testRect = new Rotation(testRect, Point(-15, 0, 0));
  testRect = new Translate(testRect, Vec3(265, 0, -295));

  /* no rotation */
  // Hittable *box1 = new Box(Point(130, 0, -230), Point(295, 165, -65), white);
  // Hittable *box2 = new Box(Point(265, 0, -460), Point(430, 330, -295),
  // white);
  //

  Box *box1 = new Box(Point(0, 0, -165), Point(165, 330, 0), glass);
  Rotation *rbox = new Rotation(box1, Point(-15, 0, 0));
  Translate *tbox = new Translate(rbox, Vec3(265, 0, -295));
  Hittable *box2 = new Box(Point(0, 0, -165), Point(165, 165, 0), white);
  box2 = new Rotation(box2, Point(18, 0, 0));
  box2 = new Translate(box2, Vec3(130, 0, -65));

  Sphere *sphere = new Sphere(90, Point(190, 90, -190), red);
  // Hittable *sphere2 = new Sphere(90, Point(190, 1000, -190), light);

  s.addObject(rect1);
  s.addObject(rect2);
  s.addObject(rect3);
  s.addObject(rect4);
  s.addObject(rect5);
  s.addObject(rect6);
  s.addObject(rect7);
  // s.addObject(testRect);
  s.addObject(tbox);
  s.addObject(box1);
  s.addObject(box2);
  s.addObject(sphere);
  // s.addObject(fog);
}

void addTestScene(Scene &s) {
  Emissive *light = new Emissive(Point(10000, 10000, 10000));
  Lambertian_ONB *red = new Lambertian_ONB(Point(.65, .05, .05));
  
  Hittable *rect3 = new XZRectangle(213, 343, -332, -227, 554.5, light, 1);
  s.setFocusable(rect3);
  Sphere *sphere = new Sphere(90, Point(190, 90, -190), red);
  s.addObject(rect3);
  s.addObject(sphere);
}

