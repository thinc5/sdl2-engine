#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/config.h"
#include "../include/timer.h"

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager initFPSManager(void) {
    return (FrameRateManager) {
        .capped = FPS_CAPPED,
        .cappedFPS = FRAME_CAP,
        .currentFPS = 0,
        .timer = initTimer(),
    };
}

/**
 * Initialise a timer.
 */
Timer initTimer(void) {
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
void startTimer(Timer* t) {
    t->started = true;
    t->paused = false;
    t->startTime = SDL_GetTicks();
};

/**
 *  Stop the timer.
 */
void stopTimer(Timer* t) {
    t->started = false;
    t->paused = false;
};

/**
 * Pause the timer.
 */
void pauseTimer(Timer* t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pausedTime = SDL_GetTicks() - t->startTime;
    }
}

/**
 * Unpasue the timer.
 */
void unpauseTimer(Timer* t) {
    if (t->paused) {
        t->paused = false;
        t->startTime = SDL_GetTicks() - t->pausedTime;
        t->pausedTime = 0;
    }
}

/**
 * Return the current ticks of the timer.
 */
uint32_t getTimerTicks(Timer* t) {
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
 * Maintain capped framerate.
 */
void updateTimer(FrameRateManager* f) {
    if (f->capped) {
        int cap = (1000 / f->cappedFPS);
        int diff = SDL_GetTicks() - getTimerTicks(&f->timer);
        if (diff < cap) {
            SDL_Delay(cap - diff);
            f->timer.startTime = SDL_GetTicks();
        }
    }
    // Implement frame rate display and update
    // if (SDL_GetTicks() - second > 1000) {
    //     f->currentFPS = frames;
    // }
}

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f) {
    printf("FPS: %d\n", f->currentFPS);
};

