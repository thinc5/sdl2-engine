#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../../include/rendering/renderer.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/entities/entity.h"
#include "../../include/scenes/scene.h"

/**
 * Render all renderable entites.
 */
void render_entities(GameData* game, Scene* scene) {
    for (int i = 0; i < scene->entities.current; i++) {
        if (has_component(&scene->entities.entities[i], Render)) {
            scene->entities.entities[i].components[Render]
                    .call(&scene->entities.entities[i], game->renderer);
        }
    }
}

