// Scene Functions
#include "Scene.h"
#include "utils/Point.h"
#include "prims/Light.h"
#include "prims/Sphere.h"
#include "prims/Hittable.h"

// Materials
#include "prims/Materials/Lambertian.h"
#include "prims/Materials/Metal.h"
#include "prims/Materials/Dielectrics.h"

// Textures
#include "prims/Textures/CheckerTexture.h"
#include "prims/Textures/SolidColour.h"

// GUI
#include "gui/imgui/imgui.h"
#include "gui/imgui/backends/imgui_impl_sdl.h"
#include "gui/imgui/backends/imgui_impl_sdlrenderer.h"
#include <stdio.h>
#include <SDL2/SDL.h>

// System libraries
#include <limits>
#include <random>
#include <iostream>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

void addSampleScene(Scene &s)
{
	Metal *mwhite = new Metal(Point(0.9, 0.9, 0.9), 0.5);
	Lambertian *lwhite = new Lambertian(Point(0.9, 0.9, 0.9));
	Metal *mgold = new Metal(Point(0.9, 0.9, 0.6), 0.8);
	Lambertian *lred = new Lambertian(Point(0.9, 0.0, 0.0));
	Lambertian *lblue = new Lambertian(Point(0.0, 0.0, 0.9));
	Dielectrics *glass = new Dielectrics(1.3);

	prims::Hittable *metallicSphere = new prims::Sphere(2, Point(255, 255, 255), Point(-8, 2, -30), mwhite);

	prims::Hittable *glassSphere = new prims::Sphere(2, Point(255, 255, 255), Point(8, 2, -30), glass);

	prims::Hittable *glassSphere2 = new prims::Sphere(3, Point(255, 255, 255), Point(-0, 3, -15), glass);

	prims::Hittable *redSphere = new prims::Sphere(3, Point(255, 255, 255), Point(-3, 3, -30), lred);

	prims::Hittable *blueSphere = new prims::Sphere(3, Point(255, 255, 255), Point(3, 3, -30), lblue);

	prims::Hittable *goldSphere = new prims::Sphere(0.3, Point(255, 255, 255), Point(2, 2, -12), mgold);

	prims::Hittable *ground = new prims::Sphere(1100, Point(255, 255, 255), Point(0, -1100.5, -30), lwhite);

	s.addObject(metallicSphere);
	s.addObject(glassSphere);
	s.addObject(glassSphere2);
	s.addObject(redSphere);
	s.addObject(blueSphere);
	s.addObject(goldSphere);
	s.addObject(ground);
}

int main(int, char **)
{
	// Setup SDL
	// (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
	// depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Setup window
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window *window = SDL_CreateWindow("JoeTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

	// Setup SDL_Renderer instance
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_Log("Error creating SDL_Renderer!");
		return -1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	// Our state
	bool show_demo_window = true;
	// background color
	ImVec4 clear_color = ImVec4(0.40f, 0.58f, 0.70f, 1.00f);

	static float x = 0;
	static float y = 0;
	static float z = 0;

	static float lx = 0;
	static float ly = 0;
	static float lz = 1;

	Point location(0, 0, 0);
	Point lookingAt(0, 0, 1);

	// Scene *s = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT, PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f, location, lookingAt), Point(clear_color.x * 255.0f, clear_color.y * 255.0f, clear_color.z * 255.0f));

	Scene *s = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT, PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f, Point(x, y, z), Point(lx, ly, lz)), Point(clear_color.x * 255.0f, clear_color.y * 255.0f, clear_color.z * 255.0f));

	// RGB Array of pixels
	char *pixels;

	SDL_Surface *surface = NULL;
	SDL_Texture *finalTexture = NULL;

	// Main loop
	bool quit = false;
	while (!quit)
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				quit = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			static float fov = 90.0f;
			ImGui::Begin("Settings");
			if (ImGui::Button("Render", ImVec2(ImGui::GetWindowWidth() - 15, 20.0f)))
			{
				s->background = Point(clear_color.x * 255.0f, clear_color.y * 255.0f, clear_color.z * 255.0f);
				s->newCamera(PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, fov, location, lookingAt));
				pixels = s->render();
				surface = SDL_CreateRGBSurfaceFrom((void *)pixels,
												   SCREEN_WIDTH,
												   SCREEN_HEIGHT,
												   3 * 8,
												   SCREEN_WIDTH * 3,
												   0x0000ff,
												   0x00ff00,
												   0xff0000,
												   0);
				finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_SaveBMP(surface, "output.bmp");
				SDL_FreeSurface(surface);
			}

			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("Settings", tab_bar_flags))
			{
				if (ImGui::BeginTabItem("Camera"))
				{
					const float CAM_MIN = -1000.0f;
					const float CAM_MAX = 1000.0f;
					const float FOV_MIN = 0.0f;
					const float FOV_MAX = 180.0f;
					ImGui::DragScalarN("Location", ImGuiDataType_Float, &location, 3, 0.05f, &CAM_MIN, &CAM_MAX, "%f");
					ImGui::DragScalarN("Looking at", ImGuiDataType_Float, &lookingAt, 3, 0.05f, &CAM_MIN, &CAM_MAX, "%f");
					ImGui::DragScalar("FOV", ImGuiDataType_Float, &fov, 0.005f, &FOV_MIN, &FOV_MAX, "%f");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Render"))
				{
					ImGui::DragInt("Samples", &s->samples, 0.5f, 0, 1000, "%d", 0);
					ImGui::DragInt("Bounces", &s->bounces, 0.5f, 0, 20, "%d", 0);
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Scene"))
				{
					if (ImGui::Button("Add Sample Scene"))
					{
						addSampleScene(*s);
					}
					ImGui::Text("Add Sphere");

					static int currentMaterial = 0;
					static ImVec4 colour = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
					static float radius = 1.0f;
					static float slocation[3] = {0, 0, 1};
					ImGui::Combo("Material Type", &currentMaterial, "Metal\0Diffuse\0Dielectric\0\0");
					prims::Materials *m;
					static float fuzz = 0;
					static float rfidx = 1.3f;
					const float FUZZMAX = 1.0f;
					const float FUZZMIN = 0.0f;
					const float IDXMIN = 0.0f;
					const float IDXMAX = 3.0f;
					switch (currentMaterial)
					{
					case (0): // Metal

						ImGui::DragScalar("Fuzz", ImGuiDataType_Float, &fuzz, 0.005f, &FUZZMIN, &FUZZMAX, "%f");
						break;
					case (1): // Diffuse
						break;
					case (2): // Dielectric

						ImGui::DragScalar("Refractive Index", ImGuiDataType_Float, &rfidx, 0.005f, &IDXMIN, &IDXMAX, "%f");
						break;
					}
					const float MIN = 0.0f;
					const float MAX = 1000.0f;

					ImGui::DragScalar("Radius", ImGuiDataType_Float, &radius, 0.05f, &MIN, &MAX, "%f", ImGuiSliderFlags_Logarithmic);
					ImGui::DragScalarN("Location", ImGuiDataType_Float, &slocation, 3, 0.05f, &MIN, &MAX, "%f", ImGuiSliderFlags_Logarithmic);
					ImGui::ColorEdit3("Sphere Colour##1", (float *)&colour);
					if (ImGui::Button("Add/Set New Material"))
					{
						switch (currentMaterial)
						{
						case (0): // Metal
							m = new Metal(Point(colour.x, colour.y, colour.z), fuzz);
							break;
						case (1): // Diffuse
							m = new Lambertian(Point(colour.x, colour.y, colour.z));
							break;
						case (2): // Dielectric
							m = new Dielectrics(1);
							break;
						}
					}
					if (ImGui::Button("Add Sphere"))
					{
						s->addObject(new prims::Sphere(radius, Point(colour.x, colour.y, colour.z), Point(slocation[0], slocation[1], slocation[2]), m));
					}
					ImGui::ColorEdit3("Background", (float *)&clear_color);

					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::Separator();
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		// SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, finalTexture, NULL, NULL);

		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
