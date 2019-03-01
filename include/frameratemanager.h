#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

#include <SDL2/SDL.h>

#include <stdio.h>

/**
 * A frame rate counter.
 */
typedef struct FrameRateManager {
    uint32_t startTime;
    uint32_t endTime;
    uint32_t delta;
    short fpsCap;
    short timePerFrame;
} FrameRateManager;

/**
 * Set the new start time at the beginning of a frame.
 */
void setStartTime(FrameRateManager* f);

/**
 *  Set the end time at the ned of a frame.
 */
void setEndTime(FrameRateManager* f);

/**
 * Show the current average fps.
 */
void showFPS(FrameRateManager* f);

#endif