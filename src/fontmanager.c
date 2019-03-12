#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/fontmanager.h"

/**
 * Load textures.
 */
bool loadFonts(FontRegistry* reg, char* configPath) {
    // How many textures are we loading?
    int total = 0;
    char buffer[100];
    // Open file and count how many lines
    FILE* fp = fopen(configPath, "r");
    if (!fp) {
        printf("Unable to find specified font configuration file.\n");
        return false;
    }
    while(fgets(buffer, sizeof(buffer), fp)) {
        total++;
    }
    // Reset the pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);
    memset(buffer, '\0', sizeof(buffer));
    // Allocate space for each of the textures.
    reg->totalSize = total;
    reg->registry = (RegisteredFont*) malloc(sizeof(RegisteredFont) * reg->totalSize);
    reg->currentSize = 0;
    // Loop each line and load the texture.
    while(fgets(buffer, sizeof(buffer), fp)) {
        // If last character of buffer is a newline, strip it
        int blen = strlen(buffer);
        if (buffer[blen - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Remove newline
        if (!loadFont(buffer, reg)) {
            fprintf(stderr, "Could not load file: %s\n", buffer);
            memset(buffer, '\0', sizeof(buffer));
            return false;
        }
        memset(buffer, '\0', sizeof(buffer));
    }
    fclose(fp);
    return true;
}

/**
 *  Load a texture into the manager.
 */
bool loadFont(char* filename, FontRegistry* reg) {
    RegisteredFont* newRF = &reg->registry[reg->currentSize];
    newRF->font = TTF_OpenFont(filename, 20);
    if (newRF->font == NULL) {
        printf("Failed to Load font\n");
        return false;
    }
    // Set the font's unique id
    newRF->uniqueID = reg->currentSize;
    // Set the font's reference string.
    newRF->reference = (char*) malloc(sizeof(char) * strlen(filename));
    if (strcpy(newRF->reference, filename) == NULL) {
        // Failed to copy string, free texture and return false.
        TTF_CloseFont(newRF->font);
        printf("Failed to copy filename into registry\n");
        return false;
    }
    // Let the registry know we have added a texture.
    reg->currentSize++;
    printf("Successfully loaded %s\n", newRF->reference);
    return true;
}

/**
 * Free an entry in the texture registry.
 */
bool freeFont(RegisteredFont* f) {
    if (f->font) {
        TTF_CloseFont(f->font);
        f->font = NULL;
    } else {
        printf("Font was not opened and cannot be closed\n");
    }
    if (f->reference) {
        printf("Freed %s\n", f->reference);
        free(f->reference);
        f->reference = NULL;
    } else {
        printf("Reference name not allocated to begin with...\n");
    }
    return true;
}

/**
 * Free all textures in registry.
 */
bool freeFonts(FontRegistry* reg) {
    int freed = 0;
    for (int i = 0; i < reg->currentSize; i++) {
        if (!freeFont(&reg->registry[i])) {
            printf("Failed to free font in position %d.\n", i);
        }
        freed++;
    }
    printf("Freed %d fonts out of %d.\n", freed, reg->totalSize);
    return true;
}
