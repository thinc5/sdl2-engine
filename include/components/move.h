#ifndef C_MOVE_H
#define C_MOVE_H

#include "../component.h"

/**
 * Possible directions of movement.
 */
typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

void move(void* e, Direction d, int pixels);

#endif