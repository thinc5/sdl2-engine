#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>

/**
 * A timer.
 */
typedef struct Timer {
    bool started;
    bool paused;
    uint32_t startTime;
    uint32_t pausedTime;
} Timer;

/**
 * Initialise a timer.
 */
Timer init_timer(void);

/**
 * Start the fps timer.
 */
void start_timer(Timer* t);
/**
 *  Stop the timer.
 */
void stop_timer(Timer* t);

/**
 * Pause the timer.
 */
void pause_timer(Timer* t);

/**
 * Unpasue the timer.
 */
void unpause_timer(Timer* t);

/**
 * Return the current ticks of the timer.
 */
uint32_t get_timer_ticks(Timer* t);

/**
 * Check if provided time in ms has elapsed already.
 */
bool time_elapsed(Timer* t, uint32_t ms);

#endif
