#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "util/framerate.h"
#include "scenes/scene.h"

typedef enum GameStatus {
    RUNNING,
    LOADING,
    CLOSING
} GameStatus;

/**
 * GameData struct, holds all data such as current scene,
 * SDL Window/Renderer and more.
 */
typedef struct GameData {
    // Is the game still running?
    GameStatus status;

    // SDL window, renderer and event.
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    // Assets required for scene.
    AssetStack assets;

    // Framerate manager.
    FrameRateManager fps;

    // Resources required for the main/escape menu and debugging.
    Scene* menu;

    // Other scene.
    Scene* scene;
    
    // Currently selected scene.
    Scene* currentScene;
} GameData;

/**
 * Return initialized GameData struct.
 */
bool init_game(GameData* gameData);

/**
 * Free game objects.
 */
void free_game(GameData* game);

extern GameData gameData;

#endif
