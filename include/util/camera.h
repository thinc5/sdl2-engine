#ifndef CAMERA_H
#define CAMERA

#include <SDL2/SDL.h>

/**
 * Given an SDL_Rect and the desired scalings (1f is the centre) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(SDL_Window* window, float wscale, float hscale,
        float xscale, float yscale);

#endif

