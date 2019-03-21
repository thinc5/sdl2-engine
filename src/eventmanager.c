#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "../include/eventmanager.h"
#include "../include/game.h"
#include "../include/entity.h"
#include "../include/Components/move.h"

/**
 * Check if provided x and y coordinates are inside of provided rectangle.
 */
bool isCollision(int x, int y, SDL_Rect position) {
    if (x >= position.x && x <= position.x + position.w &&
            y >= position.y && y <= position.y + position.h) {
        return true;
    }
    return false;
}

/**
 * Initialize the event manager with basic inputs.
 */
void initEventManager(EventManager* em);

/**
 * Process input depending on the context of the current scene.
 */
void eventHandler(GameData* gameData) {
    // Default behaviour
    if (gameData->event.key.keysym.sym == SDLK_ESCAPE) {
        gameData->status = false;
        return;
    }
    int x, y;
    switch (gameData->event.type) {
        case SDL_KEYDOWN:
            switch (gameData->event.key.keysym.sym) {
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
                    break;
                case SDLK_d:
                    gameData->entities.entities[0].components[Deleted].call(&gameData->entities.entities[0]);
                default:
                    break;
            }
        // Check if an entity was left clicked.
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            if (gameData->event.button.button == SDL_BUTTON_LEFT) {
                printf("Mouse Position: %d %d\n", x, y);
                printf("Left click!\n");
                if (gameData->event.type == SDL_MOUSEMOTION) {
                    printf("Mouse left clicked and draged!\n");
                    // Being dragged
                    for (int i = 0; i < gameData->entities.current; i++) {
                        Entity* e = &gameData->entities.entities[i];
                        // Can enttiy even be clicked?
                        if (e->components[Draged].call == NULL) {
                            continue;
                        }
                        // Check if entity has been clicked.
                        if (isCollision(x, y, e->position)) {
                            // Call entity's clicked function.
                            e->components[Draged].call(e, x, y);
                        }
                    }   
                }
            } else if (gameData->event.button.button == SDL_BUTTON_RIGHT) {
                printf("Right click!\n");
                for (int i = 0; i < gameData->entities.current; i++) {
                    Entity* e = &gameData->entities.entities[i];
                    // Can enttiy even be clicked?
                    if (e->components[RightClicked].call == NULL) {
                        continue;
                    }
                    // Check if entity has been clicked.
                    printf("Checking collision!\n");
                    if (isCollision(x, y, e->position)) {
                        // Call entity's clicked function.
                        e->components[RightClicked].call(e);
                    }
                }
            }
            break;
    }
}



