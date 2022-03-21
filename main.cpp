#include <SDL2/SDL.h>
#include <stdio.h>
#include "Scene.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

bool init();

bool loadMedia();

void close();

int main(int argc, char *args[])
{

    SDL_Window *gWindow = NULL;

    SDL_Surface *gScreenSurface = NULL;

    SDL_Surface *gHelloWorld = NULL;

    bool init();

    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Create window
    window = SDL_CreateWindow("Joe Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Scene* s = new Scene(SCREEN_WIDTH, SCREEN_HEIGHT);
    // s->render();

    int channels = 3;
    char* pixels = new char[SCREEN_WIDTH * SCREEN_HEIGHT * channels];

    for(int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH * channels; i++) {
        pixels[i] = 128;
    }

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)pixels,
                    SCREEN_WIDTH,
                    SCREEN_HEIGHT,
                    channels * 8,
                    SCREEN_WIDTH * channels,
                    0x0000FF,
                    0x00FF00,
                    0xFF0000,
                    0);

    // Fill the surface white
    // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait two seconds
    SDL_Delay(5000);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

bool init()
{

}

bool loadMedia()
{
}

void close()
{
}
