#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <stdbool.h>

#include "../entities/entity.h"
#include "../managers/assetmanager.h"

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
bool initEntityManager(EntityManager* entityManager);

/**
 * Add a new entity to the manager if there is space, if not allocate more space for new entitiy.
 */
void addEntity(EntityManager* entitiyManager, AssetRegistry* assets, Entity (*initEntity)(AssetRegistry* assets));

/**
 * Remove all entites that are marked to delete then shift all right of the removed entity left to conserve space.
 */
void cleanEntities(EntityManager* entityManager);

/**
 * Free entity manager.
 */
 void freeEntities(EntityManager* entityManager);

#endif