#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <stdbool.h>

#include "timer.h"

/**
 * A frame rate counter.
 */
typedef struct FrameRateManager {
    bool capped;
    short cappedFPS;
    short currentFPS;
    Timer timer;
} FrameRateManager;

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager init_fps(void);

/**
 * Maintain capped framerate.
 */
void cap_fps(FrameRateManager* f);

/**
 * Show the current average fps.
 */
int get_fps(FrameRateManager* f);

#endif
