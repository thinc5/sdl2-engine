#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdint.h>
#include <stdlib.h>

#include "../../../include/config.h"
#include "../../../include/debug.h"
#include "../../../include/game.h"
#include "../../../include/games/snake/state.h"
#include "../../../include/components/move.h"
#include "../../../include/entities/entity.h"
#include "../../../include/rendering/renderertemplates.h"
#include "../../../include/util/camera.h"

#include "../../../include/games/snake/food.h"

#define SPAWN_DELAY 5000 // Spawn a piece of food every 5 seconds.

#define FOOD_LIFETIME 10000 // Food lasts 10 seconds.

/**
 * Spawn a piece of food.
 */
void spawn_food(uint32_t lifetime, uint16_t score) {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    int freePos = -1;
    Food food = { 0 };
    for (int pos = 0; pos < MAX_FOOD; pos++) {
        Food food = state->food[pos];
        if (food.lifetime == 0) {
            freePos = pos;
            break;
        }
    }
    if (freePos == -1) {
        // We were unable to find a free slot, ignore call and return.
        return;
    }

    // Generate random food location
    while (1) {
        food.x = rand() % state->grid.x;
        food.y = rand() % state->grid.y;
        // Check we have not spawned on top of any other food.
        for (int i = 0; i < MAX_FOOD; i++) {
            if (food.x == state->food[i].x && food.y == state->food[i].y) {
                continue;
            }
        }
        // Check we have not spawned on top of the snake.
        for (int i = 0; i < state->snake.size; i++) {
            if (food.x == state->snake.sections[i].x && food.y == state->snake.sections[i].y) {
                continue;
            }
        }
        break;
    }
    // Create the expiry time.
    food.lifetime = lifetime + SDL_GetTicks();
    food.score = score;
    // Insert into the array.
    state->food[freePos] = food;
}

/**
 * Remove old expired food YUCK!
 */
void expire_food() {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    // Check we have not spawned on top of any other food.
    uint32_t currentTime = SDL_GetTicks();
    for (int i = 0; i < MAX_FOOD; i++) {
        if (state->food[i].lifetime < currentTime) {
            state->food[i] = (Food) { 0 };
        }
    }
}

/**
 * Render all pieces of food.
 */
void render_food() {
    SnakeState* state = (SnakeState*) gameData.scene->state;
    float gridWidth = state->grid.pos.w / state->grid.x;
    float gridHeight = state->grid.pos.h / state->grid.y;
    // Get the first food piece.
    for (int pos = 0; pos < MAX_FOOD; pos++) {
        Food food = state->food[pos];
        if (food.lifetime == 0) {
            continue;
        }
        SDL_Rect target = {
            .w = gridWidth,
            .h = gridHeight,
            .x = state->grid.pos.x + (gridWidth * food.x),
            .y = state->grid.pos.y + (gridHeight * food.y)
        };
        SDL_Colour colour = { 150, 0, 150, 255 };
        // We fade out as we get expired.
        // How expired are we?
        int32_t remainingTime = food.lifetime - SDL_GetTicks();
        float opacityPercent =  ((float) remainingTime / (float) FOOD_LIFETIME);
        float opacity = (opacityPercent * 255);
         colour.a = (int) opacity;
        //DEBUG_LOG("Remaining time: %d Food opacity: %f %% %d\n", remainingTime, opacityPercent, colour.a);
        render_rectangle(&target, colour, true);
    }
}

/**
 * 
 */
void food_on_tick(void* e) {
    Entity* food = e;
    if (!food->timers[0].started) {
        start_timer(&food->timers[0]);
    }
    if (time_elapsed(&food->timers[0], SPAWN_DELAY)) {
        // Spawn a new piece of food.
        spawn_food(FOOD_LIFETIME, 5);
        // Expire old food.
        expire_food();
        // Reset the timer.
        food->timers[0].startTime = SDL_GetTicks();
    }
}

/**
 * Initializes the snake food.
 */
Entity init_food(void) {
    Entity food;
    // Load snake assets.
    if (!init_entity(&food, NULL, NULL)) {
        ERROR_LOG("Could not initialize snake entity.\n");
        return (Entity) { 0 };
    }
    // Load cat components.
    food.timers[0] = init_timer();
    food.components[Render].call = &render_food;
    food.components[OnTick].call = &food_on_tick;
    return food;
}
