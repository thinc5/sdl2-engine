#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/config.h"
#include "../include/texturemanager.h"

/**
 * Entry point for Engine.
 */
int WinMain(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    // Init sdl
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create the window
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // TextureRegistry
    TextureRegistry tr;
    tr.currentSize = 10;
    tr.registry = (RegisteredTexture*) malloc(sizeof(RegisteredTexture) * tr.currentSize);
    tr.totalSize = 10;

    // Load a test texture.
    if (!loadTexture(renderer, "./res/alex.jpg", &tr)) {
        printf("Failed to load texture..");
        SDL_Quit();
        return 2;
    }


    // Main game loop
    bool game = true;
    while (game) {
        
        while (SDL_PollEvent(&event)) {
            // If person wants to exit i.e. alt+f4 or clicking x
            if (event.type == SDL_QUIT) {
                // Clean up memory here and break main game loop
                printf("Caught SDL_QUIT, exiting now...\n");
                freeTextures(&tr);
                game = false;
            }

            // Draw
            SDL_RenderClear(renderer);
            if (SDL_RenderCopy(renderer, (&tr)->registry[0].texture, NULL, NULL) == -1) {
                printf("Failed to render texture..");
            }
            SDL_RenderPresent(renderer);

        }
    }

    SDL_Quit();
    return 0;
}
