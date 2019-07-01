#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

/**
 * Given an SDL_Rect and the desired scaling (1f is the centre) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(float wscale, float hscale, float xscale, float yscale);

#endif
