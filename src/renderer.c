#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>

#include "../include/renderer.h"

/**
 * Simple function to draw a message to the screen using a font.
 */
void renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, SDL_Color colour, char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // Draw to renderer
    SDL_RenderCopy(renderer, texture, NULL, &pos);
    SDL_DestroyTexture(texture);
}

/**
 * Draw a pre-designed debug message to the screen.
 */
void drawDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text) {
    int height = 0;
    int width = 0;
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    int text_size = strlen(text);
    int font_size = TTF_FontHeight(font);
    SDL_Rect pos = {
        .x = height - font_size,
        .y = width,
        .w = font_size * text_size,
        .h = font_size
    };
    SDL_Color white = {255, 255, 255};
    renderFont(renderer, font, pos, white, text);
}