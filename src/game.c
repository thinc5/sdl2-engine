#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdbool.h>

#include "../include/debug.h"
#include "../include/config.h"
#include "../include/game.h"
#include "../include/util/framerate.h"
#include "../include/scenes/scene.h"
#include "../include/scenes/mainmenu.h"

/**
 * Initialize game and it's required components.
 */
bool init_game(GameData* gameData) {
    // Game is running?
    gameData->status = RUNNING;
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
    // Framerate manager.
    gameData->fps = init_fps();
    // Create the asset stack
    init_asset_stack(&gameData->assets);
    // Scenes.
    gameData->menu = (Scene*) malloc(sizeof(Scene));
    init_main_menu();
    gameData->currentScene = gameData->menu;
    // Allocate space for the other scenes.
    gameData->scene = NULL;
    return true;
}

/**
 * Free game data.
 */
void free_game(GameData* gameData) {
    DEBUG_LOG("free_game()\n");
    // Free renderer and window.
    SDL_DestroyRenderer(gameData->renderer);
    SDL_DestroyWindow(gameData->window);
    
    // Free scenes.
    if (gameData->scene != NULL) {
        // Freeing scene.
        if (gameData->scene->title[0] != '\0') {
            DEBUG_LOG("Freeing scene: \"%s\"\n", gameData->scene->title);
        }
        free_scene(gameData->scene);
        free(gameData->scene);
        gameData->scene = NULL;
        DEBUG_LOG("Freed scene\n");
    }
    if (gameData->menu != NULL) {
        if (gameData->menu->title[0] != '\0') {
            DEBUG_LOG("Freeing scene: \"%s\"\n", gameData->menu->title);
        }
        free_scene(gameData->menu);
        free(gameData->menu);
        gameData->menu = NULL;
        DEBUG_LOG("Freed menu\n");
    }
    gameData->currentScene = NULL;
}
