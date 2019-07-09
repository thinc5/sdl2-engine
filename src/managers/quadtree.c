#include <SDL2/SDL.h>

#include "../managers/quadtree.h"
#include "../util/camera.h"

/**
 * Initialize the new QuadTree node.
 */
void init_quad(QuadTree* quad) {
    quad->node = NULL;
    quad->topLeft = NULL;
    quad->topRight = NULL;
    quad->botLeft = NULL;
    quad->botRight = NULL;
}

/**
 * Traverse the QuadTree and find elements at a given position.
 */
Entity* find_entity(QuadTree* root, SDL_Rect* pos) {
    if (!is_inside(*pos, root->bounds)) {
        return NULL;
    }
    if (root->node != NULL) {
        return;
    }
    if ((root->topLeft->bounds.x + root->botRight->bounds.x) / 2
            >= pos->x) {
        // Indicates topLeft side.
        if ((root->topLeft->bounds.y + root->botRight->bounds.y) / 2
                >= pos->x) {
            if (root->topLeft == NULL) {
                return NULL;
            }
            return find_entity(root->topLeft, pos);
        // Indicates botLeft side.
        } else {
            if (root->botLeft == NULL) {
                return NULL;
            }
            return find_entity(root->botLeft, pos);
        }
    } else {
        // Top right.
        if ((root->topLeft->bounds.y + root->botRight->bounds.x) / 2
                >= pos->y) { 
            if (root->topRight == NULL) {
                return NULL;
            }
            return find_entity(root->topRight, pos);
        // Bot right. 
        } else { 
            if (root->botRight == NULL) {
                return NULL;
            }
            return find_entity(root->botRight, pos);
        } 
    }
}

/**
 * Insert a new node into the QuadTree.
 */
void insert_node(QuadTree* root, Entity* entity) {
    if (entity == NULL) {
        return;
    }
    if (!is_inside(entity->position, root->bounds)) {
        return;
    }
    // We cannot subdivide this quad further
    if (abs(root->topLeft->bounds.x - root->botRight->bounds.x) <= 1 && 
            abs(root->topLeft->bounds.y - root->botRight->bounds.y) <= 1) { 
        
        if (root->node == NULL) 
            root->node = entity; 
        return; 
    }
    if ((root->topLeft->bounds.x + root->botRight->bounds.x) / 2
            >= entity->position.x) { 
        // Indicates topLeftTree 
        if ((root->topLeft->bounds.y + root->botRight->bounds.y) / 2
                >= entity->position.y) { 
            if (root->topLeft == NULL) {
                root->topLeft = (QuadTree*) malloc(sizeof(QuadTree)); 
                Point(topLeft.x, topLeft.y), 
                Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2));
            }
            insert_node(root->topLeft, entity); 
        } else { 
            if (botLeftTree == NULL) 
                botLeftTree = new Quad( 
                    Point(topLeft.x, 
                        (topLeft.y + botRight.y) / 2), 
                    Point((topLeft.x + botRight.x) / 2, 
                        botRight.y)); 
            botLeftTree->insert(node); 
        } 
    } else { 
        // Indicates topRightTree 
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
        { 
            if (topRightTree == NULL) 
                topRightTree = new Quad( 
                    Point((topLeft.x + botRight.x) / 2, 
                        topLeft.y), 
                    Point(botRight.x, 
                        (topLeft.y + botRight.y) / 2)); 
            topRightTree->insert(node); 
        } else { 
            if (botRightTree == NULL) 
                botRightTree = new Quad( 
                    Point((topLeft.x + botRight.x) / 2, 
                        (topLeft.y + botRight.y) / 2), 
                    Point(botRight.x, botRight.y)); 
            botRightTree->insert(node); 
        } 
    } 
}

/**
 * Insert a new node into the QuadTree.
 */
void insert_remove(QuadTree* root) {
    return;
}

