#ifndef RENDERTEMPLATES_H
#define RENDERTEMPLATES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

/**
 * Simple function to draw a message to the screen using a font.
 */
bool render_font(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text);


/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool render_texture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dpos);

/**
 * Render an image as the background.
 */
bool render_background(SDL_Renderer* renderer, SDL_Texture* texture);

/**
 * Draw a pre-designed debug message to the screen.
 */
bool render_debug_message(SDL_Renderer* renderer, TTF_Font* font, char* text);

/**
 * Show the fps in the top right corner of the screen.
 */
bool render_fps(SDL_Renderer* renderer, TTF_Font* font, int fps);

/**
 * Draw a loading notification box.
 */
bool render_loading_box(SDL_Renderer* renderer, TTF_Font* font);

#endif
