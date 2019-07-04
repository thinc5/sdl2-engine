#ifndef DEBUGSCENE_H
#define DEBUGSCENE_H

#include "../scenes/scene.h"

/**
 * The debug scene's state struct.
 */
typedef struct CatState {
    uint32_t score;
} CatState;

void init_debug_scene(void);

#endif

