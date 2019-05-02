#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/game.h"

#include "../include/util/timer.h"
#include "../include/managers/entitymanager.h"

#include "../include/scenes/scene.h"
#include "../include/scenes/mainmenu.h"

/**
 * Initilize game and it's required components.
 */
bool init_game(GameData* gameData) {
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
    SDL_RenderSetLogicalSize(gameData->renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    // Custom framerate manager
    gameData->fps = initFPSManager();
    // Custom texture registry
    gameData->menu = initMainMenu(gameData->renderer);
    gameData->scene = initMainMenu(gameData->renderer);
    return true;
}

/**
 * Free game data.
 */
void free_game(GameData* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    printf("Freeing assets...\n");
    freeScene(&game->scene);
    freeScene(&game->menu);
}
