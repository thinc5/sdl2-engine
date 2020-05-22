#include <SDL2/SDL.h>

#include <stdio.h>

#include "../../include/debug.h"
#include "../../include/util/timer.h"
#include "../../include/util/framerate.h"
#include "../../include/config.h"

/**
 * Initialise the timer using some global constants defined in config.h.
 */
FrameRateManager init_fps(void) {
    FrameRateManager f = (FrameRateManager) {
        .capped = FPS_CAPPED,
        .cappedFPS = FRAME_CAP,
        .currentFPS = 0,
        .timer = init_timer(),
    };
    start_timer(&f.timer);
    return f;
}

/**
 * Maintain capped framerate.
 */
void cap_fps(FrameRateManager* f) {
    if (f->capped) {
        int cap = (1000 / f->cappedFPS);
        // Have we "finished" early?
        if (!time_elapsed(&f->timer, cap)) {
            // Delay until we are ready to continue.
            // DEBUG INFO_LOG("Delaying: %d ms\n", cap - (SDL_GetTicks() - f->timer.startTime));
            SDL_Delay(cap - (SDL_GetTicks() - f->timer.startTime));
        }
        f->timer.startTime = SDL_GetTicks();
    }
}

/**
 * Show the current average fps.
 */
int show_fps(FrameRateManager* f) {
    DEBUG_LOG("FPS: %d\n", f->currentFPS);
    return f->currentFPS;
}
