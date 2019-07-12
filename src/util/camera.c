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

/**
 * Check if provided x and y coordinates are inside of provided rectangle.
 */
bool is_collision(int x, int y, SDL_Rect position) {
    if (x >= position.x && x <= position.x + position.w &&
            y >= position.y && y <= position.y + position.h) {
        return true;
    }
    return false;
}

/**
 * Check if provided rects overlap.
 */
bool is_overlap(SDL_Rect dest, SDL_Rect position) {
    return SDL_IntersectRect(&dest, &position, NULL);
}

/**
 * Check if provided rect is entirely within the second rect.
 */
bool is_inside(SDL_Rect within, SDL_Rect container) {
    if (within.y < container.y || within.x < container.x || within.y + within.h >
            container.y + container.h || within.x + within.w >
            container.x + container.w) {
        return false;
    }
    return true;
}

/**
 * Get the center of a rectangle as a SDL_Point.
 */
SDL_Point get_rect_centre(SDL_Rect rect) {
    return (SDL_Point) { rect.x + (rect.w / 2), rect.y + (rect.h / 2) }; 
};

/**
 * Returns true if the point is within the provided rectangle.
 */
bool is_point_inside(SDL_Rect within, SDL_Point point) {
    return point.x > within.x && point.x < within.x + within.w &&
            point.y > within.y && point.y < within.y + within.h;
}

