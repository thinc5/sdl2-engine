#ifndef E_FOOD_H
#define E_FOOD_H

#include "../../entities/entity.h"

/**
 * 
 */
typedef struct Food {
    uint16_t x;
    uint16_t y;
    uint16_t score;
    uint32_t lifetime;
} Food;

/**
 * Initializes the snake food.
 */
Entity init_food(void);

#endif

