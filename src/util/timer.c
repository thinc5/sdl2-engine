#include <SDL2/SDL.h>

#include <stdio.h>

#include "../../include/config.h"
#include "../../include/util/timer.h"

/**
 * Initialise a timer.
 */
Timer init_timer(void) {
    return (Timer) {
        .started = false,
        .paused = false,
        .startTime = 0,
        .pausedTime = 0.
    };
}

/**
 * Start the fps timer.
 */
void start_timer(Timer* t) {
    t->started = true;
    t->paused = false;
    t->startTime = SDL_GetTicks();
}

/**
 *  Stop the timer.
 */
void stop_timer(Timer* t) {
    t->started = false;
    t->paused = false;
}

/**
 * Pause the timer.
 */
void pause_timer(Timer* t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pausedTime = SDL_GetTicks() - t->startTime;
    }
}

/**
 * Unpauses the timer.
 */
void unpause_timer(Timer* t) {
    if (t->paused) {
        t->paused = false;
        t->startTime = SDL_GetTicks() - t->pausedTime;
        t->pausedTime = 0;
    }
}

/**
 * Return the current ticks of the timer.
 */
uint32_t get_timer_ticks(Timer* t) {
    if (t->started) {
        if (t->paused) {
            return t->pausedTime;
        } else {
            return t->startTime;
        }
    }
    return 0;
}

/**
 * Check if provided time in ms has elapsed already.
 */
bool time_elapsed(Timer* t, uint32_t ms) {
    uint32_t elapsed = SDL_GetTicks() - get_timer_ticks(t);
    if (elapsed >= ms) {
        return true;
    }
    return false;
}

