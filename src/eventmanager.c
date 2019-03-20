#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../include/eventmanager.h"
#include "../include/game.h"
#include "../include/entity.h"
#include "../include/Components/move.h"

/**
 * Initialize the event manager with basic inputs.
 */
void initEventManager(EventManager* em);

/**
 * Process input depending on the context of the current scene.
 */
void eventHandler(GameData* gameData) {
    // Default behaviour
    if (gameData->event.type == SDL_KEYDOWN) {
        switch (gameData->event.key.keysym.sym) {
            case SDLK_ESCAPE:
                gameData->status = false;
                    break;
            // Check if its closed.
            case SDLK_LEFT:
                gameData->entities.entities[0].components[Moved].call(&gameData->entities.entities[0], LEFT);
                break;
            case SDLK_RIGHT:
                gameData->entities.entities[0].components[Moved].call(&gameData->entities.entities[0], RIGHT);
                break;
            case SDLK_UP:
                gameData->entities.entities[0].components[Moved].call(&gameData->entities.entities[0], UP);
                break;
            case SDLK_DOWN:
                gameData->entities.entities[0].components[Moved].call(&gameData->entities.entities[0], DOWN);
            default:
                break;
        }
    // Check if an entity was clicked.
    } else if (gameData->event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // printf("Mouse Position: %d %d\n", x, y);
        for (int i = 0; i < gameData->entities.current; i++) {
            Entity* e = &gameData->entities.entities[i];
            // Can enttiy even be clicked?
            if (e->components[Clicked].call == NULL) {
                continue;
            }
            // Check if entity has been clicked.
            if (x >= e->position.x && x <= e->position.x + e->position.w &&
                    y >= e->position.y && y <= e->position.y + e->position.h) {
                // Call entity's clicked function.
                e->components[Clicked].call(e);
            }
        }
    }

}

