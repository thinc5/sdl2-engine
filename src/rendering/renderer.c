#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../../include/rendering/renderer.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/entities/entity.h"

/**
 * Render all renderable entites.
 */
void render_entities(GameData* gameData) {
    for (int i = 0; i < gameData->scene.entities.current; i++) {
        if (has_component(&gameData->scene.entities.entities[i], Render)) {
            gameData->scene.entities.entities[i].components[Render].call(&gameData->scene.entities.entities[i], gameData->renderer);
        }
    } 
}
