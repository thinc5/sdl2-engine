#ifndef E_SNAKE_H
#define E_SNAKE_H

#include <stdint.h>

#include "../../entities/entity.h"
#include "../../components/move.h"

/**
 * Information about the Snake.
 */
typedef struct Snake {
    // Snake length
    uint32_t size;
    // Snake direction
    Direction dir;
    // Snake location
    uint16_t x;
    uint16_t y;
} Snake;

/**
 * Initializes the snake entity.
 */
Entity init_snake(void);

#endif
