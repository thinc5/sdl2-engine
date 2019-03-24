#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "assetmanager.h"
#include "component.h"
#include "timer.h"


/**
 * Possible stats an entity can have.
 */
 typedef enum Stats {
    HP,
    MaxHP,
    Attack,
    Defence,
    Speed,
    NUMBER_OF_STATS
 } Stats;

/**
 * A simple entity, with a position, texture and movement function.
 */
typedef struct Entity {
    SDL_Texture* textures[4];
    Mix_Chunk* sounds[4];
    SDL_Rect position;
    Component components[COMPONENT_TOTAL];
    Timer timers[4];
    bool remove;
} Entity;

/**
 * Initalize an entity with a default size, location and with provided texture.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef, const char* soundRef);

/**
 * Returns true if the entity has queried component.
 */
bool hasComponent(Entity* e, ComponentType c);


#endif