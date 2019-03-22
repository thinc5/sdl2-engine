#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/game.h"

#include "../include/timer.h"
#include "../include/assetmanager.h"
#include "../include/entitymanager.h"

#include "../include/Entities/cat.h"

bool initGame(GameData* gameData) {
    // Game is running?
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
    gameData->fps = initFPSManager();
    // Custom texture registry
    gameData->assets = (AssetRegistry) {
        .currentSize = 0,
        .totalSize = 0,
    };
    gameData->entities = initEntityManager();
    return true;
}

/**
 * Free game data struct.
 */
void freeGame(GameData* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    printf("Freeing assets...\n");
    free(game->entities.entities);
    freeAssets(&game->assets);
    free(game->assets.registry);
    game->assets.registry = NULL;
    // Destroy SDL components.
    
}
