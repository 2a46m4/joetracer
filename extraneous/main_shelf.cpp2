#include <SDL2/SDL.h>
#include <SDL_mouse.h>
#include <SDL_keyboard.h>
#include <iostream>
#include <chrono>
#include <limits>

#include <random>

#include "Scene.h"
#include "utils/Point.h"
#include "utils/Light.h"
#include "utils/Sphere.h"
#include "utils/Hittable.h"
#include "utils/Materials/Lambertian.h"
#include "utils/Materials/Metal.h"
#include "utils/Materials/Dielectrics.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_SOFTWARE_FONT
#include "gui/nuklear/nuklear.h"
#define NK_SDLSURFACE_IMPLEMENTATION
#include "gui/nuklear/sdl2surface_rawfb.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const float FLOAT_MAX = std::numeric_limits<float>::max();
const float FLOAT_MIN = std::numeric_limits<float>::lowest();

using namespace std::chrono;

static nk_keys translate_sdl_key(struct SDL_Keysym const *k)
{
    // switch(k)
    // {
    //     default:

    //     case SDL_KEYDOWN:
    //         return NK_KEY_DOWN;
    //         break;
    // }

    NK_UNUSED(k);

    return NK_KEY_NONE;
}

static nk_buttons sdl_button_to_nk(int button)
{
    switch (button)
    {
    default:
    /* ft */
    case SDL_BUTTON_LEFT:
        return NK_BUTTON_LEFT;
        break;
    case SDL_BUTTON_MIDDLE:
        return NK_BUTTON_MIDDLE;
        break;
    case SDL_BUTTON_RIGHT:
        return NK_BUTTON_RIGHT;
        break;
    }
}

int main(int argc, char *args[])
{

    bool quit = false;

    // The window we'll be rendering to
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    struct nk_color clear = {0, 100, 0, 255};
    struct nk_vec2 vec;
    struct nk_rect bounds = {40, 40, 0, 0};
    struct sdlsurface_context *context;

    SDL_DisplayMode dm;

    // Not using main arguments
    NK_UNUSED(argc);
    NK_UNUSED(args);

    int flags = 0;

    // The surface contained by the window
    // SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GetDesktopDisplayMode(0, &dm);

    // initialize nuklear
    struct nk_colorf background;

    // flags |= SDL_RENDERER_ACCELERATED;
    // flags |= SDL_RENDERER_PRESENTVSYNC;

    // Create SDL window
    window = SDL_CreateWindow("Joe Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, flags);
    if (renderer == NULL)
    {
        SDL_Log("Error SDL_CreateRenderer %s", SDL_GetError());
        exit(-1);
    }

    background.r = 0.40f, background.g = 0.58f, background.b = 0.70f, background.a = 1.0f;

    // // Get window surface
    // screenSurface = SDL_GetWindowSurface(window);

    SDL_Surface *surface = NULL;

    context = nk_sdlsurface_init(surface, 13.0f);

    // // s->debugAddCube();
    // s->addLight(prims::Light(Point(0, 2, -5), 1000.0, Point(255, 255, 255)));
    // s->addLight(prims::Light(Point(0, 0, 0), 1000.0, Point(255, 255, 255)));
    // s->addLight(prims::Light(Point(0, 2, -10), 1000.0, Point(255, 255, 255)));
    int channels = 3;

    // auto start = high_resolution_clock::now();
    // auto stop = high_resolution_clock::now();

    // auto duration = duration_cast<milliseconds>(stop - start);
    // std::cout << duration.count() << std::endl;

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
    Point _sphereCol;

    nk_color bgbyte = nk_rgb_cf(background);
    // Point(150, 170, 240)
    Scene *s = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT, PinholeCamera(SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f, Point(x, y, z), Point(lx, ly, lz)), Point(bgbyte.r, bgbyte.g, bgbyte.b));

    
    SDL_Texture *finalTexture = NULL;

    while (!quit)
    {
        // Event handler
        SDL_Event e;
        nk_input_begin(&(context->ctx));
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                nk_input_key(&(context->ctx), translate_sdl_key(&e.key.keysym), 1);
                break;
            case SDL_KEYUP:
                nk_input_key(&(context->ctx), translate_sdl_key(&e.key.keysym), 0);
                break;
            case SDL_MOUSEMOTION:
                nk_input_motion(&(context->ctx), e.motion.x, e.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                nk_input_button(&(context->ctx), (nk_buttons) sdl_button_to_nk(e.button.button), e.button.x, e.button.y, 1);
                break;
            case SDL_MOUSEBUTTONUP:
                nk_input_button(&(context->ctx), (nk_buttons) sdl_button_to_nk(e.button.button), e.button.x, e.button.y, 0);
                break;
            case SDL_MOUSEWHEEL:
                vec.x = e.wheel.x;
                vec.y = e.wheel.y;
                nk_input_scroll(&(context->ctx), vec);

                break;
            }
        }

        nk_input_end(&(context->ctx));

        if (nk_begin(&(context->ctx), "Settings", nk_rect(50, 50, 700, 500),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                         NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {
            enum
            {
                EASY,
                HARD
            };
            static int op = EASY;

            nk_layout_row_dynamic(&(context->ctx), 30, 1);
            if (nk_button_label(&(context->ctx), "Render"))
            {
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
            }

            nk_layout_row_dynamic(&(context->ctx), 400, 2);
            if (nk_group_begin(&(context->ctx), "Camera settings", NK_WINDOW_BORDER))
            {
                nk_layout_row_dynamic(&(context->ctx), 30, 1);
                nk_label(&(context->ctx), "Camera Settings", NK_TEXT_CENTERED);
                nk_layout_row_dynamic(&(context->ctx), 30, 1);
                nk_label(&(context->ctx), "Location:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(&(context->ctx), 30, 3);
                nk_property_float(&(context->ctx), "#X:", FLOAT_MIN, &x, FLOAT_MAX, 5, 1);
                nk_property_float(&(context->ctx), "#Y:", FLOAT_MIN, &y, FLOAT_MAX, 5, 1);
                nk_property_float(&(context->ctx), "#Z:", FLOAT_MIN, &z, FLOAT_MAX, 5, 1);

                nk_layout_row_dynamic(&(context->ctx), 30, 1);
                nk_label(&(context->ctx), "Looking at:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(&(context->ctx), 30, 3);
                nk_property_float(&(context->ctx), "#X:", FLOAT_MIN, &lx, FLOAT_MAX, 5, 1);
                nk_property_float(&(context->ctx), "#Y:", FLOAT_MIN, &ly, FLOAT_MAX, 5, 1);
                nk_property_float(&(context->ctx), "#Z:", FLOAT_MIN, &lz, FLOAT_MAX, 5, 1);

                nk_property_float(&(context->ctx), "FOV:", 0, &fov, 120, 5, 1);
                nk_group_end(&(context->ctx));
            }

            if (nk_group_begin(&(context->ctx), "Add Spheres", NK_WINDOW_BORDER))
            {
                nk_layout_row_dynamic(&(context->ctx), 30, 1);
                nk_label(&(context->ctx), "Scene Settings", NK_TEXT_CENTERED);
                nk_layout_row_dynamic(&(context->ctx), 30, 1);
                if (nk_button_label(&(context->ctx), "Add Sample Spheres"))
                {
                    Metal *m = new Metal(Point(0.9, 0.9, 0.9), 0.5);
                    Lambertian *l = new Lambertian(Point(0.9, 0.9, 0.9));
                    Metal *ma = new Metal(Point(0.9, 0.9, 0.6), 0.8);
                    Lambertian *la = new Lambertian(Point(0.5, 0.5, 0.5));
                    Lambertian *lred = new Lambertian(Point(0.9, 0.0, 0.0));
                    Lambertian *lblue = new Lambertian(Point(0.0, 0.0, 0.9));
                    Dielectrics *d = new Dielectrics(1.3);

                    s->addSphere(prims::Sphere(2, Point(255, 255, 255), Point(-8, 2, -30), m));
                    s->addSphere(prims::Sphere(2, Point(255, 255, 255), Point(8, 2, -30), d));
                    s->addSphere(prims::Sphere(3, Point(255, 255, 255), Point(-0, 3, -15), d));
                    s->addSphere(prims::Sphere(3, Point(255, 255, 255), Point(-3, 3, -30), lred));
                    s->addSphere(prims::Sphere(3, Point(255, 255, 255), Point(3, 3, -30), lblue));
                    s->addSphere(prims::Sphere(0.3, Point(255, 255, 255), Point(2, 2, -12), ma));
                    s->addSphere(prims::Sphere(1100, Point(255, 255, 255), Point(0, -1100.5, -30), l));
                }
                // nk_layout_row_dynamic(&(context->ctx), 30, 1);
                // nk_label(&(context->ctx), "Add Sphere", NK_TEXT_ALIGN_LEFT);
                // static const char *material[] = {"Metal", "Lambertian", "Dielectric"}; // The options we want to display
                // static int selected_item_index = 0;                                    // Selected item index
                // struct nk_vec2 size = {100, 100};                                      // Size of the dropdown that displays all our items
                // nk_layout_row_dynamic(&(context->ctx), 30, 2);
                // nk_combobox(&(context->ctx), material, 3, &selected_item_index, 20, size);
                // switch (selected_item_index)
                // {
                // case (0): // Metal
                //     nk_layout_row_dynamic(&(context->ctx), 30, 2);
                //     nk_property_float(&(context->ctx), "Fuzz:", 0, &prop, 1, 0.1, 0.2);
                //     if (nk_combo_begin_color(&(context->ctx), nk_rgb_cf(sphereCol), nk_vec2(nk_widget_width(&(context->ctx)), 400)))
                //     {
                //         nk_layout_row_dynamic(&(context->ctx), 120, 1);
                //         sphereCol = nk_color_picker(&(context->ctx), sphereCol, NK_RGB);
                //         nk_layout_row_dynamic(&(context->ctx), 25, 1);
                //         sphereCol.r = nk_propertyf(&(context->ctx), "#R:", 0, sphereCol.r, 1.0f, 0.01f, 0.005f);
                //         sphereCol.g = nk_propertyf(&(context->ctx), "#G:", 0, sphereCol.g, 1.0f, 0.01f, 0.005f);
                //         sphereCol.b = nk_propertyf(&(context->ctx), "#B:", 0, sphereCol.b, 1.0f, 0.01f, 0.005f);
                //         _sphereCol.x = nk_rgb_cf(sphereCol).r;
                //         _sphereCol.x = nk_rgb_cf(sphereCol).g;
                //         _sphereCol.x = nk_rgb_cf(sphereCol).b;
                //         nk_combo_end(&(context->ctx));
                //     }
                //     break;
                // case (1): // Lambertian
                //     if (nk_combo_begin_color(&(context->ctx), nk_rgb_cf(sphereCol), nk_vec2(nk_widget_width(&(context->ctx)), 400)))
                //     {
                //         nk_layout_row_dynamic(&(context->ctx), 120, 1);
                //         sphereCol = nk_color_picker(&(context->ctx), sphereCol, NK_RGB);
                //         nk_layout_row_dynamic(&(context->ctx), 25, 1);
                //         sphereCol.r = nk_propertyf(&(context->ctx), "#R:", 0, sphereCol.r, 1.0f, 0.01f, 0.005f);
                //         sphereCol.g = nk_propertyf(&(context->ctx), "#G:", 0, sphereCol.g, 1.0f, 0.01f, 0.005f);
                //         sphereCol.b = nk_propertyf(&(context->ctx), "#B:", 0, sphereCol.b, 1.0f, 0.01f, 0.005f);
                //         _sphereCol.x = nk_rgb_cf(sphereCol).r;
                //         _sphereCol.x = nk_rgb_cf(sphereCol).g;
                //         _sphereCol.x = nk_rgb_cf(sphereCol).b;
                //         nk_combo_end(&(context->ctx));
                //     }
                //     break;
                // case (2): // Dielectric
                //     nk_layout_row_dynamic(&(context->ctx), 30, 1);
                //     nk_property_float(&(context->ctx), "Refractive Index:", 0, &prop, 100, 0.1, 0.2);
                //     break;
                // }
                // nk_layout_row_dynamic(&(context->ctx), 30, 1);
                // nk_property_float(&(context->ctx), "#Radius:", 0, &r, FLOAT_MAX, 5, 1);
                // nk_layout_row_dynamic(&(context->ctx), 30, 1);
                // nk_label(&(context->ctx), "Location:", NK_TEXT_LEFT);
                // nk_layout_row_dynamic(&(context->ctx), 30, 3);
                // nk_property_float(&(context->ctx), "#X:", FLOAT_MIN, &sx, FLOAT_MAX, 5, 1);
                // nk_property_float(&(context->ctx), "#Y:", FLOAT_MIN, &sy, FLOAT_MAX, 5, 1);
                // nk_property_float(&(context->ctx), "#Z:", FLOAT_MIN, &sz, FLOAT_MAX, 5, 1);
                // nk_layout_row_dynamic(&(context->ctx), 30, 1);
                // if (nk_button_label(&(context->ctx), "Add Sphere"))
                // {
                //     std::cout << sx << sy << sz << std::endl;
                //     s->addSphere(prims::Sphere(r, _sphereCol, Point(sx, sy, sz), new Metal(Point(0, 0, 0), 0.5)));
                // }
                nk_group_end(&(context->ctx));
            }

            // nk_layout_row_dynamic(&(context->ctx), 30, 2);
            // if (nk_option_label(&(context->ctx), "easy", op == EASY))
            //     op = EASY;
            // if (nk_option_label(&(context->ctx), "hard", op == HARD))
            //     op = HARD;
            // nk_layout_row_dynamic(&(context->ctx), 25, 1);

            // nk_layout_row_dynamic(&(context->ctx), 20, 1);
            // nk_label(&(context->ctx), "background:", NK_TEXT_LEFT);
            // nk_layout_row_dynamic(&(context->ctx), 25, 1);
            // if (nk_combo_begin_color(&(context->ctx), nk_rgb_cf(background), nk_vec2(nk_widget_width(&(context->ctx)), 400)))
            // {
            //     nk_layout_row_dynamic(&(context->ctx), 120, 1);
            //     background = nk_color_picker(&(context->ctx), background, NK_RGB);
            //     nk_layout_row_dynamic(&(context->ctx), 25, 1);
            //     background.r = nk_propertyf(&(context->ctx), "#R:", 0, background.r, 1.0f, 0.01f, 0.005f);
            //     background.g = nk_propertyf(&(context->ctx), "#G:", 0, background.g, 1.0f, 0.01f, 0.005f);
            //     background.b = nk_propertyf(&(context->ctx), "#B:", 0, background.b, 1.0f, 0.01f, 0.005f);
            //     bgbyte = nk_rgb_cf(background);
            //     s->changeBackground(Point(bgbyte.r, bgbyte.g, bgbyte.b));
            //     nk_combo_end(&(context->ctx));
            // }
        }
        nk_end(&(context->ctx));

        nk_sdlsurface_render(context, clear, 1);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, finalTexture, NULL, NULL);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(finalTexture);
    }

    // Shut down nuklear
    nk_sdlsurface_shutdown(context);

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
