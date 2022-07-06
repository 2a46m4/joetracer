// Scene Functions and Primitives
#include "./Hittable.h"
#include "./Light.h"
#include "./Point.h"
#include "./Sphere.h"
#include "./aaBox.h"
#include "./aaRect.h"
#include "Rotation.h"
#include "Scene.h"
#include "Translate.h"

// Materials
#include "./Materials/Dielectrics.h"
#include "./Materials/Emissive.h"
#include "./Materials/Lambertian.h"
#include "./Materials/Metal.h"

// Textures
#include "./Textures/CheckerTexture.h"
#include "./Textures/ImageTexture.h"
#include "./Textures/PerlinTexture.h"
#include "./Textures/SolidColour.h"

// GUI
#include "./gui/imgui/backends/imgui_impl_sdl.h"
#include "./gui/imgui/backends/imgui_impl_sdlrenderer.h"
#include "./gui/imgui/imgui.h"
#include "Vec.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

// System libraries
#include <iostream>
#include <limits>
#include <random>

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

static int screenWidth = 600;
static int screenHeight = 600;

void addSampleScene(Scene &s) {
  Metal *mwhite = new Metal(Point(0.9, 0.9, 0.9), 0.5);
  Metal *mirror = new Metal(Point(0.9, 0.9, 0.9), 0.0);
  Lambertian *lwhite = new Lambertian(Point(0.9, 0.9, 0.9));
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
  // cube = new Translate(cube, Vec(-5, 5, -25));

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
  s.camera.changeLocation(Point(0, 0, 0));
  s.camera.changeView(Point(0, 0, -1));
}

void addDebugScene(Scene &s) {
  Lambertian *green = new Lambertian(Point(.12, .45, .15));
  Lambertian *red = new Lambertian(Point(.65, .05, .05));
  Lambertian *white = new Lambertian(Point(1, 1, 1));

  Emissive *emission = new Emissive(Point(500, 500, 500));

  Hittable *floor = new XZRectangle(-100, 100, -100, 100, -0.5, white);
  Hittable *sphere = new Sphere(1, Point(1, 0.5, -5), green);
  Hittable *cube = new Box(Point(-1, -0.5, -6), Point(-0.5, 0, -5.5), red);

  Hittable *light = new XZRectangle(-20, 20, -20, 20, 20, emission);
  s.addObject(floor);
  s.addObject(light);
  s.addObject(sphere);
  s.addObject(cube);
}

void addCornellBox(Scene &s) {
  Lambertian *green = new Lambertian(Point(.12, .45, .15));
  Lambertian *red = new Lambertian(Point(.65, .05, .05));
  Lambertian *white = new Lambertian(Point(.73, .73, .73));
  Emissive *light = new Emissive(Point(4500, 4500, 4500));

  Hittable *rect1 = new YZRectangle(0, 555, -555, 0, 555, green);
  Hittable *rect2 = new YZRectangle(0, 555, -555, 0, 0, red);
  Hittable *rect3 = new XZRectangle(213, 343, -332, -227, 554, light);
  Hittable *rect4 = new XZRectangle(0, 555, -555, 0, 0, white);
  Hittable *rect5 = new XZRectangle(0, 555, -555, 0, 555, white);
  Hittable *rect6 = new XYRectangle(0, 555, 0, 555, -555, white);

  // Hittable *box1 = new Box(Point(130, 0, -230), Point(295, 165, -65), white);
  // box1 = new Rotation(box1, Point(15, 0, 0));
  // Hittable *box2 = new Box(Point(265, 0, -460), Point(430, 330, -295),
  // white); box2 = new Rotation(box2, Point(-18, 0, 0));

  Hittable *box1 = new Box(Point(0, 0, 0), Point(165, 330, 165), white);
  box1 = new Rotation(box1, Point(15, 0, 0));
  box1 = new Translate(box1, Vec(265, 0, -295));
  Hittable *box2 = new Box(Point(265, 0, -460), Point(430, 330, -295), white);
  box2 = new Rotation(box2, Point(-18, 0, 0));

  s.addObject(rect1);
  s.addObject(rect2);
  s.addObject(rect3);
  s.addObject(rect4);
  s.addObject(rect5);
  s.addObject(rect6);
  s.addObject(box1);
  s.addObject(box2);
}

int main(int argc, char **argv) {

  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
           IMG_GetError());
  }

  bool debug;
  // if (argc < 2) {
  // debug = false;
  // } else if (strcmp(argv[0], "debug")) {
  debug = true;
  // }

  // demo window
  bool show_demo_window = true;
  // background color
  // ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
  ImVec4 clear_color = ImVec4(0, 0, 0, 1.0f);
  static float x = 0;
  static float y = 0;
  static float z = 0;

  static float lx = 0;
  static float ly = 0;
  static float lz = 1;

  // Point location(278, 278, 800);
  // Point lookingAt(278, 278, 0); //

  Point location(1, 1, 1);
  Point lookingAt(0, 0, -5);

  Scene s = Scene(screenWidth, screenHeight,
                  PinholeCamera(screenWidth, screenHeight, 90.0f,
                                Point(x, y, z), Point(lx, ly, lz)),
                  Point(clear_color.x * 255.0f, clear_color.y * 255.0f,
                        clear_color.z * 255.0f));

  // RGB Array of pixels
  unsigned char *pixels;

  SDL_Surface *surface = NULL;
  SDL_Texture *finalTexture = NULL;

  if (debug) {
    // addCornellBox(s);
    // addSampleScene(s);
    addDebugScene(s);
    s.samples = 25;
    static float fov = 90.0f;

    s.background = Point(clear_color.x * 255.0f, clear_color.y * 255.0f,
                         clear_color.z * 255.0f);
    s.newCamera(
        PinholeCamera(screenWidth, screenHeight, fov, location, lookingAt));
    pixels = s.render();
    surface = SDL_CreateRGBSurfaceFrom((void *)pixels, screenWidth,
                                       screenHeight, 3 * 8, screenWidth * 3,
                                       0x0000ff, 0x00ff00, 0xff0000, 0);
    SDL_SaveBMP(surface, "output.bmp");
    SDL_FreeSurface(surface);
    return 0;
  }

  // Setup window
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI |
                        SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_Window *window = SDL_CreateWindow("JoeTracer", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, screenWidth,
                                        screenHeight, window_flags);

  // Setup SDL_Renderer instance
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("Error creating SDL_Renderer!");
    return -1;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer_Init(renderer);

  // Main loop
  bool quit = false;

  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        quit = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        quit = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    {
      static float fov = 90.0f;
      ImGui::Begin("Settings");
      if (ImGui::Button("Render",
                        ImVec2(ImGui::GetWindowWidth() - 15, 20.0f))) {

        s.background = Point(clear_color.x * 255.0f, clear_color.y * 255.0f,
                             clear_color.z * 255.0f);
        s.newCamera(
            PinholeCamera(screenWidth, screenHeight, fov, location, lookingAt));
        pixels = s.render();
        surface = SDL_CreateRGBSurfaceFrom((void *)pixels, screenWidth,
                                           screenHeight, 3 * 8, screenWidth * 3,
                                           0x0000ff, 0x00ff00, 0xff0000, 0);
        finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_SaveBMP(surface, "output.bmp");
        SDL_FreeSurface(surface);
      }

      ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
      if (ImGui::BeginTabBar("Settings", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Camera")) {
          const float CAM_MIN = -1000.0f;
          const float CAM_MAX = 1000.0f;
          const float FOV_MIN = 0.0f;
          const float FOV_MAX = 180.0f;
          ImGui::DragScalarN("Location", ImGuiDataType_Float, &location, 3,
                             0.05f, &CAM_MIN, &CAM_MAX, "%f");
          ImGui::DragScalarN("Looking at", ImGuiDataType_Float, &lookingAt, 3,
                             0.05f, &CAM_MIN, &CAM_MAX, "%f");
          ImGui::DragScalar("FOV", ImGuiDataType_Float, &fov, 0.005f, &FOV_MIN,
                            &FOV_MAX, "%f");
          ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Render")) {
          ImGui::DragInt("Samples", &s.samples, 0.5f, 0, 1000, "%d", 0);
          ImGui::DragInt("Bounces", &s.bounces, 0.5f, 0, 20, "%d", 0);
          ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Scene")) {
          if (ImGui::Button("Add Sample Scene")) {
            addSampleScene(s);
          }
          if (ImGui::Button("Add Cornell Box")) {
            addCornellBox(s);
          }

          ImGui::Text("Add Sphere");

          static int currentMaterial = 0;
          static ImVec4 colour = ImVec4(114.0f / 255.0f, 144.0f / 255.0f,
                                        154.0f / 255.0f, 200.0f / 255.0f);
          static float radius = 1.0f;
          static float slocation[3] = {0, 0, 1};
          ImGui::Combo("Material Type", &currentMaterial,
                       "Metal\0Diffuse\0Dielectric\0\0");
          Materials *m;
          static float fuzz = 0;
          static float rfidx = 1.3f;
          const float FUZZMAX = 1.0f;
          const float FUZZMIN = 0.0f;
          const float IDXMIN = 0.0f;
          const float IDXMAX = 3.0f;
          switch (currentMaterial) {
          case (0): // Metal

            ImGui::DragScalar("Fuzz", ImGuiDataType_Float, &fuzz, 0.005f,
                              &FUZZMIN, &FUZZMAX, "%f");
            break;
          case (1): // Diffuse
            break;
          case (2): // Dielectric

            ImGui::DragScalar("Refractive Index", ImGuiDataType_Float, &rfidx,
                              0.005f, &IDXMIN, &IDXMAX, "%f");
            break;
          }
          const float MIN = 0.0f;
          const float MAX = 1000.0f;

          ImGui::DragScalar("Radius", ImGuiDataType_Float, &radius, 0.05f, &MIN,
                            &MAX, "%f", ImGuiSliderFlags_Logarithmic);
          ImGui::DragScalarN("Location", ImGuiDataType_Float, &slocation, 3,
                             0.05f, &MIN, &MAX, "%f",
                             ImGuiSliderFlags_Logarithmic);
          ImGui::ColorEdit3("Sphere Colour##1", (float *)&colour);
          if (ImGui::Button("Add/Set New Material")) {
            switch (currentMaterial) {
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
          if (ImGui::Button("Add Sphere")) {
            s.addObject(new Sphere(
                radius, Point(slocation[0], slocation[1], slocation[2]), m));
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
