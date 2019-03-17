#include <SDL2/SDL.h>

#include "../include/eventmanager.h"
#include "../include/game.h"

/**
 * Initialize the event manager with basic inputs.
 */
void initEventManager(EventManager* em);

void scene1Manager(GameData* gameData, int* pickedTex) {
    if (gameData->event.type == SDL_KEYDOWN) {
        switch (gameData->event.key.keysym.sym) {
            case SDLK_ESCAPE:
                gameData->status = false;
                    break;
            case SDLK_LEFT:
                if (*pickedTex - 1 < 0) {
                    *pickedTex = gameData->assets->currentSize - 1;
                } else {
                    *pickedTex = *pickedTex - 1;
                }
                break;
            case SDLK_RIGHT:
                if (*pickedTex + 1 < gameData->assets->currentSize) {
                    *pickedTex = *pickedTex + 1;
                } else {
                    *pickedTex = 0;
                }
                break;
            case SDLK_SPACE:
                // gameData->fps->timer->
                break;
            default:
                break;
        }
    }    
}