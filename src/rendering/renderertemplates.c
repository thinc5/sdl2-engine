#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/util/camera.h"

/**
 * Simple function to draw and fill a rectangle.
 */
bool render_rectangle(SDL_Rect* pos, SDL_Color colour, bool fill) {
    SDL_SetRenderDrawColor(gameData.renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawRect(gameData.renderer, pos);
    if (fill) {
        SDL_RenderFillRect(gameData.renderer, pos);
    }
    return true;
}

/**
 * Simple function to draw a message to the screen using a font.
 */
bool render_font(TTF_Font* font, SDL_Rect* pos, SDL_Color colour, char* text) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gameData.renderer, surface);
    SDL_FreeSurface(surface);
    // Draw to renderer
    bool result = SDL_RenderCopy(gameData.renderer, texture, NULL, pos);
    SDL_DestroyTexture(texture);
    return result;
}

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool render_texture(SDL_Texture* texture, SDL_Rect* dpos) {
    if (SDL_RenderCopy(gameData.renderer, texture, NULL, dpos) != 0) {
        return false;
    }
    return true;
}

/**
 * Simple wrapper function for rendering textures to the screen.
 */
bool render_background(Scene* currentScene) {
    if (currentScene->bg == NULL) {
        return false;
    }
    if (SDL_RenderCopy(gameData.renderer, currentScene->bg,
            NULL, NULL) != 0) {
        return false;
    }
    return true;
}

/**
 * Draw a pre-designed debug message to the screen.
 */
bool render_debug_message(TTF_Font* font, char* text) {
    int text_size = strlen(text);
    int font_height = TTF_FontHeight(font);
    int font_width = font_height / 2;
    SDL_Rect pos = {
        .x = 0,
        .y = 0,
        .w = font_width * text_size,
        .h = font_height
    };
    SDL_Color c = { 255, 0, 0, 255 };
    return render_font(font, &pos, c, text);
}

/**
 * Show the fps in the top right corner of the screen.
 */
bool render_fps(TTF_Font* font, int fps) {
    char text[10];
    sprintf(text, "%d", fps);
    int height, width;
    SDL_GetRendererOutputSize(gameData.renderer, &width, &height);
    int font_size = TTF_FontHeight(font);
    SDL_Rect pos = {
        .x = width - ((font_size/2) * 4) - 5,
        .y = 0,
        .w = font_size * 2,
        .h = font_size
    };
    SDL_Color c = { 0, 0, 0, 255 };
    return render_font(font, &pos, c, text);
}

/**
 * Draw a loading notification box.
 */
bool render_loading_box(TTF_Font* font) {
    // Size of screen.
    int height, width;
    SDL_GetRendererOutputSize(gameData.renderer, &width, &height);
    SDL_Rect pos = transform_rect((SDL_Rect) { 0 }, 0.0f, 0.0f, 0.2f, 0.2f);
    SDL_Color c = { 0, 0, 0, 255 };
    return render_font(font, &pos, c, "Loading...");
}

/**
 * Render cursor.
 * TODO: Transparency on cursor.
 */
bool render_cursor(Scene* currentScene) {
    // Render cursor if applicable
        if (currentScene->cursor != NULL) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Rect rect = {
                .x = x - 15,
                .y = y - 15,
                .w = 30,
                .h = 30
            };
            // TODO: Fix the transparent rendering of cursor with Colour Keying
            //SDL_BlitSurface(currentScene->cursor, NULL, gameData.renderer, &rect);
            render_texture(currentScene->cursor, &rect);
        }
        return true;
}
