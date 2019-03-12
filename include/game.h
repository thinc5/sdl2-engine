#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "../include/texturemanager.h"
#include "../include/fontmanager.h"
#include "../include/timer.h"

/**
 * Each texture to be registered.
 */
typedef struct GameData {
    bool status;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    TextureRegistry* tr;
    FontRegistry* fr;
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