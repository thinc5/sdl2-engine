#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/config.h"
#include "../include/timer.h"

/**
 * Initialise the timer using some global constants defined in config.h.
 */
void initFPSManager(FrameRateManager* f) {
    f->capped = FPS_CAPPED;
    f->cappedFPS = FRAME_CAP;
    f->currentFPS = 0;
    initTimer(&f->timer);
}

/**
 * Initialise a timer.
 */
void initTimer(Timer* t) {
    t->started = false;
    t->paused = false;
    t->startTime = 0;
    t->pausedTime = 0;
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
            return SDL_GetTicks() + t->startTime;
        }
    }
    return 0;
}

/**
 * Maintain capped framerate.
 */
void updateTimer(FrameRateManager* f) {
    f->currentFPS++;
    if (f->capped && (getTimerTicks(&f->timer) < (1000 / f->cappedFPS))) {
        SDL_Delay((1000 / f->cappedFPS) - getTimerTicks(&f->timer));
        // Reset timer
        f->timer.startTime = SDL_GetTicks();
        f->currentFPS = 0;
    }
    
    
}

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f) {
    printf("FPS: %d\n", f->currentFPS);
};