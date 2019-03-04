#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdbool.h>

/**
 * A frame rate counter.
 */
typedef struct FrameRateManager {
    bool capped;
    bool started;
    bool paused;
    uint32_t startTime;
    uint32_t pausedTime;
    short cappedFPS;
    short currentFPS;
} FrameRateManager;

/**
 * Iniilise the timer using some global constants defined in config.h.
 */
void initTimer(FrameRateManager* f);

/**
 * Start the fps timer.
 */
void startTimer(FrameRateManager* f);
/**
 *  Stop the timer.
 */
void stopTimer(FrameRateManager* f);

/**
 * Pause the timer.
 */
void pauseTimer(FrameRateManager* f);

/**
 * Unpasue the timer.
 */
void unpauseTimer(FrameRateManager* f);

/**
 * Return the current ticks of the timer.
 */
uint32_t getTimerTicks(FrameRateManager* f);

/**
 * Maintain capped framerate.
 */
void updateTimer(FrameRateManager* f);
/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f);

#endif