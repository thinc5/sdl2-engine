#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../include/eventmanager.h"
#include "../include/game.h"
#include "../include/entity.h"

/**
 * Initialize the event manager with basic inputs.
 */
void initEventManager(EventManager* em);

void scene1Manager(GameData* gameData, Entity* e) {
    if (gameData->event.type == SDL_KEYDOWN) {
        switch (gameData->event.key.keysym.sym) {
            case SDLK_ESCAPE:
                gameData->status = false;
                    break;
            case SDLK_LEFT:
                e->move(e, LEFT);
                break;
            case SDLK_RIGHT:
                e->move(e, RIGHT);
                break;
            case SDLK_UP:
                e->move(e, UP);
                break;
            case SDLK_DOWN:
                e->move(e, DOWN);
                break;
            case SDLK_SPACE:
                // gameData->fps->timer->
                break;
            default:
                break;
        }
        Mix_PlayChannel(-1, e->sound, 0);
    }    
}