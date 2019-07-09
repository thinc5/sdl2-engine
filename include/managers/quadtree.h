#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>

#include "../entities/entity.h"

typedef struct QuadTree {
    // The bounds of this Quad Tree.
    SDL_Rect bounds;
    // The entity stored in this node.
    Entity* node;
    // The children of this node.
    QuadTree* topLeft;
    QuadTree* topRight;
    QuadTree* botLeft;
    QuadTree* botRight;
} QuadTree;

/**
 * Initialize the new QuadTree node.
 */
void init_quad(QuadTree* quad);

/**
 * Traverse the QuadTree and find elements at a given position.
 */
Entity* find_entity(QuadTree* root, SDL_Rect* pos);

/**
 * Insert a new node into the QuadTree.
 */
void insert_node(QuadTree* root, Entity* entity);

/**
 * Insert a new node into the QuadTree.
 */
void insert_remove(QuadTree* root);

#endif

