#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <limits>

#include <random>

#include "Scene.h"
#include "utils/Point.h"
#include "prims/Light.h"
#include "prims/Sphere.h"
#include "prims/Hittable.h"
#include "prims/Materials/Lambertian.h"
#include "prims/Materials/Metal.h"
#include "prims/Materials/Dielectrics.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "gui/nuklear/nuklear.h"
#include "gui/nuklear/nuklear_sdl_renderer.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const float FLOAT_MAX = std::numeric_limits<float>::max();
const float FLOAT_MIN = std::numeric_limits<float>::lowest();

using namespace std::chrono;

int main(int argc, char *args[])
{

    bool quit = false;

    // The window we'll be rendering to
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int flags = 0;

    // Initialize SDL
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // initialize nuklear
    struct nk_colorf background;
    struct nk_context *ctx;

    flags |= SDL_RENDERER_ACCELERATED;
    flags |= SDL_RENDERER_PRESENTVSYNC;

    // Create window
    window = SDL_CreateWindow("Joe Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, flags);
    if (renderer == NULL)
    {
        SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
        exit(-1);
    }

    // Initialize nuklear gui instance
    ctx = nk_sdl_init(window, renderer);
    {
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(&atlas);
        nk_sdl_font_stash_end();
        ;
    }

    background.r = 0.40f, background.g = 0.58f, background.b = 0.70f, background.a = 1.0f;
    int channels = 3;

    static float x = 0;
    static float y = 0;
    static float z = 0;

    static float lx = 0;
    static float ly = 0;
    static float lz = 1;

    static float fov = 90.0;

    char *pixels;

    static float sx = 0;
    static float sy = 0;
    static float sz = 0;

    static float sr = 0;
    static float sg = 0;
    static float sb = 0;

    static float r = 1;

    static float prop = 0;
    static float col = 0;

    struct nk_colorf sphereCol;
    sphereCol.r = 1;
    sphereCol.g = 0;
    sphereCol.b = 0;

    nk_color bgbyte = nk_rgb_cf(background);
    // Point(150, 170, 240)
    Scene *s = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT, PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f, Point(x, y, z), Point(lx, ly, lz)), Point(bgbyte.r, bgbyte.g, bgbyte.b));

    SDL_Surface *surface = NULL;
    SDL_Texture *finalTexture = NULL;

    while (!quit)
    {
        // Event handler
        SDL_Event e;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            nk_sdl_handle_event(&e);
        }

        nk_input_end(ctx);

        if (nk_begin(ctx, "Settings", nk_rect(50, 50, 700, 500),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                         NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {
            enum
            {
                EASY,
                HARD
            };
            static int op = EASY;

            nk_layout_row_dynamic(ctx, 30, 1);
            if (nk_button_label(ctx, "Render"))
            {
                auto start = high_resolution_clock::now();

                s->newCamera(PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, fov, Point(x, y, z), Point(lx, ly, lz)));
                pixels = s->render();
                surface = SDL_CreateRGBSurfaceFrom((void *)pixels,
                                                   SCREEN_WIDTH,
                                                   SCREEN_HEIGHT,
                                                   channels * 8,
                                                   SCREEN_WIDTH * channels,
                                                   0x0000ff,
                                                   0x00ff00,
                                                   0xff0000,
                                                   0);
                finalTexture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<milliseconds>(stop - start);
                std::cout << duration.count() << std::endl;
            }

            nk_layout_row_dynamic(ctx, 400, 2);
            if (nk_group_begin(ctx, "Camera settings", NK_WINDOW_BORDER))
            {
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Camera Settings", NK_TEXT_CENTERED);
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Location:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(ctx, 30, 3);
                nk_property_float(ctx, "#X:", FLOAT_MIN, &x, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Y:", FLOAT_MIN, &y, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Z:", FLOAT_MIN, &z, FLOAT_MAX, 5, 1);

                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Looking at:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(ctx, 30, 3);
                nk_property_float(ctx, "#X:", FLOAT_MIN, &lx, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Y:", FLOAT_MIN, &ly, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Z:", FLOAT_MIN, &lz, FLOAT_MAX, 5, 1);

                nk_property_float(ctx, "FOV:", 0, &fov, 120, 5, 1);
                nk_group_end(ctx);
            }

            if (nk_group_begin(ctx, "Add Spheres", NK_WINDOW_BORDER))
            {
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Scene Settings", NK_TEXT_CENTERED);
                nk_layout_row_dynamic(ctx, 30, 1);
                if (nk_button_label(ctx, "Add Sample Spheres"))
                {
                    Metal *mwhite = new Metal(Point(0.9, 0.9, 0.9), 0.5);
                    Lambertian *lwhite = new Lambertian(Point(0.9, 0.9, 0.9));
                    Metal *mgold = new Metal(Point(0.9, 0.9, 0.6), 0.8);
                    Lambertian *lgrey = new Lambertian(Point(0.5, 0.5, 0.5));
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

                    s->addObject(metallicSphere);
                    s->addObject(glassSphere);
                    s->addObject(glassSphere2);
                    s->addObject(redSphere);
                    s->addObject(blueSphere);
                    s->addObject(goldSphere);
                    s->addObject(ground);
                }
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Add Sphere", NK_TEXT_ALIGN_LEFT);
                static const char *material[] = {"Metal", "Lambertian", "Dielectric"}; // The options we want to display
                static int selected_item_index = 0;                                    // Selected item index
                struct nk_vec2 size = {100, 100};                                      // Size of the dropdown that displays all our items
                nk_layout_row_dynamic(ctx, 30, 2);
                nk_combobox(ctx, material, 3, &selected_item_index, 20, size);
                switch (selected_item_index)
                {
                case (0): // Metal
                    nk_layout_row_dynamic(ctx, 30, 2);
                    nk_property_float(ctx, "Fuzz:", 0, &prop, 1, 0.1, 0.2);
                    if (nk_combo_begin_color(ctx, nk_rgb_cf(sphereCol), nk_vec2(nk_widget_width(ctx), 400)))
                    {
                        nk_layout_row_dynamic(ctx, 120, 1);
                        sphereCol = nk_color_picker(ctx, sphereCol, NK_RGB);
                        nk_layout_row_dynamic(ctx, 25, 1);
                        sphereCol.r = nk_propertyf(ctx, "#R:", 0, sphereCol.r, 1.0f, 0.01f, 0.005f);
                        sphereCol.g = nk_propertyf(ctx, "#G:", 0, sphereCol.g, 1.0f, 0.01f, 0.005f);
                        sphereCol.b = nk_propertyf(ctx, "#B:", 0, sphereCol.b, 1.0f, 0.01f, 0.005f);
                        nk_combo_end(ctx);
                    }
                    break;
                case (1): // Lambertian
                    if (nk_combo_begin_color(ctx, nk_rgb_cf(sphereCol), nk_vec2(nk_widget_width(ctx), 400)))
                    {
                        nk_layout_row_dynamic(ctx, 120, 1);
                        sphereCol = nk_color_picker(ctx, sphereCol, NK_RGB);
                        nk_layout_row_dynamic(ctx, 25, 1);
                        sphereCol.r = nk_propertyf(ctx, "#R:", 0, sphereCol.r, 1.0f, 0.01f, 0.005f);
                        sphereCol.g = nk_propertyf(ctx, "#G:", 0, sphereCol.g, 1.0f, 0.01f, 0.005f);
                        sphereCol.b = nk_propertyf(ctx, "#B:", 0, sphereCol.b, 1.0f, 0.01f, 0.005f);
                        nk_combo_end(ctx);
                    }
                    break;
                case (2): // Dielectric
                    nk_layout_row_dynamic(ctx, 30, 1);
                    nk_property_float(ctx, "Refractive Index:", 0, &prop, 100, 0.1, 0.2);
                    break;
                }
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_property_float(ctx, "#Radius:", 0, &r, FLOAT_MAX, 5, 1);
                nk_layout_row_dynamic(ctx, 30, 1);
                nk_label(ctx, "Location:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(ctx, 30, 3);
                nk_property_float(ctx, "#X:", FLOAT_MIN, &sx, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Y:", FLOAT_MIN, &sy, FLOAT_MAX, 5, 1);
                nk_property_float(ctx, "#Z:", FLOAT_MIN, &sz, FLOAT_MAX, 5, 1);
                nk_layout_row_dynamic(ctx, 30, 1);
                if (nk_button_label(ctx, "Add Sphere"))
                {
                    switch (selected_item_index)
                    {
                    case (0): // Metal
                    {
                        s->addObject(new prims::Sphere(r, Point(0, 0, 0), Point(sx, sy, sz), new Metal(Point(sphereCol.r, sphereCol.g, sphereCol.b), prop)));
                        break;
                    }
                    case (1): // Lambertian
                    {
                        s->addObject(new prims::Sphere(r, Point(0, 0, 0), Point(sx, sy, sz), new Lambertian(Point(sphereCol.r, sphereCol.g, sphereCol.b))));
                        break;
                    }
                    case (2): // Dielectric
                    {
                        s->addObject(new prims::Sphere(r, Point(0, 0, 0), Point(sx, sy, sz), new Dielectrics(prop)));
                        break;
                    }
                    }
                }
                nk_group_end(ctx);
            }

            // nk_layout_row_dynamic(ctx, 30, 2);
            // if (nk_option_label(ctx, "easy", op == EASY))
            //     op = EASY;
            // if (nk_option_label(ctx, "hard", op == HARD))
            //     op = HARD;
            // nk_layout_row_dynamic(ctx, 25, 1);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_combo_begin_color(ctx, nk_rgb_cf(background), nk_vec2(nk_widget_width(ctx), 400)))
            {
                nk_layout_row_dynamic(ctx, 120, 1);
                background = nk_color_picker(ctx, background, NK_RGB);
                nk_layout_row_dynamic(ctx, 25, 1);
                background.r = nk_propertyf(ctx, "#R:", 0, background.r, 1.0f, 0.01f, 0.005f);
                background.g = nk_propertyf(ctx, "#G:", 0, background.g, 1.0f, 0.01f, 0.005f);
                background.b = nk_propertyf(ctx, "#B:", 0, background.b, 1.0f, 0.01f, 0.005f);
                bgbyte = nk_rgb_cf(background);
                s->changeBackground(Point(bgbyte.r, bgbyte.g, bgbyte.b));
                nk_combo_end(ctx);
            }
        }
        nk_end(ctx);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, finalTexture, NULL, NULL);

        nk_sdl_render(NK_ANTI_ALIASING_ON);

        SDL_RenderPresent(renderer);
    }

    // Shut down nuklear
    nk_sdl_shutdown();

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
