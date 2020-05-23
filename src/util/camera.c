#include <SDL2/SDL.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/util/camera.h"

/**
 * Given an SDL_Rect and the desired scaling (0.0f is the centre, 1.0f the edge) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_rect(SDL_Rect within, float x, float y, float width, float height) {
    // Are we using the screen size?
    if (within.w == 0 && within.h == 0) {
        // Get the size of the window.
        SDL_GetRendererOutputSize(gameData.renderer, &within.w, &within.h);
    }
    SDL_Point centre = get_rect_centre(within);
    x = x * -1;
    y = y * -1;
    // Calculate width and height.
    int w = (width * centre.x);
    int h = (height * centre.y);
    // Ensure that the scale will center the rectangle at the desired location.
    SDL_Rect new = { .x = ((x + 1.0f) * centre.x) - (w / 2), .y = ((y + 1.0f) * centre.y) - (h / 2),
            .w = w, .h = h};
    // DEBUG_LOG("%d %d %d %d\n", new.x, new.y, new.w, new.h);
    return new;
}

/**
 * Given an SDL_Rect and the desired scaling (0.0f is the centre, 1.0f the edge) modify
 * the x and y coords to match the desired location.
 */
SDL_Rect transform_right_angle_rect(SDL_Rect within, float x, float y, float width) {
    // Are we using the screen size?
    if (within.w == 0 && within.h == 0) {
        // Get the size of the window.
        SDL_GetRendererOutputSize(gameData.renderer, &within.w, &within.h);
    }
    SDL_Point centre = get_rect_centre(within);
    x = x * -1;
    y = y * -1;
    // Calculate width and height.
    int w = (width * centre.x);
    // Ensure that the scale will center the rectangle at the desired location.
    SDL_Rect new = { .x = ((x + 1.0f) * centre.x) - (w / 2), .y = ((y + 1.0f) * centre.y) - (w / 2),
            .w = w, .h = w};
    // DEBUG_LOG("%d %d %d %d\n", new.x, new.y, new.w, new.h);
    return new;
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
}

/**
 * Returns true if the point is within the provided rectangle.
 */
bool is_point_inside(SDL_Rect within, SDL_Point point) {
    return point.x > within.x && point.x < within.x + within.w &&
            point.y > within.y && point.y < within.y + within.h;
}
