#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

#include <stdbool.h>

/**
 * Given an SDL_Rect and the desired scaling (0.0f is the centre, 1.0f the edge) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(SDL_Rect within, float x, float y, float width, float height);

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

/**
 * Get the center of a rectangle as a SDL_Point.
 */
SDL_Point get_rect_centre(SDL_Rect rect);

/**
 * Returns true if the point is within the provided rectangle.
 */
bool is_point_inside(SDL_Rect within, SDL_Point point);

#endif

