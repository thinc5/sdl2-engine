#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>

#include "../entities/entity.h"

/**
 * Child positions.
 */
typedef enum Child {
    TOPLEFT,
    TOPRIGHT,
    BOTLEFT,
    BOTRIGHT,
    MAX_CHILDREN
} Child;

/**
 * The node of the tree.
 */
typedef struct QuadTreeNode {
    // The bounds of this node.
    SDL_Rect bounds;
    // The entity stored in this node.
    Entity* entity;
    // The children of this node.
    QuadTreeNode* children[MAX_CHILDREN];
} QuadTreeNode;

/**
 * The quad tree.
 */
typedef struct QuadTree {
    // The root.
    QuadTreeNode* root;
    // Number of nodes.
    uint16_t size;
} QuadTree;

/**
 * Initialize the new QuadTree node.
 */
void init_quad_tree(QuadTree* quad, SDL_Rect bounds);

/**
 * Does this node have any children?
 * Returns the pointer to stored entity on success, and NULL
 * if no entity was found.
 */
Entity* find_entity(QuadTreeNode* node, SDL_Rect point)

/**
 * Insert a new node into the QuadTree.
 */
void insert_node(QuadTree* root, Entity* entity);


#endif

