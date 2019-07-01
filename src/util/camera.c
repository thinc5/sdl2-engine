#include <SDL2/SDL.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/util/camera.h"

/**
 * Given an SDL_Rect and the desired scaling (1f is the centre) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(float wscale, float hscale, float xscale, float yscale) {
    SDL_Rect rect;
    // Get the size of the window.
    int w, h;
    SDL_GetRendererOutputSize(gameData.renderer, &w, &h);
    w = w/2;
    h = h/2;
    // Ensure that the scale will center the rectangle at the desired location.
    rect.w = (int)(w * wscale);
    rect.h = (int)(h * wscale);
    rect.x = (int)(w * xscale) - (int)(rect.w/2);
    rect.y = (int)(h * yscale) - (int)(rect.h/2);
    return rect;
}

