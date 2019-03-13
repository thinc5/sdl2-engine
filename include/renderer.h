#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * Simple function to draw a message to the screen using a font.
 */
bool renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text);


/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dpos);

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderBackground(SDL_Renderer* renderer, SDL_Texture* texture);

#endif