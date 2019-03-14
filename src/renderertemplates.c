#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>

#include "../include/renderertemplates.h"

/**
 * Draw a pre-designed debug message to the screen.
 */
bool renderDebugMessage(SDL_Renderer* renderer, TTF_Font* font, char* text) {
    int text_size = strlen(text);
    int font_height = TTF_FontHeight(font);
    int font_width = font_height / 2;
    SDL_Rect pos = {
        .x = 0,
        .y = 0,
        .w = font_width * text_size,
        .h = font_height
    };
    SDL_Color c = {255, 0, 0};
    return renderFont(renderer, font, &pos, c, text);
}

/**
 * Show the fps in the top right corner of the screen.
 */
bool renderFPS(SDL_Renderer* renderer, TTF_Font* font, int fps) {
    char text[10];
    sprintf(text, "%d", fps);
    int height, width;
    SDL_GetRendererOutputSize(renderer, &width, &height);
    int font_size = TTF_FontHeight(font);
    SDL_Rect pos = {
        .x = width - ((font_size/2) * 4) - 5,
        .y = 0,
        .w = font_size * 2,
        .h = font_size
    };
    SDL_Color c = {0, 0, 0};
    return renderFont(renderer, font, &pos, c, text);
}
