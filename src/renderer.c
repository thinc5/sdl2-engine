#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../include/renderer.h"
#include "../include/renderertemplates.h"
#include "../include/entity.h"

/**
 * Render all renderable entites.
 */
void renderEntities(GameData* gameData) {
    for (int i = 0; i < gameData->scene.entities.current; i++) {
        if (hasComponent(&gameData->scene.entities.entities[i], Render)) {
            gameData->scene.entities.entities[i].components[Render].call(&gameData->scene.entities.entities[i], gameData->renderer);
        }
    } 
}
