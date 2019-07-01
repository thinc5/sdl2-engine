#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/entities/entity.h"
#include "../../include/components/component.h"
#include "../../include/util/timer.h"
#include "../../include/util/camera.h"
#include "../../include/entities/cat.h"
#include "../../include/components/move.h"

/**
 * Behaviour of cat when clicked.
 */
static void cat_right_clicked(void* e) {
    Entity* entity = (Entity*) e;
    unsigned int fattenBy = 10;
    entity->position.w += fattenBy;
    entity->position.h += fattenBy;
    entity->position.x -= fattenBy / 2;
    entity->position.y -= fattenBy / 2;
}

/**
 * Behaviour of cat when dragged.
 */
static void cat_dragged(void *e, int x, int y) {
    INFO_LOG("Dragged cat!\n");
}

/**
 * On tick.
 * Limit time via a local timer initialized using a static variable.
 */
static void cat_on_tick(void* e) {
    Entity* entity = (Entity*) e;
    if (!entity->timers[0].started) {
        start_timer(&entity->timers[0]);
    }
    if (time_elapsed(&entity->timers[0], 100)) {
        // Pick which direction we are moving.
        unsigned int direction = rand() % 4;
        entity->components[Moved].call(entity, direction, 10);
        entity->timers[0].startTime = SDL_GetTicks();
    }
}

/**
 * Initializes the cat entity and its components.
 */
Entity init_cat(void) {
    Entity cat;
    // Load cat assets make more flexable and specific later.
    if (!init_entity(&cat, "cat4.jpg", "meow1.ogg")) {
        ERROR_LOG("Could not initialize cat entity.\n");
        return (Entity) { 0 };
    }
    //cat.stats[0] = 10;
    // Cat specific specifications.
    
    // Starting position.
    cat.position.x = 400;
    cat.position.y = 400;

    // Width and height.
    cat.position.w = 20;
    cat.position.h = 20;

    // Load cat components.
    cat.timers[0] = init_timer();
    cat.components[Moved].call = &move;
    cat.components[LeftClicked] = cat.components[Deleted];
    cat.components[RightClicked].call = &cat_right_clicked;
    cat.components[Dragged].call = &cat_dragged;
    cat.components[OnTick].call = &cat_on_tick;

    return cat;
}
