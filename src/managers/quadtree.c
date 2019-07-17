#include <SDL2/SDL.h>

#include <stdbool.h>

#include "../../include/debug.h"
#include "../../include/game.h"

#include "../../include/managers/quadtree.h"
#include "../../include/util/camera.h"

// ---------------- Helper functions ----------------

/**
 * Create a node.
 */
static void init_quad_node(QuadTreeNode* node, SDL_Rect bounds) {
    // Allocate the root node.
    node = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
    // Children nodes.
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    // Set the bounds.
    node->bounds = bounds;
}

/**
 * Free a node.
 */
static void free_quad_node(QuadTreeNode* node) {
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i] != NULL) {
            free_quad_node(node->children[i]);
        }
    }
    if (node->entity != NULL) {
        free(node->entity);
    }
    free(node);
    node = NULL;
}

/**
 * Is this node a leaf? (No children, degree 0)
 */
bool is_node_leaf(QuadTreeNode* node) {
    return node->children[TOPLEFT] == NULL &&
            node->children[TOPRIGHT] == NULL &&
            node->children[BOTLEFT] == NULL &&
            node->children[BOTRIGHT] == NULL;
}

/**
 * Is this node empty?
 */
bool is_node_empty(QuadTreeNode* node) {
    return is_node_leaf(node) && node->entity == NULL;
}

/**
 * Is this node a leaf and occupied?
 */
static bool is_node_occupied(QuadTreeNode* node) {
    return is_node_leaf(node) && node->entity != NULL;
}

/**
 * Get the next node to search.
 */
static Child get_dir(SDL_Point centre, SDL_Point point) {
    if (point.x == centre.x && point.y == centre.y) {
        return MAX_CHILDREN;
    }
    // Left.
    if (point.x < centre.x) {
        // Bottom.
        if (point.y < centre.y) {
            return BOTLEFT;
        // Top.
        } else  {
            return TOPLEFT;
        }
    // Right.
    } else {
        // Bottom.
        if (point.y < centre.y) {
            return BOTRIGHT;
        // Top.
        } else  {
            return TOPRIGHT;
        }
    }
    return MAX_CHILDREN;
}

/**
 * Turn a leaf into a branch and relocate the entity.
 */
static void subdivide_node(QuadTreeNode* node, Entity* entity) {
    SDL_Point centre = get_rect_centre(node->bounds);
    SDL_Point dim = { .x = node->bounds.w / 2, .y = node->bounds.h / 2 };
    // Create the children.
    node->children[TOPLEFT] = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
    node->children[TOPLEFT]->bounds = (SDL_Rect) { .x = node->bounds.x, .y = node->bounds.y,
            .w = dim.x, .h = dim.y };
    node->children[TOPRIGHT] = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
    node->children[TOPRIGHT]->bounds = (SDL_Rect) { .x = node->bounds.x + dim.x, .y = node->bounds.y,
            .w = dim.x, .h = dim.y };
    node->children[BOTLEFT] = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
    node->children[BOTLEFT]->bounds = (SDL_Rect) { .x = node->bounds.x, .y = node->bounds.y + dim.y,
            .w = dim.x, .h = dim.y };
    node->children[BOTRIGHT] = (QuadTreeNode*) malloc(sizeof(QuadTreeNode));
    node->children[BOTRIGHT]->bounds = (SDL_Rect) { .x = node->bounds.x + dim.x, .y = node->bounds.y + dim.y,
            .w = dim.x, .h = dim.y };
    // Insert the old entity.
    Child dir = get_dir(centre, get_rect_centre(node->entity->position));
    node->children[dir]->entity = node->entity;
    node->entity = NULL;
    // Insert the new entity.
    place_entity(node, entity);
}

/**
 * Place entity.
 */
bool place_entity(QuadTreeNode* node, Entity* entity) {
    SDL_Point point = get_rect_centre(entity->position);
    INFO_LOG("Entity being placed at %d %d.\n", point.x, point.y);
    // Is this point even able to be inserted? (Within the bounds?)
    if (!is_point_inside(node->bounds, point)) {
        INFO_LOG("Entity not inside.\n");
        return false;
    }
    // Do we have space in the current node to add entity?
    if (is_node_leaf(node) && node->entity == NULL) {
        // Place entity and return.
        node->entity = entity;
        INFO_LOG("Entity placed!\n");
        return true;
    }
    // Are we on a branch or a leaf?
    if (!is_node_leaf(node)) {
        // We can try and find a place to put the entity.
        Child dir = get_dir(get_rect_centre(node->bounds),
                get_rect_centre(entity->position));
        switch (dir) {
            case MAX_CHILDREN:
                return false;
            case TOPLEFT:
                if (node->children[TOPLEFT]->entity == NULL) {
                    node->children[TOPLEFT]->entity = entity;
                    return true;
                } else {
                    return place_entity(node->children[TOPLEFT], entity);
                }
            case TOPRIGHT:
                if (node->children[TOPRIGHT]->entity == NULL) {
                    node->children[TOPRIGHT]->entity = entity;
                    return true;
                } else {
                    return place_entity(node->children[TOPRIGHT], entity);
                }
            case BOTLEFT:
                if (node->children[BOTLEFT]->entity == NULL) {
                    node->children[BOTLEFT]->entity = entity;
                    return true;
                } else {
                    return place_entity(node->children[BOTLEFT], entity);
                }
            case BOTRIGHT:
                if (node->children[BOTRIGHT]->entity == NULL) {
                    node->children[BOTRIGHT]->entity = entity;
                    return true;
                } else {
                    return place_entity(node->children[BOTRIGHT], entity);
                }
        }
    }
    // We need to subdivide.
    subdivide_node(node, entity);
    return true;
}

/**
 * Restore a node when there is only one or no entities.
 * Turns branch into a leaf.
 */
static void restore_node(QuadTreeNode* node) {
    Entity* j = NULL;
    // Find our entity to pull up.
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->children[i]->entity != NULL) {
            if (j != NULL) {
                return;
            }
            j = node->children[i]->entity;
        }
    }
    // Free the child nodes.
    for (int i = 0; i < MAX_CHILDREN; i++) {
        free_quad_node(node->children[i]);
    }
    // Set the entity.
    node->entity = j;
}

// ---------------- Main functions ----------------

/**
 * Initialize the quad tree node.
 */
void init_quad_tree(QuadTree* quad, SDL_Rect bounds) {
    // Were we supplied a size for our tree?
    if (bounds.w == 0 && bounds.h == 0) {
        SDL_GetWindowSize(gameData.window, &bounds.w, &bounds.h);
    }
    // Size of the quad tree.
    quad->size = 0;
    // Initialize the root node.
    init_quad_node(quad->root, bounds);
}

/**
 * Free quad tree.
 */
void free_quad_tree(QuadTree* quad) {
    free_quad_node(quad->root);
}

/**
 * Does this node have any children?
 * Returns the pointer to stored entity on success, and NULL
 * if no entity was found.
 */
Entity* find_entity(QuadTreeNode* node, SDL_Rect point) {
    // Does this node exist?
    if (!node) {
        return NULL;
    }
    // Is this a leaf?
    if (is_node_occupied(node)) {
        // Check if any entities intersect with the point.
        return node->entity;
    }
    // Where do we search next?
    SDL_Point centre = get_rect_centre(node->bounds);
    SDL_Point p = get_rect_centre(point);
    // Get direction.
    Child dir = get_dir(centre, p);
    switch (dir) {
        case MAX_CHILDREN:
            // No direction.
            return NULL;
        case TOPLEFT:
            if (node->children[TOPLEFT] != NULL) {
                find_entity(node->children[TOPLEFT], point);
            }
            break;
        case TOPRIGHT:
            if (node->children[TOPRIGHT] != NULL) {
                find_entity(node->children[TOPRIGHT], point);
            }
            break;
        case BOTLEFT:
            if (node->children[BOTLEFT] != NULL) {
                find_entity(node->children[BOTLEFT], point);
            }
            break;
        case BOTRIGHT:
            if (node->children[BOTRIGHT] != NULL) {
                find_entity(node->children[BOTRIGHT], point);
            }
            break;
    }
    return NULL;
}

/**
 * Insert an entity into the quad tree.
 */
bool insert_entity(QuadTreeNode* node, Entity (*init_entity)(void), SDL_Rect position) {
    Entity* entity = (Entity*) malloc(sizeof(Entity));
    *entity = init_entity();
    entity->position = position;
    INFO_LOG("Entity created! %d\n", entity->position.x);
    return place_entity(node, entity);
}

