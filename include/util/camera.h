#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

/**
 * Given an SDL_Rect and the desired scaling (1f is the centre) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(float wscale, float hscale, float xscale, float yscale);

/**
 * Check if provided x and y coordinates are inside of provided rectangle.
 */
bool is_collision(int x, int y, SDL_Rect position);

/**
 * Check if provided rects overlap.
 */
bool is_overlap(SDL_Rect dest, SDL_Rect position);

/**
 * Check if provided rect is entirely within the second rect.
 */
bool is_inside(SDL_Rect within, SDL_Rect container);

#endif

