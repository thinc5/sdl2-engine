#include <SDL2/SDL.h>

#include <stdio.h>

#include "../include/frameratemanager.h"

/**
 * Set the new start time at the beginning of a frame.
 */
void setStartTime(FrameRateManager* f) {
    if (!f->startTime) {
        f->startTime = SDL_GetTicks();
    } else {
        f->delta = f->endTime - f->startTime;
    }
};

/**
 *  Set the end time at the ned of a frame.
 */
void setEndTime(FrameRateManager* f) {
    if (f->delta < f->timePerFrame) {
        SDL_Delay(f->timePerFrame - f->delta);
    }
    f->startTime = f->endTime;
    f->endTime = SDL_GetTicks();
};

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f) {
    if (f->delta > f->timePerFrame) {
        f->fps = 1000 / f->delta;
    }
    printf("FPS: %d\n", f->fps);
};