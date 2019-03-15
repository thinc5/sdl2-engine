#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "../include/assetmanager.h"
#include "../include/timer.h"

/**
 * Each texture to be registered.
 */
typedef struct GameData {
    bool status;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    AssetRegistry* assets;
    FrameRateManager* fps;
} GameData;

/**
 * Return initialized GameData struct.
 */
void initGame(GameData* gameData);

/**
 * Free game objects.
 */
void freeGame(GameData* game);

#endif