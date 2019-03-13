#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../include/renderer.h"

/**
 * Simple function to draw a message to the screen using a font.
 */
bool renderFont(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    // Draw to renderer
    bool result = SDL_RenderCopy(renderer, texture, NULL, pos);
    SDL_DestroyTexture(texture);
    return result;
}


/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dpos) {
    if (SDL_RenderCopy(renderer, texture, NULL, dpos) != 0) {
        return false;
    }
    return true;
}

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool renderBackground(SDL_Renderer* renderer, SDL_Texture* texture) {
    if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) {
        return false;
    }
    return true;
}
