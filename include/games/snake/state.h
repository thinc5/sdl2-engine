#ifndef SNAKESTATE_H
#define SNAKESTATE_H

#include <stdint.h>

#include "../../components/move.h"
#include "../../entities/entity.h"

/**
 * The snake game's state struct.
 */
typedef struct SnakeState {
    // Player score.
    uint32_t score;
    // Remaining time.
    uint32_t remaining_time;
    uint32_t last_time;
    // Snake length
    uint32_t snake_size;
    Direction snake_dir;
    // Game speed.
    uint32_t game_speed;
} SnakeState;

Entity init_snake_state(void);

#endif

