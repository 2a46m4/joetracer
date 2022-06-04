#include "Scene.h"
#include "./Point.h"
#include "./Vec.h"
#include "./Sphere.h"
#include "PinholeCamera.h"
#include "./Functions.h"
#include "./Light.h"
#include "./Ray.h"
#include "./Hittable.h"
#include "./BVHNode.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <random>
#include <thread>

Scene::Scene()
{
	width = 1000;
	height = 800;
	pixels = new unsigned char[height * width * 3];
}

Scene::Scene(int w, int h, PinholeCamera camera, Point background)
{
	width = w;
	height = h;
	this->camera = camera;
	this->background = background;
	pixels = new unsigned char[height * width * 3];
}

unsigned char *Scene::render() const
{
	if (hittables.objects.empty())
		return NULL;
	BVHNode box = BVHNode(hittables, 0, std::numeric_limits<float>::max());
	// for(auto hittable : hittables.objects) {
	// 	aabb test;
	// 	hittable->boundingBox(0, std::numeric_limits<double>::max(), test);
	// 	std::cout << (test.max.x - test.min.x) / 2 << ", " << (test.max.y - test.min.y) / 2 << ", " << (test.max.z - test.min.z) / 2 << std::endl;
	// }
#pragma omp parallel
	{
#pragma omp for
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width * 3; x += 3)
				{
					Ray r;
					Point col;

					std::random_device device;
					std::mt19937 gen(device());
					std::uniform_real_distribution<> realrand(0, 1);

					for (int i = 0; i < samples; i++)
					{
						camera.getPrimaryRay(float(x / 3) + realrand(device), float(y) + realrand(device), r);
						col = add(col, Colour(r, bounces, box));
					}
					// R channel
					pixels[y * (width * 3) + x] = (sqrt(col.x / samples / 255)) * 255;
					// G channel
					pixels[y * (width * 3) + x + 1] = (sqrt(col.y / samples / 255)) * 255;
					// B channel
					pixels[y * (width * 3) + x + 2] = (sqrt(col.z / samples / 255)) * 255;
				}
			}
		}
	}
	return pixels;
}

void Scene::newCamera(PinholeCamera p)
{
	camera = p;
}

void Scene::addLight(Light p)
{
	lights.push_back(p);
}

std::vector<Hittable *> Scene::getObjects() const
{
	return hittables.objects;
}

void Scene::removeObject(int i)
{
	if (i > hittables.objects.size())
		;
	else
		hittables.objects.erase(hittables.objects.begin() + i);
}

bool Scene::removeLight(int i)
{
	if (i > lights.size())
		return false;
	else
	{
		lights.erase(lights.begin() + i);
		return true;
	}
}

const std::vector<Light> Scene::getLights() const
{
	return lights;
}

/*--------------- Sphere stuff ---------------*/

Point Scene::Colour(Ray r, int limit, BVHNode &sceneBox) const
{
	hitRecord rec;

	// Checks all objects
	if (sceneBox.hit(r, rec, 0, std::numeric_limits<float>::max()) && limit > 0)
	{
		Ray scattered;
		Point attenuation;																				// surface value of the rendering equation
		Point emitted = rec.matPtr->emitted(rec.u, rec.v, rec.p); // emitted value of the rendering equation
		if (!rec.matPtr->scatter(r, rec, attenuation, scattered)) {
			// std::cout << emitted << std::endl;
			return emitted; // returns the emitted value if the object doesn't scatter

		}
		return emitted + attenuation * Colour(scattered, limit - 1, sceneBox);
	}
	else
		return background;
}

void Scene::addObject(Hittable *o)
{
	hittables.objects.push_back(o);
}