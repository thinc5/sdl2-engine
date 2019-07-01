#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "../entities/entity.h"
#include "../scenes/scene.h"

/**
 * Process input depending on the context of the current scene.
 */
void default_handler(void);

#endif

