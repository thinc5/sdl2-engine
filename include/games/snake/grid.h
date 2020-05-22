#ifndef SNAKEGRID_H
#define SNAKEGRID_H

#include "../../entities/entity.h"

/**
 * Information about the Snake Game Grid.
 */
typedef struct Grid {
    uint32_t x;
    uint16_t y;
} Grid;

Entity init_snake_grid(void);

#endif
