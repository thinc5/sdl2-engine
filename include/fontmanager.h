#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

/**
 * Each font to be registered.
 */
typedef struct RegisteredFont {
    int uniqueID;
    char* reference;
    TTF_Font* font;
} RegisteredFont;

/**
 * The registry of all loaded fonts.
 */
typedef struct FontRegistry {
    unsigned int currentSize;
    unsigned int totalSize;
    RegisteredFont* registry;
} FontRegistry;

/**
 * Load fonts from a newline-delimated plain text file.
 */
bool loadFonts(FontRegistry* reg, char* configPath);

/**
 *  Load a texture into the manager.
 */
bool loadFont(char* filename, FontRegistry* reg);

/**
 * Free all textures from a provided registry.
 */
bool freeFonts(FontRegistry* reg);

#endif