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
 * Add a new entity to the manager if there is space, if not allocate more space for new entitiy.
 */
void addEntity(EntityManager* entitiyManager, AssetRegistry* assets, Entity (*initEntity)(AssetRegistry* assets)) {
    // Check if we have any space left for a new entity.
    if (entitiyManager->current + 1 >= entitiyManager->maximum) {
        entitiyManager->maximum *= 2;
        entitiyManager->entities = (Entity*) realloc(entitiyManager, sizeof(Entity) * entitiyManager->maximum);
    }
    // Create new entity with provided constructor.
    entitiyManager->entities[entitiyManager->current] = initEntity(assets);
    entitiyManager->current++;
}

/**
 * Remove all entities that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void cleanEntities(EntityManager* entityManager) {
    for (int i = 0; i < entityManager->current; i++) {
        // Does this entity need to be removed?
        if (entityManager->entities[i].remove) {
            // Shift over it
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