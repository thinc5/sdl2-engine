#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>

#include "../managers/assetstack.h"
#include "../managers/entitymanager.h"
#include "../entities/entity.h"

/**
 * What is the context of this "scene".
 */
typedef enum SceneType {
    EscMenu,
    MainMenu,
    Debug,
    TileSelect,
    Battle
} SceneType;

/**
 * Scene abstraction, each game "view" is considered a scene.
 */
typedef struct Scene {
    // Type of scene.
    SceneType type;
    // Entities present in scene.
    EntityManager entities;
    // Need to cast as GameData
    void (*event_handler)();
    SDL_Texture* bg;
    SDL_Texture* cursor;
} Scene;

/**
 * Initialize the scene components.
 */
bool init_scene(Scene* scene);

/**
 * Free a scene.
 */
void free_scene(Scene* scene);

 /**
  * Switch scenes.
  */
void change_scene(void (*next)(void));

#endif
