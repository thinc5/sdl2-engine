#ifndef RENDERTEMPLATES_H
#define RENDERTEMPLATES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

#include "../scenes/scene.h"

/**
 * Simple function to draw a message to the screen using a font.
 */
bool render_font(TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text);


/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool render_texture(SDL_Texture* texture, SDL_Rect* dpos);

/**
 * Render an image as the background.
 */
bool render_background(Scene* currentScene);

/**
 * Draw a pre-designed debug message to the screen.
 */
bool render_debug_message(TTF_Font* font, char* text);

/**
 * Show the fps in the top right corner of the screen.
 */
bool render_fps(TTF_Font* font, int fps);

/**
 * Draw a loading notification box.
 */
bool render_loading_box(TTF_Font* font);

/**
 * Render cursor.
 */
bool render_cursor(Scene* currentScene);

#endif
