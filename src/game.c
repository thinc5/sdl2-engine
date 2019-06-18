#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "../include/debug.h"
#include "../include/config.h"
#include "../include/game.h"
#include "../include/util/framerate.h"
#include "../include/scenes/scene.h"
#include "../include/scenes/mainmenu.h"
#include "../include/scenes/debugscene.h"

/**
 * Initialize game and it's required components.
 */
bool init_game(GameData* gameData) {
    // Game is running?
    gameData->status = true;
    
    // Create the window.
    gameData->window = SDL_CreateWindow(WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	        WINDOW_WIDTH, WINDOW_HEIGHT, 0); //SDL_WINDOW_RESIZABLE);
    
    // Create the renderer.
    gameData->renderer = SDL_CreateRenderer(gameData->window, -1,
            SDL_RENDERER_ACCELERATED);
    
    // Set default background colour.
    SDL_SetRenderDrawColor(gameData->renderer, 255, 0, 0, 255);
    
    // Setting render mode.
    SDL_RenderSetLogicalSize(gameData->renderer, WINDOW_WIDTH,
            WINDOW_HEIGHT);
    
    // Custom framerate manager.
    gameData->fps = init_fps();
    
    // Scenes.
    gameData->menu = (Scene*) malloc(sizeof(Scene));
    gameData->scene = (Scene*) malloc(sizeof(Scene));
    if (!init_main_menu(gameData->renderer, gameData->menu) ||
            !init_debug_scene(gameData->renderer, gameData->scene)) {
	    return false;
    }
    return true;
}


/**
 * Free game data.
 */
void free_game(GameData* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    INFO_LOG("Freeing assets...\n");
    free_scene(game->scene);
    free_scene(game->menu);
    free(game->scene);
    free(game->menu);
}

