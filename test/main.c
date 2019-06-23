#if EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif
#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/**
 *  Initialize SDL components.
 */
static bool init_modules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return false;
    }
    return true;
 }

/**
 * Quit SDL components.
 */
static void quit_modules(void) {
    SDL_Quit();
 }

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Start all major game components.
    if (!init_modules()) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("lul", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	1920, 1080, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Set default background colour.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            if (event.key.keysym.sym == SDLK_F1) {
                break;
            }
        }
        SDL_RenderClear(renderer);
	    SDL_RenderPresent(renderer);
        //printf("hello world!\n");
    }

    quit_modules();
    return 0;
}

