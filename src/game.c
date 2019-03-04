#include <SDL2/SDL.h>

#include <stdlib.h>

#include "../include/config.h"
#include "../include/game.h"
#include "../include/frameratemanager.h"

void initGame(GameData* gameData) {
    // Create the window
    gameData->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE),
    // Create the renderer
    gameData->renderer = SDL_CreateRenderer(gameData->window, -1, SDL_RENDERER_ACCELERATED);
    // Set default background colour
    SDL_SetRenderDrawColor(gameData->renderer, 255, 0, 0, 255);
    // Custom framerate manager
    gameData->fps = (FrameRateManager*) malloc(sizeof(FrameRateManager));
    initTimer(gameData->fps);
    // Custom texture registry
    gameData->tr = (TextureRegistry*) malloc(sizeof(TextureRegistry));
    gameData->tr->currentSize = 0;
    gameData->tr->totalSize = 0;
}

/**
 * Free game data struct.
 */
void freeGame(GameData* game) {
    free(game->fps);
    freeTextures(game->tr);
    free(game->tr);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
}
