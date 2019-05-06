#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/managers/eventmanager.h"
#include "../../include/entities/entity.h"
#include "../../include/components/move.h"

/**
 * Check if provided x and y coordinates are inside of provided rectangle.
 */
static bool is_collision(int x, int y, SDL_Rect position) {
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
static void click_handler(GameData* gameData, Scene* scene) {
    // Check if an entity was left clicked.
    int x, y;
    SDL_GetMouseState(&x, &y);
    // INFO_LOG("Cick at x: %d, y:%d\n", x, y);
    
    if (gameData->event.button.button == SDL_BUTTON_LEFT) {
        if (gameData->event.type == SDL_MOUSEMOTION) {
            INFO_LOG("Mouse left clicked and dragged!\n");
            // Being dragged
            for (int i = 0; i < scene->entities.current; i++) {
                Entity* e = &scene->entities.entities[i];
                // Can entity even be clicked?
                if (!has_component(e, Dragged)) {
                    continue;
                }
                // Check if entity has been clicked.
                if (is_collision(x, y, e->position)) {
                    // Call entity's clicked function.
                    e->components[Dragged].call(e, x, y);
		    return;
                }
            }   
        } else {
            for (int i = 0; i < scene->entities.current; i++) {
                Entity* e = &scene->entities.entities[i];
                if (!has_component(e, LeftClicked)) {
                    continue;
                }
                if (is_collision(x, y, e->position)) {
                    e->components[LeftClicked].call(e);
		    return;
                }
            }
        }
    } else if (gameData->event.button.button == SDL_BUTTON_RIGHT) {
        for (int i = 0; i < scene->entities.current; i++) {
            Entity* e = &scene->entities.entities[i];
            // Can entity even be clicked?
            if (!has_component(e, RightClicked)) {
                continue;
            }
            // Check if entity has been clicked.
            if (is_collision(x, y, e->position)) {
                // Call entity's clicked function.
                e->components[RightClicked].call(e);
		return;
            }
        }
    }
}

/**
 * Default keyboard press handler.
 * Handle arrow keys and delete. 
 */
static void key_handler(GameData* gameData, Scene* scene) {
    // INFO_LOG("Key: %s\n", SDL_GetKeyName(gameData->event.key.keysym.sym));
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
            for (int i = 0; i < scene->entities.current; i++) {
                Entity* e = &scene->entities.entities[i];
                if (is_collision(x, y, e->position)) {
                    // Call entity's clicked function.
                    e->components[Deleted].call(e);
		    return;
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
void default_handler(void* game, void* scene) {
    GameData* gameData = (GameData*) game;
    Scene* currentScene = (Scene*) scene;
    // Default behaviour.
    if (gameData->event.key.keysym.sym == SDLK_ESCAPE) {
	// INFO_LOG("ESC pressed.\n");
        gameData->status = false;
        return;
    }
    switch (gameData->event.type) {
        case SDL_MOUSEBUTTONDOWN:
	    // INFO_LOG("Mouse button press.\n");
            click_handler(gameData, currentScene);
            break;
        case SDL_KEYDOWN:
	    // INFO_LOG("Key press.\n");
            key_handler(gameData, currentScene);
            break;
        default:
            break;
    }
}


