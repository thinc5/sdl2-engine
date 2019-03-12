#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "game.h"

/**
 * The event type and the function to execute.
 */
typedef struct Event {
    char* name;
    void* handler;
} Event;

/**
 * Holds all registered keycodes with their events.
 */
typedef struct EventManager {
    int total;
    Event** events;
} EventManager;

/**
 * Initialize the event manager with basic inputs.
 */
void initEventManager(EventManager* em);

/**
 * Check the event against the registered events and execute
 * associated command.
 */
void checkEvent(SDL_Keycode);

void scene1Manager(GameData* gameData, int* pickedTex);

#endif