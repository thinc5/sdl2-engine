#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "timer.h"
#include "camera.h"

// Window dimensions.
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// Standard unit height, size of food, snake etc.
#define UNIT_SIZE  (WINDOW_WIDTH / 20)

// Size of the game's bounding box.
#define BOX_WIDTH (UNIT_SIZE * 16)
#define BOX_HEIGHT (UNIT_SIZE * 9)

// How large can the snake get?
#define SNAKE_MAX 20

// How many pieces of food can spawn at once?
#define FOOD_MAX 4

typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct GameData {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    // Game logic stuff.
    SDL_Rect bounds;            // Size of game space.
    Timer timer;                // Keep track of game speed.
    uint32_t speed;
    SDL_Point snake[SNAKE_MAX]; // Location of each snake component.
    int snake_size;                   // Size of the snake.
    Direction dir;              // Current direction of the snake.
    SDL_Point food[FOOD_MAX];   // Location of all "spawned" food pieces.
    int food_size;
} GameData;

/**
 *  Initialize SDL components.
 */
static bool init_modules(void) {
    // Start SDL and components.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return false;
    }
    return true;
 }

/**
 * Quit SDL components.
 */
static void quit_modules(void) {
    SDL_Quit();
 }

/**
 * Shift the snake along.
 */
static void shift_snake(GameData* data) {
    for (int i = data->snake_size - 1; i > 0; i--) {
        data->snake[i - 1] = data->snake[i]; 
    }
    switch (data->dir) {
        case LEFT:
            data->snake[0].x -= UNIT_SIZE;
            break;
        case RIGHT:
            data->snake[0].x += UNIT_SIZE;
            break;
        case UP:
            data->snake[0].y -= UNIT_SIZE;
            break;
        case DOWN:
            data->snake[0].y += UNIT_SIZE;
            break;
    }
}

/**
 * Check snake collisions.
 */
static void snake_collision(GameData* data) {
    // We only check collision for head since it's the only unit moving to a new location.
    // Has it hit itself?
    SDL_Rect body = {0, 0, UNIT_SIZE, UNIT_SIZE};    
    for (int i = 1; i < data->snake_size; i++) {
        body.x = data->snake[i].x;
        body.y = data->snake[i].y;
        if (is_collision(data->snake[0].x, data->snake[0].y, body)) {
            // Game over.
            return;
        }
    }
    // Has it hit food?
    for (int i = 1; i < data->food_size; i++) {
        body.x = data->food[i].x;
        body.y = data->food[i].y;
        if (is_collision(data->snake[0].x, data->snake[0].y, body)) {
            // we have a food collision.
            data->snake_size++;
            return;
        }
    }
}

/**
 * The method that decides if we spawn food.
 */
static void spawn_food(GameData* data) {
    // Is there room for more food?
    if (data->food_size >= FOOD_MAX) {
        return;
    }
    // We have a 30% chance every tick to try add food.
    if (rand() % 3 != 0) {
        return;
    }
    // Find a random location within our grid and if it's unnocupied add the food to the game.
    
}

/**
 * The main game loop.
 */
static void loop(void* arg) {
    GameData* data = (GameData*) arg;

    // Has enough time passed?
    if (!time_elapsed(&data->timer, data->speed)) {
        return;
    }

    // Handle input
    while (SDL_PollEvent(&data->event)) {
        switch (data->event.key.keysym.sym) {
            case SDLK_LEFT:
                data->dir = LEFT;
                break;
            case SDLK_RIGHT:
                data->dir = RIGHT;
                break;
            case SDLK_UP:
                data->dir = UP;
                break;
            case SDLK_DOWN:
                data->dir = DOWN;
                break;
        }
    }

    // Move snake and process collision.
    shift_snake(data);

    // Has snake hit food or a wall or itself?
    snake_collision(data);
    
    // Have the conditions been met to spawn more food?
    spawn_food(data);

    // Render background.
    SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 255);
    SDL_RenderClear(data->renderer);

    // Draw the background.
    SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(data->renderer, &data->bounds);

    // Draw the snake.
    SDL_SetRenderDrawColor(data->renderer, 0, 255, 255, 255);
    SDL_Rect pos = {0, 0, UNIT_SIZE, UNIT_SIZE};
    for (int i = 0; i < data->snake_size; i++) {
        pos.x = data->snake[i].x;
        pos.y = data->snake[i].y;
        SDL_RenderFillRect(data->renderer, &pos);
    }

	SDL_RenderPresent(data->renderer);
}

/**
 * Entry point for the engine.
 */
int main(int argc, char** argv) {
    // Start all major game components.
    if (!init_modules()) {
        return 1;
    }

    // Init the game.
    GameData data;
    data.bounds = (SDL_Rect) {(WINDOW_WIDTH / 2) - (BOX_WIDTH / 2), (WINDOW_HEIGHT / 2) - (BOX_HEIGHT / 2), BOX_WIDTH, BOX_HEIGHT};
    data.timer = init_timer();
    start_timer(&data.timer);
    data.speed = 1000;
    data.dir = LEFT;
    data.snake_size = 1;
    data.snake[0] = (SDL_Point) {(WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2)};
    data.food_size = 0;

    // Set up window and renderer.
    data.window = SDL_CreateWindow("lul", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    data.renderer = SDL_CreateRenderer(data.window, -1, SDL_RENDERER_ACCELERATED);

    // Set default background colour.
    SDL_SetRenderDrawColor(data.renderer, 255, 255, 255, 255);

    // Start main loop.
    emscripten_set_main_loop_arg(&loop, &data, -1, -1);

    // Clean up.
    SDL_DestroyRenderer(data.renderer);
    SDL_DestroyWindow(data.window);
    quit_modules();
    return 0;
}

