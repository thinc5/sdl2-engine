#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "assetmanager.h"
#include "component.h"

/**
 * A simple entity, with a position, texture and movement function.
 */
typedef struct Entity {
    SDL_Texture* texture;
    Mix_Chunk* sound;
    SDL_Rect position;
    Component components[COMPONENT_TOTAL];
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