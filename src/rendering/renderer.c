#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <string.h>

#include "../../include/game.h"
#include "../../include/rendering/renderer.h"
#include "../../include/rendering/renderertemplates.h"
#include "../../include/managers/quadtree.h"
#include "../../include/entities/entity.h"
#include "../../include/scenes/scene.h"

/**
 * Rendering algorithm for quadtree.
 */
static void render_quad_entities(QuadTreeNode* node) {
    // If we are at a leaf we render.
    if (is_node_leaf(node)) {
        if (has_component(node->entity, Render)) {
            node->entity->components[Render].call();
        }
    }
    // Is it an empty node?
    if (is_node_empty(node)) {
        return;
    }
    // Is it a branch?
    if (!is_node_leaf(node)) {
        for (int i = 0; i < MAX_CHILDREN; i++) {
            render_quad_entities(node->children[i]);
        }
    }
}

/**
 * Render all renderable entities.
 */
void render_entities(Scene* currentScene) {
    render_quad_entities(currentScene->entities.root);
}

