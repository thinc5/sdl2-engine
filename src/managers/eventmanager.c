#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "../../include/game.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/entities/entity.h"
#include "../../include/components/move.h"

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
 * Default handler for clicks.
 * Handles: left clicks, right clicks, and click and drags.
 */
void clickHandler(GameData* gameData) {
    // Check if an entity was left clicked.
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (gameData->event.button.button == SDL_BUTTON_LEFT) {
        if (gameData->event.type == SDL_MOUSEMOTION) {
            printf("Mouse left clicked and dragged!\n");
            // Being dragged
            for (int i = 0; i < gameData->scene.entities.current; i++) {
                Entity* e = &gameData->scene.entities.entities[i];
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
            for (int i = 0; i < gameData->scene.entities.current; i++) {
                Entity* e = &gameData->scene.entities.entities[i];
                if (!hasComponent(e, LeftClicked)) {
                    continue;
                }
                if (isCollision(x, y, e->position)) {
                    e->components[LeftClicked].call(e);
                }
            }
        }
    } else if (gameData->event.button.button == SDL_BUTTON_RIGHT) {
        for (int i = 0; i < gameData->scene.entities.current; i++) {
            Entity* e = &gameData->scene.entities.entities[i];
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
}

/**
 * Default keyboard press handler.
 * Handle arrow keys and delete. 
 */
void keyHandler(GameData* gameData) {
    int x, y = 0;
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
            for (int i = 0; i < gameData->scene.entities.current; i++) {
                Entity* e = &gameData->scene.entities.entities[i];
                if (isCollision(x, y, e->position)) {
                    // Call entity's clicked function.
                    e->components[Deleted].call(e);
                }
            }
            break;
        default:
            break;
    }
}

/**
 * Process input depending on the context of the current scene.
 */
void default_handler(void* game) {
    GameData* gameData = (GameData*) gameData;
    // Default behaviour
    if (gameData->event.key.keysym.sym == SDLK_ESCAPE) {
        gameData->status = false;
        return;
    }
    switch (gameData->event.type) {
        case SDL_MOUSEBUTTONDOWN:
            clickHandler(gameData);
            break;
        case SDL_KEYDOWN:
            keyHandler(gameData);
            break;
        default:
            break;
    }
}

