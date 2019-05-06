#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

#include "../game.h"
#include "../scenes/scene.h"

/**
 * Render all renderable entites.
 */
void render_entities(GameData* game, Scene* scene);

#endif

