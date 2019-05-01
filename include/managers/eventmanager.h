#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "entities/entity.h"

/**
 * Check the event against the registered events and execute
 * associated command.
 */
void check_event(SDL_Keycode);

/**
 * Process input depending on the context of the current scene.
 */
void default_handler(void* game);

#endif
