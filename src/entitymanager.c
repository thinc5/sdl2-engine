#include "../include/game.h"
#include "../include/entity.h"
#include "../include/entitymanager.h"

/**
 * Create new entity manager.
 */
EntityManager initEntityManager(void) {
    return (EntityManager) {
        .current = 0,
        .maximum = 5,
        .entities = (Entity*) malloc(sizeof(Entity) * 5)
    };
}

/**
 * Add a new entity to the manager if there is space, if not allocate more space for new entity.
 */
void addEntity(EntityManager* entityManager, AssetRegistry* assets, Entity (*initEntity)(AssetRegistry* assets)) {
    // Check if we have any space left for a new entity.
    if (entityManager->current + 1 >= entityManager->maximum) {
        entityManager->maximum *= 2;
        entityManager->entities = (Entity*) realloc(entityManager, sizeof(Entity) * entityManager->maximum);
    }
    // Create new entity with provided constructor.
    entityManager->entities[entityManager->current] = initEntity(assets);
    entityManager->current++;
}

/**
 * Remove all entities that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void cleanEntities(EntityManager* entityManager) {
    for (int i = 0; i < entityManager->current; i++) {
        // Does this entity need to be removed?
        if (entityManager->entities[i].remove) {
            // Shift over it
            entityManager->entities[i] = (Entity) {};
            for (int j = i; i < (entityManager->current) - 1; j++) {
                entityManager->entities[j] = entityManager->entities[j + 1];
            }
        }
    }
    if (entityManager->current < (entityManager->maximum / 2) - 1) {
        entityManager->maximum /= 2;
        entityManager->entities = (Entity*) realloc(entityManager->entities, sizeof(Entity) * entityManager->maximum);
    }
}