#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "util/framerate.h"
#include "scenes/scene.h"

/**
 * GameData struct, holds all data such as current scene,
 * SDL Window/Renderer and more.
 */
typedef struct GameData {
    // Is the game still running?
    bool status;
    // SDL window, renderer and event.
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    // Frame rate manager.
    FrameRateManager fps;
    // Resources required for the main/escape menu and debugging.
    Scene* menu;
    // Current scene.
    Scene* scene;
} GameData;

/**
 * Return initialized GameData struct.
 */
bool init_game(GameData* gameData);

/**
 * Free game objects.
 */
void free_game(GameData* game);

GameData gameData;

#endif
