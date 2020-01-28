#ifndef CAT_STATE_H
#define CAT_STATE_H

#include <stdint.h>

#include "../../entities/entity.h"

/**
 * The debug scene's state struct.
 */
typedef struct CatState {
    // Player score.
    uint32_t score;
    // Remaining time.
    uint32_t remaining_time;
    uint32_t last_time;
} CatState;

Entity init_cat_state(void);

#endif

