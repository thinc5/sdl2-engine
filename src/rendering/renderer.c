#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../../include/game.h"
#include "../../include/rendering/renderer.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/entities/entity.h"
#include "../../include/scenes/scene.h"

/**
 * Render all renderable entities (Super basic and inefficient).
 */
void render_entities(Scene* currentScene) {
    for (int i = 0; i < currentScene->entities.current; i++) {
        if (has_component(&currentScene->entities.entities[i], Render)) {
            currentScene->entities.entities[i].components[Render]
                    .call(&currentScene->entities.entities[i]);
        }
    }
}
