#ifndef E_SNAKE_H
#define E_SNAKE_H

#include <stdint.h>

#include "../../entities/entity.h"
#include "../../components/move.h"

#define MAX_SNAKE_SIZE 100

/**
 * Information about the Snake.
 */
typedef struct Snake {
    // Snake length
    uint32_t size;
    // Snake direction
    Direction dir;
    // Snake next dir
    Direction next_dir;
    // Snake location
    SDL_Point sections[MAX_SNAKE_SIZE];
} Snake;

/**
 * Initializes the snake entity.
 */
Entity init_snake(void);

#endif
