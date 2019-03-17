#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "assetmanager.h"

/**
 * Possible directions of movement.
 */
typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

/**
 * A simple entity, with a position, texture and movement function.
 */
typedef struct Entity {
    SDL_Texture* texture;
    SDL_Rect position;
    void (*move)(void* e, Direction d);
} Entity;

/**
 * Initalize an entity with a default size, location and with provided texture.
 */
bool initEntity(Entity* e, AssetRegistry* reg, const char* textureRef);

/**
 * Move an entity a set distance in a provided direction.
 */
void move(void* e, Direction d);

#endif