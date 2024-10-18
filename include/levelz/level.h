#ifndef LEVELZ_LEVEL_H
#define LEVELZ_LEVEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "coordinate.h"
#include "matrix.h"

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
LevelHeader* LevelHeader_fromString(const char* str) {
    if (str == 0) return 0;

    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    char* name = strtok(str0, " ") + 1;
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
    LevelObject2D** blocks;

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
 * Gets a header from a Level2D.
 * @param level The Level2D.
 * @param name The name of the header.
 * @return The value of the header.
 */
char* Level2D_getHeader(Level2D* level, char* name) {
    if (level->headers == 0) return 0;

    int i = 0;
    while (level->headers[i] != 0) {
        if (strcmp(level->headers[i]->name, name) == 0) {
            return level->headers[i]->value;
        }
        i++;
    }

    return 0;
}

/**
 * Adds a header to a Level2D.
 * @param level Level to add the header to.
 * @param h The header to add.
 */
void Level2D_setHeader(Level2D* level, LevelHeader* h) {
    if (level->headers == 0) {
        level->headers = (LevelHeader**) malloc(2 * sizeof(LevelHeader*));
        level->headers[0] = h;
        level->headers[1] = 0;
    } else {
        int headerCount = Level2D_getHeaderCount(level);
        for (int i = 0; i < headerCount; i++) {
            LevelHeader* header = level->headers[i];
            if (strcmp(header->name, h->name) == 0) {
                header->value = h->value;
                return;
            } else {
                level->headers = (LevelHeader**) realloc(level->headers, (headerCount + 2) * sizeof(LevelHeader*));
                level->headers[headerCount] = h;
                level->headers[headerCount + 1] = 0;
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
 * Gets the number of blocks in a Level2D.
 * @param level The Level2D.
 * @return The number of blocks in the Level2D.
 */
int Level2D_getBlockCount(Level2D* level) {
    int blockCount = 0;
    while (level->blocks[blockCount] != NULL) {
        blockCount++;
    }

    return blockCount;
}

/**
 * Gets a block from a Level2D.
 * @param level The Level2D.
 * @param coordinate The coordinate of the block.
 * @return The block at the coordinate, or 0 if no block is found.
 */
Block* Level2D_getBlock(Level2D* level, Coordinate2D* coordinate) {
    if (level->blocks == 0) return 0;

    int i = 0;
    while (level->blocks[i] != 0) {
        if (level->blocks[i]->coordinate->x == coordinate->x && level->blocks[i]->coordinate->y == coordinate->y) {
            return level->blocks[i]->block;
        }
        i++;
    }

    return 0;
}

/**
 * Adds a block to a Level2D.
 * @param level The Level2D.
 * @param block The block to add.
 */
void Level2D_addBlock(Level2D* level, LevelObject2D* block) {
    if (level == 0) return;
    if (block == 0) return;

    if (level->blocks == 0) {
        level->blocks = (LevelObject2D**) malloc(16 * sizeof(LevelObject2D*));
        level->blocks[0] = block;
        level->blocks[1] = 0;
    } else {
        int size = Level2D_getBlockCount(level);
        for (int i = 0; i < size; i++) {
            Coordinate2D* c = level->blocks[i]->coordinate;
            if (c->x == block->coordinate->x && c->y == block->coordinate->y) {
                level->blocks[i] = block;
                return;
            }
        }

        level->blocks = (LevelObject2D**) realloc(level->blocks, (size + 2) * sizeof(LevelObject2D*));
        level->blocks[size] = block;
        level->blocks[size + 1] = 0;
    }
}

/**
 * Adds a block to a Level2D on a matrix of coordinates.
 * @param level The Level2D.
 * @param block The block to add.
 * @param matrix The matrix of coordinates to add the block to.
 */
void Level2D_addMatrix(Level2D* level, Block* block, CoordinateMatrix2D* matrix) {
    int size = CoordinateMatrix2D_size(matrix);
    Coordinate2D** coordinates = CoordinateMatrix2D_coordinates(matrix);

    for (int i = 0; i < size; i++) {
        Coordinate2D* coordinate = coordinates[i];
        Level2D_addBlock(level, createLevelObject2D(block, coordinate));
    }

}

/**
 * Removes a block from a Level2D.
 * @param level The Level2D.
 * @param block The block to remove.
 */
void Level2D_removeBlock(Level2D* level, LevelObject2D* block) {
    if (level->blocks == 0) return;

    int i = 0;
    while (level->blocks[i] != 0) {
        if (level->blocks[i] == block) {
            free(level->blocks[i]);
            
            for (int j = i; j < sizeof(level->blocks) - 1; j++) {
                level->blocks[j] = level->blocks[j + 1];
            }
            level->blocks[sizeof(level->blocks) - 1] = 0;
            return;
        }
        i++;
    }
}

/**
 * Gets the number of blocks in a Level2D with a specific name.
 * @param level The Level2D.
 * @param name The name of the block.
 * @return The number of blocks in the Level2D with the name.
 */
int Level2D_blockCount(Level2D* level, const char* name) {
    if (level == 0) return 0;
    if (level->blocks == 0) return 0;
    if (name == 0) return 0;

    int count = 0;
    for (int i = 0; i < Level2D_getBlockCount(level); i++) {
        if (strcmp(level->blocks[i]->block->name, name) == 0) {
            count++;
        }
    }

    return count;
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
 * Gets a header from a Level3D.
 * @param level The Level3D.
 * @param name The name of the header.
 * @return The value of the header.
 */
char* Level3D_getHeader(Level3D* level, char* name) {
    if (level->headers == 0) return 0;

    int i = 0;
    while (level->headers[i] != 0) {
        if (strcmp(level->headers[i]->name, name) == 0) {
            return level->headers[i]->value;
        }
        i++;
    }

    return 0;
}

/**
 * Adds a header to a Level3D.
 * @param level Level to add the header to.
 * @param h The header to add.
 */
void Level3D_setHeader(Level3D* level, LevelHeader* h) {
    if (level->headers == 0) {
        level->headers = (LevelHeader**) malloc(2 * sizeof(LevelHeader*));
        level->headers[0] = h;
        level->headers[1] = 0;
    } else {
        int headerCount = Level3D_getHeaderCount(level);
        for (int i = 0; i < headerCount; i++) {
            LevelHeader* header = level->headers[i];
            if (strcmp(header->name, h->name) == 0) {
                header->value = h->value;
                return;
            } else {
                level->headers = (LevelHeader**) realloc(level->headers, (headerCount + 1) * sizeof(LevelHeader*));
                level->headers[headerCount] = h;
                level->headers[headerCount + 1] = 0;
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

/**
 * Gets a block from a Level3D.
 * @param level The Level3D.
 * @param coordinate The coordinate of the block.
 * @return The block at the coordinate, or 0 if no block is found.
 */
Block* Level3D_getBlock(Level3D* level, Coordinate3D* coordinate) {
    if (level->blocks == 0) return 0;

    int i = 0;
    while (level->blocks[i] != 0) {
        if (level->blocks[i]->coordinate->x == coordinate->x && level->blocks[i]->coordinate->y == coordinate->y && level->blocks[i]->coordinate->z == coordinate->z) {
            return level->blocks[i]->block;
        }
        i++;
    }

    return 0;
}

/**
 * Gets the number of blocks in a Level3D.
 * @param level The Level3D.
 * @return The number of blocks in the Level3D.
 */
int Level3D_getBlockCount(Level3D* level) {
    int blockCount = 0;
    while (level->blocks[blockCount] != NULL) {
        blockCount++;
    }

    return blockCount;
}

/**
 * Adds a block to a Level3D.
 * @param level The Level3D.
 * @param block The block to add.
 */
void Level3D_addBlock(Level3D* level, LevelObject3D* block) {
    if (level->blocks == 0) {
        level->blocks = (LevelObject3D**) malloc(16 * sizeof(LevelObject3D*));
        level->blocks[0] = block;
        level->blocks[1] = 0;
    } else {
        int size = Level3D_getBlockCount(level);

        for (int i = 0; i < size; i++) {
            Coordinate3D* c = level->blocks[i]->coordinate;
            if (c->x == block->coordinate->x && c->y == block->coordinate->y && c->z == block->coordinate->z) {
                level->blocks[i] = block;
                return;
            }
        }

        level->blocks = (LevelObject3D**) realloc(level->blocks, (size + 2) * sizeof(LevelObject3D*));
        level->blocks[size] = block;
        level->blocks[size + 1] = 0;
    }
}

/**
 * Adds a block to a Level3D on a matrix of coordinates.
 * @param level The Level3D.
 * @param block The block to add.
 * @param matrix The matrix of coordinates to add the block to.
 */
void Level3D_addMatrix(Level3D* level, Block* block, CoordinateMatrix3D* matrix) {
    int size = CoordinateMatrix3D_size(matrix);
    Coordinate3D** coordinates = CoordinateMatrix3D_coordinates(matrix);
    for (int i = 0; i < size; i++) {
        Coordinate3D* coordinate = coordinates[i];
        Level3D_addBlock(level, createLevelObject3D(block, coordinate));
    }
}

/**
 * Removes a block from a Level3D.
 * @param level The Level3D.
 * @param block The block to remove.
 */
void Level3D_removeBlock(Level3D* level, LevelObject3D* block) {
    if (level->blocks == 0) return;

    int i = 0;
    while (level->blocks[i] != 0) {
        if (level->blocks[i] == block) {
            free(level->blocks[i]);
            
            for (int j = i; j < sizeof(level->blocks) - 1; j++) {
                level->blocks[j] = level->blocks[j + 1];
            }
            level->blocks[sizeof(level->blocks) - 1] = 0;
            return;
        }
        i++;
    }
}

/**
 * Gets the number of blocks in a Level3D with a specific name.
 * @param level The Level3D.
 * @param name The name of the block.
 * @return The number of blocks in the Level3D with the name.
 */
int Level3D_blockCount(Level3D* level, const char* name) {
    if (level == 0) return 0;
    if (level->blocks == 0) return 0;
    if (name == 0) return 0;

    int count = 0;
    for (int i = 0; i < Level3D_getBlockCount(level); i++) {
        if (strcmp(level->blocks[i]->block->name, name) == 0) {
            count++;
        }
    }

    return count;
}

#endif