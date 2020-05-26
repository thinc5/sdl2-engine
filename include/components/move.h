#ifndef C_MOVE_H
#define C_MOVE_H

#include "../../include/components/component.h"

/**
 * Possible directions of movement.
 */
typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DIRECTIONS
} Direction;

void move(void* e, Direction d, int pixels, SDL_Rect bounds);

#endif
