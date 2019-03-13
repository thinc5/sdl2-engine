#ifndef RENDERTEMPLATES_H
#define RENDERTEMPLATES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "renderer.h"

/**
 * Draw a pre-designed debug message to the screen.
 */
bool drawDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text);

#endif