#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdbool.h>

#include "../managers/assetstack.h"
#include "../components/component.h"
#include "../util/timer.h"


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
    int stats[NUMBER_OF_STATS];
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
bool init_entity(Entity* e, AssetStack* stack, const char* texture, const char* sound);

/**
 * Returns true if the entity has queried component.
 */
bool has_component(Entity* e, ComponentType c);


#endif
