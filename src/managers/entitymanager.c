#include <stdlib.h>
#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"
#include "../../include/entities/entity.h"
#include "../../include/managers/entitymanager.h"

/**
 * Create new entity manager.
 */
bool init_entity_manager(EntityManager* entityManager) {
    entityManager->current = 0;
    entityManager->maximum = 5;
    entityManager->entities = (Entity*) malloc(sizeof(Entity) * 5);
    return true;
}

/**
 * Add a new entity to the manager if there is space, if not allocate
 * more space for new entity.
 */
void add_entity(EntityManager* entityManager, Entity (*init_entity)(void), SDL_Rect rect) {
    // Check if we have any space left for a new entity.
    if (entityManager->current + 1 >= entityManager->maximum) {
        entityManager->maximum *= 2;
        entityManager->entities = (Entity*) realloc(entityManager->entities,
	            sizeof(Entity) * entityManager->maximum);
    }
    // Create new entity with provided constructor.
    entityManager->entities[entityManager->current] = init_entity();
    // Set the width and height.
    entityManager->entities[entityManager->current].position = rect;
    entityManager->current++;
}

/**
 * Remove all entities that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void clean_entities(EntityManager* entityManager) {
    for (int i = 0; i < entityManager->current; i++) {
        // Does this entity need to be removed?
        if (entityManager->entities[i].remove) {
            // Shift over it.
            entityManager->entities[i] = (Entity) { 0 };
            for (int j = i; j < (entityManager->current) - 1; j++) {
                entityManager->entities[j] = entityManager->entities[j + 1];
            }
            entityManager->current--;
        }
    }
    // Shrink if we have removed entities.
    if (entityManager->current < (entityManager->maximum / 2) - 1) {
        entityManager->maximum /= 2;
        entityManager->entities = (Entity*) realloc(entityManager->entities, sizeof(Entity) * entityManager->maximum);
        // DEBUG INFO_LOG("Current entities = %d, Maximum = %d\n", entityManager->current, entityManager->maximum);
    }
}

/**
 * Free entity manager.
 */
void free_entities(EntityManager* entityManager) {
    free(entityManager->entities);
}

