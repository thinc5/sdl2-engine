#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "entity.h"
#include "assetmanager.h"

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
EntityManager initEntityManager(void);

/**
 * Add a new entity to the manager if there is space, if not allocate more space for new entitiy.
 */
void addEntity(EntityManager* entitiyManager, AssetRegistry* assets, Entity (*initEntity)(AssetRegistry* assets));

/**
 * Remove all entites that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void cleanEntities(EntityManager* entityManager);

#endif