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

// GUI
#include "../include/imgui/backends/imgui_impl_sdl.h"
#include "../include/imgui/backends/imgui_impl_sdlrenderer.h"
#include "../include/imgui/imgui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>

// System libraries
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <cmath>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <eigen3/Eigen/src/Core/util/Constants.h>
#include <iostream>
#include <limits>

// Sample Scenes
#include "SampleScenes.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

// TODO hardcoded values, change
static int screenWidth = 1000;
static int screenHeight = 800;

void updateCamera(int x, int y, int z, int i, int j, int k, int fov, Scene &s) {
  s.newCamera(PinholeCamera(screenWidth, screenHeight, Vector3(x, y, z),
                            Vector3(i, j, k), fov));
  s.resetRaw();
}

// sdl boilerplate
int setupSDL() {
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
}

int main(int argc, char **argv) {

  // setupSDL();
  bool debug;
  debug = true;

  // demo window
  bool show_demo_window = true;
  // background color
  // ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
  ImVec4 clear_color = ImVec4(0, 0, 0, 1.0f);

  double *raw = new double[screenHeight * screenWidth * 3];

  // RGB Array of pixels
  unsigned char *pixels = new unsigned char[screenHeight * screenWidth * 3];

  SDL_Surface *surface = NULL;
  SDL_Texture *finalTexture = NULL;

  // Setup window
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
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

  Scene s;

  // our main rendering loop
  if (debug) {
    int x = 278;
    int y = 278;
    int z = 0;
    float i = -50;
    float j = 15;
    float k = 0;
    static float fov = 120.0f;

    s = Scene(screenWidth, screenHeight,
              PinholeCamera(screenWidth, screenHeight, Eigen::Vector3f(x, y, z),
                            Eigen::Vector3f(i, j, k), fov),
              Point3(clear_color.x * 255.0f, clear_color.y * 255.0f,
                     clear_color.z * 255.0f),
              raw);

    addTestScene(s);

    s.samples = 1;
    s.bounces = 4;

    int sampleCount = 0;
    s.createBVHBox();

    SDL_Event event;
    while (sampleCount < 2000) {
      sampleCount++;
      s.render();
      // quit the program
      while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
          sampleCount = 2000;
        else if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
          case SDLK_UP:
            i++;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_DOWN:
            i--;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_LEFT:
            j--;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_RIGHT:
            j++;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_w:
            z--;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_s:
            z++;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_a:
            x++;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_d:
            x--;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_i:
            y++;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          case SDLK_k:
            y--;
            updateCamera(x, y, z, i, j, k, fov, s);
            sampleCount = 0;
            break;
          default:
            break;
          }
        }
      }

      for (int i = 0; i < screenHeight * screenWidth * 3; i++) {
        pixels[i] = // truncates overbright values
            (s.raw[i] / sampleCount > 255) ? 255 : (s.raw[i] / sampleCount);
        // s.raw[i];
      }

      surface = SDL_CreateRGBSurfaceFrom((void *)pixels, screenWidth,
                                         screenHeight, 3 * 8, screenWidth * 3,
                                         0x0000ff, 0x00ff00, 0xff0000, 0);

      finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, finalTexture, NULL, NULL);
      SDL_RenderPresent(renderer);
      SDL_DestroyTexture(finalTexture);
    }
    SDL_SaveBMP(surface, "output.bmp");
    return 0;
  }

  // // Setup Dear ImGui context
  // IMGUI_CHECKVERSION();
  // ImGui::CreateContext();
  // ImGuiIO &io = ImGui::GetIO();
  // (void)io;
  // io.ConfigFlags |=
  //     ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // io.ConfigFlags |=
  //     ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // // Setup Dear ImGui style
  // ImGui::StyleColorsDark();

  // // Setup Platform/Renderer backends
  // ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  // ImGui_ImplSDLRenderer_Init(renderer);

  // // Main loop
  // bool quit = false;

  // while (!quit) {
  //   SDL_Event event;
  //   while (SDL_PollEvent(&event)) {
  //     ImGui_ImplSDL2_ProcessEvent(&event);
  //     if (event.type == SDL_QUIT)
  //       quit = true;
  //     if (event.type == SDL_WINDOWEVENT &&
  //         event.window.event == SDL_WINDOWEVENT_CLOSE &&
  //         event.window.windowID == SDL_GetWindowID(window))
  //       quit = true;
  //   }

  //   // Start the Dear ImGui frame
  //   ImGui_ImplSDLRenderer_NewFrame();
  //   ImGui_ImplSDL2_NewFrame();
  //   ImGui::NewFrame();

  //   if (show_demo_window)
  //     ImGui::ShowDemoWindow(&show_demo_window);

  //   {
  //     static float fov = 90.0f;
  //     ImGui::Begin("Settings");
  //     if (ImGui::Button("Render",
  //                       ImVec2(ImGui::GetWindowWidth() - 15, 20.0f))) {

  //       // s.background = Point(clear_color.x * 255.0f, clear_color.y * 255.0f,
  //                            // clear_color.z * 255.0f);
  //       // s.newCamera(
  //           // PinholeCamera(screenWidth, screenHeight, fov, location, lookingAt));
  //       // pixels = s.render();
  //       surface = SDL_CreateRGBSurfaceFrom((void *)pixels, screenWidth,
  //                                          screenHeight, 3 * 8, screenWidth * 3,
  //                                          0x0000ff, 0x00ff00, 0xff0000, 0);
  //       finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
  //       SDL_SaveBMP(surface, "output.bmp");
  //       SDL_FreeSurface(surface);
  //     }

  //     ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
  //     if (ImGui::BeginTabBar("Settings", tab_bar_flags)) {
  //       if (ImGui::BeginTabItem("Camera")) {
  //         const float CAM_MIN = -1000.0f;
  //         const float CAM_MAX = 1000.0f;
  //         const float FOV_MIN = 0.0f;
  //         const float FOV_MAX = 180.0f;
  //         // ImGui::DragScalarN("Location", ImGuiDataType_Float, &location, 3,
  //                            // 0.05f, &CAM_MIN, &CAM_MAX, "%f");
  //         // ImGui::DragScalarN("Looking at", ImGuiDataType_Float, &lookingAt, 3,
  //                            // 0.05f, &CAM_MIN, &CAM_MAX, "%f");
  //         ImGui::DragScalar("FOV", ImGuiDataType_Float, &fov, 0.005f, &FOV_MIN,
  //                           &FOV_MAX, "%f");
  //         ImGui::EndTabItem();
  //       }
  //       if (ImGui::BeginTabItem("Render")) {
  //         ImGui::DragInt("Samples", &s.samples, 0.5f, 0, 1000, "%d", 0);
  //         ImGui::DragInt("Bounces", &s.bounces, 0.5f, 0, 20, "%d", 0);
  //         ImGui::EndTabItem();
  //       }
  //       if (ImGui::BeginTabItem("Scene")) {
  //         if (ImGui::Button("Add Sample Scene")) {
  //           addSampleScene(s);
  //         }
  //         if (ImGui::Button("Add Cornell Box")) {
  //           addCornellBox(s);
  //         }

  //         ImGui::Text("Add Sphere");

  //         static int currentMaterial = 0;
  //         static ImVec4 colour = ImVec4(114.0f / 255.0f, 144.0f / 255.0f,
  //                                       154.0f / 255.0f, 200.0f / 255.0f);
  //         static float radius = 1.0f;
  //         static float slocation[3] = {0, 0, 1};
  //         ImGui::Combo("Material Type", &currentMaterial,
  //                      "Metal\0Diffuse\0Dielectric\0\0");
  //         Materials *m;
  //         static float fuzz = 0;
  //         static float rfidx = 1.3f;
  //         const float FUZZMAX = 1.0f;
  //         const float FUZZMIN = 0.0f;
  //         const float IDXMIN = 0.0f;
  //         const float IDXMAX = 3.0f;
  //         switch (currentMaterial) {
  //         case (0): // Metal

  //           ImGui::DragScalar("Fuzz", ImGuiDataType_Float, &fuzz, 0.005f,
  //                             &FUZZMIN, &FUZZMAX, "%f");
  //           break;
  //         case (1): // Diffuse
  //           break;
  //         case (2): // Dielectric

  //           ImGui::DragScalar("Refractive Index", ImGuiDataType_Float, &rfidx,
  //                             0.005f, &IDXMIN, &IDXMAX, "%f");
  //           break;
  //         }
  //         const float MIN = 0.0f;
  //         const float MAX = 1000.0f;

  //         ImGui::DragScalar("Radius", ImGuiDataType_Float, &radius, 0.05f, &MIN,
  //                           &MAX, "%f", ImGuiSliderFlags_Logarithmic);
  //         ImGui::DragScalarN("Location", ImGuiDataType_Float, &slocation, 3,
  //                            0.05f, &MIN, &MAX, "%f",
  //                            ImGuiSliderFlags_Logarithmic);
  //         ImGui::ColorEdit3("Sphere Colour##1", (float *)&colour);
  //         if (ImGui::Button("Add/Set New Material")) {
  //           switch (currentMaterial) {
  //           case (0): // Metal
  //             m = new Metal(Point(colour.x, colour.y, colour.z), fuzz);
  //             break;
  //           case (1): // Diffuse
  //             m = new Lambertian(Point(colour.x, colour.y, colour.z));
  //             break;
  //           case (2): // Dielectric
  //             m = new Dielectrics(1);
  //             break;
  //           }
  //         }
  //         if (ImGui::Button("Add Sphere")) {
  //           s.addObject(new Sphere(
  //               radius, Point(slocation[0], slocation[1], slocation[2]), m));
  //         }
  //         ImGui::ColorEdit3("Background", (float *)&clear_color);

  //         ImGui::EndTabItem();
  //       }
  //       ImGui::EndTabBar();
  //     }
  //     ImGui::Separator();
  //     ImGui::End();
  //   }

  //   // Rendering
  //   ImGui::Render();
  //   SDL_RenderClear(renderer);
  //   SDL_RenderCopy(renderer, finalTexture, NULL, NULL);

  //   ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
  //   SDL_RenderPresent(renderer);
  // }

  // // Cleanup
  // ImGui_ImplSDLRenderer_Shutdown();
  // ImGui_ImplSDL2_Shutdown();
  // ImGui::DestroyContext();

  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // SDL_Quit();

  // return 0;
}
