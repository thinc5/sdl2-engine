#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/game.h"
#include "../include/timer.h"
#include "../include/assetmanager.h"

void initGame(GameData* gameData) {
    gameData->status = true;
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
    initFPSManager(gameData->fps);
    // Custom texture registry
    gameData->assets = (AssetRegistry*) malloc(sizeof(AssetRegistry));
    gameData->assets->currentSize = 0;
    gameData->assets->totalSize = 0;
}

/**
 * Free game data struct.
 */
void freeGame(GameData* game) {
    printf("Freeing textures...\n");
    freeAssets(game->assets);
    free(game->assets->registry);
    game->assets->registry = NULL;
    free(game->assets);
    game->assets = NULL;
    printf("Freeing timer\n");
    free(game->fps);
    printf("Freeing renderer\n");
    SDL_DestroyRenderer(game->renderer);
    printf("Freeing window\n");
    SDL_DestroyWindow(game->window);
}
