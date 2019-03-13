#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

#include "../include/renderertemplates.h"

/**
 * Draw a pre-designed debug message to the screen.
 */
bool drawDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text) {
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
    SDL_Color red = {255, 0, 0};
    return renderFont(renderer, font, &pos, red, text);
}