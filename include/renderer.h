#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, SDL_Color colour, char* text);

void drawDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text);

#endif