#ifndef LEVELZ_LEVEL_H
#define LEVELZ_LEVEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "coordinate.h"

/**
 * Represents a header in a level.
 */
typedef struct LevelHeader {
    /**
     * Represents the name of a level header.
     */
    char* name;

    /**
     * Represents the value of a level header.
     */
    char* value;
} LevelHeader;

/**
 * Creates a new LevelHeader.
 * @param name Name of the header.
 * @param value Value of the header.
 * @return A new LevelHeader.
 */
LevelHeader* createLevelHeader(char* name, char* value) {
    LevelHeader* h = (LevelHeader*) malloc(sizeof(LevelHeader));
    h->name = name;
    h->value = value;
    return h;
}

/**
 * Converts a LevelHeader to a string.
 * @param header The LevelHeader.
 * @return The string representation of the LevelHeader.
 */
char* LevelHeader_toString(LevelHeader* header) {
    if (header == 0) return 0;

    char* str = (char*) malloc(strlen(header->name) + strlen(header->value) + 3);
    sprintf(str, "@%s %s", header->name, header->value);

    return str;
}

/**
 * Converts a string to a LevelHeader.
 * @param str The string representation of the LevelHeader.
 * @return The LevelHeader.
 */
LevelHeader* LevelHeader_fromString(char* str) {
    if (str == 0) return 0;

    char* name = strtok(str, " ") + 1;
    char* value = strtok(0, " ");

    return createLevelHeader(name, value);
}

/**
 * Represents a 2D Level.
 */
typedef struct Level2D {
    /**
     * The headers of the level.
     */
    LevelHeader** headers;

    /**
     * The blocks in the level.
     */
    LevelObject2D* blocks[16];

    /**
     * The spawnpoint of the level.
     */
    Coordinate2D* spawn;
} Level2D;

enum Scroll {
    /**
     * No Scrolling
     */
    NONE,
    
    /**
     * Horizontal Scrolling moving left
     */
    HORIZONTAL_LEFT,

    /**
     * Horizontal Scrolling moving right
     */
    HORIZONTAL_RIGHT,

    /**
     * Vertical Scrolling moving up
     */
    VERTICAL_UP,

    /**
     * Vertical Scrolling moving down
     */
    VERTICAL_DOWN
};

/**
 * Creates a new Level2D.
 * @param spawn The spawnpoint of the level.
 * @return A new Level2D.
 */
Level2D* createLevel2D(Coordinate2D* spawn) {
    Level2D* l = (Level2D*) malloc(sizeof(Level2D));
    l->spawn = spawn;
    return l;
}

/**
 * Gets the number of headers in a Level2D.
 * @param level The Level2D.
 * @return The number of headers in the Level2D.
 */
int Level2D_getHeaderCount(Level2D* level) {
    int headerCount = 0;
    while (level->headers[headerCount] != NULL) {
        headerCount++;
    }

    return headerCount;
}

/**
 * Adds a header to a Level2D.
 * @param level Level to add the header to.
 * @param h The header to add.
 */
void Level2D_setHeader(Level2D* level, LevelHeader* h) {
    if (level->headers == 0) {
        level->headers = (LevelHeader**) malloc(16 * sizeof(LevelHeader*));
        for (int i = 0; i < 16; i++) {
            level->headers[i] = NULL;
        }

        level->headers[0] = h;
    } else {
        int headerCount = Level2D_getHeaderCount(level);
        for (int i = 0; i < headerCount; i++) {
            LevelHeader* header = level->headers[i];
            if (strcmp(header->name, h->name) == 0) {
                header->value = h->value;
                return;
            } else {
                level->headers = (LevelHeader**) realloc(level->headers, (i + 1) * sizeof(LevelHeader*));
                level->headers[i] = h;
            }
        }
    }
}

/**
 * Adds a header to a Level2D.
 * @param level Level to add the header to.
 * @param name The name of the header.
 * @param value The value of the header.
 */
void Level2D_addHeader(Level2D* level, char* name, char* value) {
    LevelHeader* h = (LevelHeader*) malloc(sizeof(LevelHeader));
    h->name = name;
    h->value = value;

    Level2D_setHeader(level, h);
}

/**
 * Removes a header from a Level2D.
 * @param level Level to remove the header from.
 * @param name The name of the header to remove.
 */
void Level2D_removeHeader(Level2D* level, char* name) {
    if (level->headers == 0) return;

    int i = 0;
    while (level->headers[i] != 0) {
        if (strcmp(level->headers[i]->name, name) == 0) {
            free(level->headers[i]);
            
            for (int j = i; j < sizeof(level->headers) - 1; j++) {
                level->headers[j] = level->headers[j + 1];
            }
            level->headers[sizeof(level->headers) - 1] = 0;
            return;
        }
        i++;
    }
}

/**
 * Represents a 3D Level.
 */
typedef struct Level3D {
    /**
     * The headers of the level.
     */
    LevelHeader** headers;

    /**
     * The blocks in the level.
     */
    LevelObject3D** blocks;

    /**
     * The spawnpoint of the level.
     */
    Coordinate3D* spawn;
} Level3D;

/**
 * Creates a new Level3D.
 * @param spawn The spawnpoint of the level.
 * @return A new Level3D.
 */
Level3D* createLevel3D(Coordinate3D* spawn) {
    Level3D* l = (Level3D*) malloc(sizeof(Level3D));
    l->headers = NULL;
    l->blocks = NULL;
    l->spawn = spawn;
    return l;
}

/**
 * Gets the number of headers in a Level3D.
 * @param level The Level3D.
 * @return The number of headers in the Level3D.
 */
int Level3D_getHeaderCount(Level3D* level) {
    int headerCount = 0;
    while (level->headers[headerCount] != NULL) {
        headerCount++;
    }

    return headerCount;
}

/**
 * Adds a header to a Level3D.
 * @param level Level to add the header to.
 * @param h The header to add.
 */
void Level3D_setHeader(Level3D* level, LevelHeader* h) {
    if (level->headers == 0) {
        level->headers = (LevelHeader**) malloc(16 * sizeof(LevelHeader*));
        for (int i = 0; i < 16; i++) {
            level->headers[i] = NULL;
        }
        
        level->headers[0] = h;
    } else {
        int headerCount = Level3D_getHeaderCount(level);
        for (int i = 0; i < headerCount; i++) {
            LevelHeader* header = level->headers[i];
            if (strcmp(header->name, h->name) == 0) {
                header->value = h->value;
                return;
            } else {
                level->headers = (LevelHeader**) realloc(level->headers, (i + 1) * sizeof(LevelHeader*));
                level->headers[i] = h;
            }
        }
    }
}

/**
 * Adds a header to a Level3D.
 * @param level Level to add the header to.
 * @param name The name of the header.
 * @param value The value of the header.
 */
void Level3D_addHeader(Level3D* level, char* name, char* value) {
    LevelHeader* h = (LevelHeader*) malloc(sizeof(LevelHeader));
    h->name = name;
    h->value = value;

    Level3D_setHeader(level, h);
}

/**
 * Removes a header from a Level3D.
 * @param level Level to remove the header from.
 * @param name The name of the header to remove.
 */
void Level3D_removeHeader(Level3D* level, char* name) {
    if (level->headers == 0) return;

    int i = 0;
    while (level->headers[i] != 0) {
        if (strcmp(level->headers[i]->name, name) == 0) {
            free(level->headers[i]);
            
            for (int j = i; j < sizeof(level->headers) - 1; j++) {
                level->headers[j] = level->headers[j + 1];
            }
            level->headers[sizeof(level->headers) - 1] = 0;
            return;
        }
        i++;
    }
}

#endif