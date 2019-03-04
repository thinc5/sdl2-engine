#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/config.h"
#include "../include/frameratemanager.h"

/**
 * Iniilise the timer using some global constants defined in config.h.
 */
void initTimer(FrameRateManager* f) {
    f->capped = FPS_CAPPED;
    f->started = false;
    f->paused = false;
    f->startTime = 0;
    f->pausedTime = 0;
    f->cappedFPS = FRAME_CAP;
    f->currentFPS = 0;
}

/**
 * Start the fps timer.
 */
void startTimer(FrameRateManager* f) {
    f->started = true;
    f->paused = false;
    f->startTime = SDL_GetTicks();
};

/**
 *  Stop the timer.
 */
void stopTimer(FrameRateManager* f) {
    f->started = false;
    f->paused = false;
};

/**
 * Pause the timer.
 */
void pauseTimer(FrameRateManager* f) {
    if (f->started && !f->paused) {
        f->paused = true;
        f->pausedTime = SDL_GetTicks() - f->startTime;
    }
}

/**
 * Unpasue the timer.
 */
void unpauseTimer(FrameRateManager* f) {
    if (f->paused) {
        f->paused = false;
        f->startTime = SDL_GetTicks() - f->pausedTime;
        f->pausedTime = 0;
    }
}

/**
 * Return the current ticks of the timer.
 */
uint32_t getTimerTicks(FrameRateManager* f) {
    if (f->started) {
        if (f->paused) {
            return f->pausedTime;
        } else {
            return SDL_GetTicks() + f->startTime;
        }
    }
    return 0;
}

/**
 * Maintain capped framerate.
 */
void updateTimer(FrameRateManager* f) {
    f->currentFPS++;
    if (f->capped &&  (getTimerTicks(f) < 1000 / f->cappedFPS)) {
        SDL_Delay((1000 / f->cappedFPS) - getTimerTicks(f));
    }
}

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f) {
    printf("FPS: %d\n", f->currentFPS);
};