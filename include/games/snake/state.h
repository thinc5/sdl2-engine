#ifndef SNAKESTATE_H
#define SNAKESTATE_H

#include <stdint.h>

#include "../../components/move.h"
#include "../../entities/entity.h"

#include "grid.h"
#include "food.h"
#include "snake.h"

#define MAX_FOOD 5

/**
 * Different states of the game.
 */
typedef enum SnakeGameStatus {
    SNAKE_ALIVE,
    SNAKE_DEAD
} SnakeGameStatus;

/**
 * The snake game's state struct.
 */
typedef struct SnakeState {
    // Game status.
    SnakeGameStatus status;
    // Player score.
    uint32_t score;
    // Game starting time.
    uint32_t starting_time;
    uint32_t duration;
    // Game speed factor.
    uint32_t game_speed;
    // Game grid
    Grid grid;
    // Snake instance.
    Snake snake;
    Food food[MAX_FOOD];
} SnakeState;

#endif