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
    return (SDL_Rect) {
        .x = ((x + 1.0f) * centre.x) - (w / 2),
        .y = ((y + 1.0f) * centre.y) - (h / 2),
        .w = w,
        .h = h
    };
}

/**
 * Given an SDL_Rect and the desired scaling (0.0f is the centre, 1.0f the edge) modify
 * the x and y coords to match the desired location while ensuring that you end up with a
 * square that fits within the bounds provided..
 */
SDL_Rect transform_right_angle_square(SDL_Rect within, float x, float y, float width, float height) {
    // Are we using the screen size?
    if (within.w == 0 && within.h == 0) {
        // Get the size of the window.
        SDL_GetRendererOutputSize(gameData.renderer, &within.w, &within.h);
    }
    // Invert the floats.
    x = x * -1;
    y = y * -1;

    SDL_Point centre = get_rect_centre(within);
    // Calculate width and height.
    int w = (width * centre.x);
    int h = (height * centre.y);

    // Find out which is smaller?
    int min = w <= h ? w : h;

    // Ensure that the scale will center the rectangle at the desired location.
    SDL_Rect new = {
        .x = ((x + 1.0f) * centre.x) - (min / 2),
        .y = ((y + 1.0f) * centre.y) - (min / 2),
        .w = min,
        .h = min
    };
    // DEBUG_LOG("%d %d %d %d\n", new.x, new.y, new.w, new.h);
    return new;
}

/**
 * Given an SDL_Rect and the desired scaling (0.0f is the centre, 1.0f the edge) modify
 * the x and y coords to create a right angled rectangle.
 */
SDL_Rect transform_right_angle_rect(SDL_Rect within, float x, float y, float width, float height,
            int unitX, int unitY) {
    // Are we using the screen size?
    if (within.w == 0 && within.h == 0) {
        // Get the size of the window.
        SDL_GetRendererOutputSize(gameData.renderer, &within.w, &within.h);
    }
    // Invert the floats.
    x = x * -1;
    y = y * -1;

    SDL_Point centre = get_rect_centre(within);
    // Calculate width and height.
    int w = (width * centre.x);
    int h = (height * centre.y);
    int wMultiple = w / unitX;
    int hMultiple = h / unitY;
    int wRecalc = wMultiple * unitX;
    int hRecalc = hMultiple * unitY;
    bool largerW = w >= h ? true : false;

    // Find out which is smaller and recalc the larger.
    if (largerW) {
        wRecalc = hMultiple * unitX;
    } else {
        hRecalc = wMultiple * unitY;
    }
    
    // Find the greatest common denominator.
    return (SDL_Rect) {
        .x = ((x + 1.0f) * centre.x) - (wRecalc / 2),
        .y = ((y + 1.0f) * centre.y) - (hRecalc / 2),
        .w = wRecalc,
        .h = hRecalc
    };
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
