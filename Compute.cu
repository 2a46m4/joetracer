#include <stdio.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <thread>
#include <vector>
#include <unistd.h>

#include <curand.h>
#include <curand_kernel.h>

#include "Compute.h"
#include "Scene.h"
#include "./BVHNode.h"
#include "./Functions.h"
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Ray.h"
#include "./Sphere.h"
#include "./Vec.h"
#include "./PinholeCamera.h"

__global__ void deviceRender(unsigned int seed, Scene* s, BVHNode* box, unsigned char* pixels) {
  curandState_t state;

  curand_init(seed, blockIdx.x, 0, &state);

  float random = curand_uniform(&state);
  
  unsigned char rand = (unsigned char) random; 

  Ray r;
  Point col;
  
  pixels[blockIdx.x * 3 + ((s->getWidth() * 3) * blockIdx.y)]     = rand;
  pixels[blockIdx.x * 3 + ((s->getWidth() * 3) * blockIdx.y) + 1] = rand;
  pixels[blockIdx.x * 3 + ((s->getWidth() * 3) * blockIdx.y) + 2] = rand;
  
  // s.camera.getPrimaryRay()
}

unsigned char* GPUrender(const Scene s) {
  // this is probably really inefficient

  Scene scene = s;
  
  BVHNode box = BVHNode(*scene.getHittables(), 0, std::numeric_limits<float>::max());
  int size = scene.getHeight() * scene.getWidth() * 3;

  // device copies of needed structures
  unsigned char *gPixels;
  BVHNode* gBox;
  Scene* gScene;
  
  cudaMalloc((void **) &gPixels, size);
  cudaMalloc((void **) &gBox, sizeof(BVHNode));
  cudaMalloc((void **) &gScene, sizeof(Scene));

  cudaMemcpy(gScene, &s, sizeof(Scene), cudaMemcpyHostToDevice);
  cudaMemcpy(gBox, &box, sizeof(BVHNode), cudaMemcpyHostToDevice);
  // cudaMemcpy(gPixels, pixels, size, cudaMemcpyHostToDevice);

  dim3 numBlocks(scene.getWidth(), scene.getHeight());
  int threadsPerBlock = scene.samples;
  
  deviceRender<<<numBlocks, threadsPerBlock>>>(time(0), gScene, gBox, gPixels);  

  unsigned char* pixels = (unsigned char*)malloc(size);
  cudaMemcpy(pixels, gPixels, size, cudaMemcpyDeviceToHost);

  return pixels;
}
// #include "Scene.h"
// #include "./BVHNode.h"
// #include "./Functions.h"
// #include "./Hittable.h"
// #include "./Light.h"
// #include "./Point.h"
// #include "./Ray.h"
// #include "./Sphere.h"
// #include "./Vec.h"
// #include "PinholeCamera.h"

// #include <cmath>
// #include <iostream>
// #include <limits>
// #include <random>
// #include <thread>
// #include <vector>

// Scene::Scene() {
//   width = 1000;
//   height = 800; 
//   pixels = new unsigned char[height * width * 3];
// }

// Scene::Scene(int w, int h, PinholeCamera camera, Point background) {
//   width = w;
//   height = h;
//   this->camera = camera;
//   this->background = background;
//   pixels = new unsigned char[height * width * 3];
// }

// unsigned char *Scene::render() const {
//   if (hittables.objects.empty())
//     return NULL;
//   BVHNode box = BVHNode(hittables, 0, std::numeric_limits<float>::max());
// #pragma omp for
//     for (int y = 0; y < height; y++) {
//       for (int x = 0; x < width * 3; x += 3) {
//         Ray r;
//         Point col;

//         std::random_device device;
//         std::mt19937 gen(device());
//         std::uniform_real_distribution<> realrand(0, 1);

//         for (int i = 0; i < samples; i++) {
//           camera.getPrimaryRay(float(x / 3) + realrand(device),
//                                float(y) + realrand(device), r);
//           col = add(col, Colour(r, bounces, box));
//         }
//         // R channel
//         pixels[y * (width * 3) + x] =
//             (col.x / samples >= 255) ? 255 : col.x / samples;
//         // G channel
//         pixels[y * (width * 3) + x + 1] =
//             (col.y / samples >= 255) ? 255 : col.y / samples;
//         // B channel
//         pixels[y * (width * 3) + x + 2] =
//             (col.z / samples >= 255) ? 255 : col.z / samples;
//       }
//     }
//   return pixels;
// }

// void Scene::newCamera(PinholeCamera p) { camera = p; }

// std::vector<Hittable *> Scene::getObjects() const { return hittables.objects; }

// void Scene::removeObject(int i) {
//   if (i > hittables.objects.size())
//     ;
//   else
//     hittables.objects.erase(hittables.objects.begin() + i);
// }

// /*--------------- Sphere stuff ---------------*/

// Point Scene::Colour(Ray r, int limit, BVHNode &sceneBox) const {
//   hitRecord rec;

//   // Checks all objects
//   if (sceneBox.hit(r, rec, 0, std::numeric_limits<float>::max()) && limit > 0) {
//     Ray scattered;
//     Point attenuation; // surface value of the rendering equation
//     Point emitted = rec.matPtr->emitted(
//         rec.u, rec.v, rec.p); // emitted value of the rendering equation
//     if (!rec.matPtr->scatter(r, rec, attenuation, scattered)) {
//       return emitted; // returns the emitted value if the object doesn't scatter
//     }
//     return emitted + attenuation * Colour(scattered, limit - 1, sceneBox);
//   } else
//     return background;
// }

// void Scene::addObject(Hittable *o) { hittables.objects.push_back(o); }
