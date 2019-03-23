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
                    // Implement after we have selection.
                    break;
                case SDLK_RIGHT:
                    break;
                case SDLK_UP:
                    break;
                case SDLK_DOWN:
                    break;
                case SDLK_DELETE:
                    // If hovering over an entity delete it.
                    SDL_GetMouseState(&x, &y);
                    for (int i = 0; i < gameData->entities.current; i++) {
                        Entity* e = &gameData->entities.entities[i];
                        if (isCollision(x, y, e->position)) {
                            // Call entity's clicked function.
                            e->components[Deleted].call(e);
                        }
                    }
                    break;
                default:
                    break;
            }
        // Check if an entity was left clicked.
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            if (gameData->event.button.button == SDL_BUTTON_LEFT) {
                if (gameData->event.type == SDL_MOUSEMOTION) {
                    printf("Mouse left clicked and dragged!\n");
                    // Being dragged
                    for (int i = 0; i < gameData->entities.current; i++) {
                        Entity* e = &gameData->entities.entities[i];
                        // Can entity even be clicked?
                        if (!hasComponent(e, Dragged)) {
                            continue;
                        }
                        // Check if entity has been clicked.
                        if (isCollision(x, y, e->position)) {
                            // Call entity's clicked function.
                            e->components[Dragged].call(e, x, y);
                        }
                    }   
                } else {
                    for (int i = 0; i < gameData->entities.current; i++) {
                        Entity* e = &gameData->entities.entities[i];
                        if (!hasComponent(e, LeftClicked)) {
                            continue;
                        }
                        if (isCollision(x, y, e->position)) {
                            e->components[LeftClicked].call(e);
                        }
                    }
                }
            } else if (gameData->event.button.button == SDL_BUTTON_RIGHT) {
                for (int i = 0; i < gameData->entities.current; i++) {
                    Entity* e = &gameData->entities.entities[i];
                    // Can entity even be clicked?
                    if (!hasComponent(e, RightClicked)) {
                        continue;
                    }
                    // Check if entity has been clicked.
                    if (isCollision(x, y, e->position)) {
                        // Call entity's clicked function.
                        e->components[RightClicked].call(e);
                    }
                }
            }
            break;
    }
}



