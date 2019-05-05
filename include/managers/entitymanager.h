#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <stdbool.h>

#include "../entities/entity.h"
#include "../managers/assetstack.h"

/**
 * Holds total number of entites.
 */
typedef struct EntiyManager {
    unsigned int current;
    unsigned int maximum;
    Entity* entities;
} EntityManager;

/**
 * Create new entity manager.
 */
bool init_entity_manager(EntityManager* entityManager);

/**
 * Add a new entity to the manager if there is space, if not allocate more space for new entitiy.
 */
void add_entity(EntityManager* entitiyManager, AssetStack* assets, Entity (*init_entity)(AssetStack* assets));

/**
 * Remove all entites that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void clean_entities(EntityManager* entityManager);

/**
 * Free entity manager.
 */
void free_entities(EntityManager* entityManager);

#endif
