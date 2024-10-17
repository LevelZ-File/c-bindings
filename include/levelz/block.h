#ifndef LEVELZ_BLOCK_H
#define LEVELZ_BLOCK_H

#define _BLOCK_PROPERTIES_INIT_CAPACITY 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coordinate.h"

/**
 * Represents the properties of a Block.
 */
typedef struct BlockProperty {
    /**
     * The name of the property.
     */
    char* name;
    
    /**
     * The value of the property.
     */
    char* value;
} BlockProperty;

/**
 * Represents a block in a game level.
 */
typedef struct Block {
    /**
     * The name of the block.
     */
    char* name;
    
    /**
     * The properties of the block.
     */
    BlockProperty** properties;

    /**
     * The number of properties in the block.
     */
    int propertyCount;

    /**
     * The capacity of the properties array.
     */
    int propertyCapacity;
} Block;

/**
 * Creates a new Block.
 * @param name The name of the block.
 */
Block* createBlock(char* name) {
    Block* b = (Block*) malloc(sizeof(Block));
    b->name = name;
    b->propertyCount = 0;
    b->propertyCapacity = _BLOCK_PROPERTIES_INIT_CAPACITY;
    b->properties = (BlockProperty**) malloc(b->propertyCapacity * sizeof(BlockProperty*));
    
    return b;
}

/**
 * Gets the value of a property of a Block.
 * @param b The block.
 * @param name The name of the property.
 * @return The value of the property.
 */
char* Block_getProperty(Block* b, char* name) {
    if (b == 0) return 0;
    if (name == 0) return 0;

    for (int i = 0; i < b->propertyCount; i++) {
        if (strcmp(b->properties[i]->name, name) == 0) {
            return b->properties[i]->value;
        }
    }

    return "";
}

/**
 * Sets a property of a Block.
 * @param b The block.
 * @param name The name of the property.
 * @param value The value of the property.
 */
void Block_setProperty(Block* b, char* name, char* value) {
    if (b == 0) return;
    if (name == 0) return;
    if (value == 0) return;

    for (int i = 0; i < b->propertyCount; i++) {
        if (strcmp(b->properties[i]->name, name) == 0) {
            b->properties[i]->value = value;
            return;
        }
    }

    BlockProperty* p = (BlockProperty*) malloc(sizeof(BlockProperty));
    p->name = strcpy((char*) malloc(strlen(name) + 1), name);
    p->value = strcpy((char*) malloc(strlen(value) + 1), value);

    if (b->propertyCount == b->propertyCapacity) {
        b->propertyCapacity *= 2;
        b->properties = (BlockProperty**) realloc(b->properties, b->propertyCapacity * sizeof(BlockProperty*));
    }

    b->properties[b->propertyCount] = p;
    b->propertyCount++;

    return;
}

/**
 * Removes a property from a Block.
 * @param b The block.
 * @param name The name of the property.
 */
void Block_removeProperty(Block* b, char* name) {
    if (b == 0) return;
    if (name == 0) return;
    if (b->propertyCount == 0) return;

    for (int i = 0; i < b->propertyCount; i++) {
        if (strcmp(b->properties[i]->name, name) == 0) {
            free(b->properties[i]);
            for (int j = i; j < b->propertyCount - 1; j++) {
                b->properties[j] = b->properties[j + 1];
            }
            b->propertyCount--;
            return;
        }
    
        if (b->propertyCount < b->propertyCapacity / 2) {
            b->propertyCapacity /= 2;
            b->properties = (BlockProperty**) realloc(b->properties, b->propertyCapacity * sizeof(BlockProperty*));
        }
    }
}

/**
 * Converts a Block to a string.
 * @param b The block.
 * @return The string representation of the block.
 */
char* Block_toString(Block* b) {
    if (b == 0) return 0;

    char* name = (char*) malloc(strlen(b->name) + 1);
    sprintf(name, "%s", b->name);

    if (b->propertyCount == 0)
        return name;
    
    int bytes = strlen(name) + 1;
    for (int i = 0; i < b->propertyCount; i++) {
        bytes += strlen(b->properties[i]->name) + strlen(b->properties[i]->value) + 4;
    }

    char* str = (char*) malloc(bytes);
    sprintf(str, "%s<", name);

    for (int i = 0; i < b->propertyCount; i++) {
        sprintf(str, "%s%s=%s", str, b->properties[i]->name, b->properties[i]->value);
        if (i < b->propertyCount - 1)
            sprintf(str, "%s, ", str);
    }

    sprintf(str, "%s>", str);
    return str;
}

/**
 * Converts a string to a Block.
 * @param str The string representation of the block.
 * @return The Block.
 */
Block* Block_fromString(const char* str) {
    if (str == 0) return 0;

    int l = strlen(str);
    if (l == 0) return 0;

    char* strCopy = (char*) malloc(l + 1);
    strcpy(strCopy, str);
    strCopy[l - 1] = '\0';

    char* name = strtok(strCopy, "<");
    if (name == 0) {
        free(strCopy);
        return 0;
    }

    Block* b = createBlock(name);

    char* properties = strtok(0, "<");
    if (properties == 0) {
        free(strCopy);
        return b;
    }

    char* property = strtok(properties, "=,");
    char* key = 0;
    char* value = 0;
    while (property != 0) {
        if (key == 0) {
            key = property;
        } else {
            value = property;
            Block_setProperty(b, key, value);

            key = 0;
            value = 0;
        }

        property = strtok(0, "=,");
    }

    return b;
}

/**
 * Utility Object for representing a Level Block and its Coordinate.
 */
typedef struct LevelObject2D {

    /**
     * The block of the object.
     */
    Block* block;

    /**
     * The 2D coordinate of the object.
     */
    Coordinate2D* coordinate;
} LevelObject2D;

/**
 * Creates a new LevelObject2D.
 * 
 * @param block The block of the object.
 * @param coordinate The 2D coordinate of the object.
 * @return A new LevelObject2D.
 */
LevelObject2D* createLevelObject2D(Block* block, Coordinate2D* coordinate) {
    LevelObject2D* o = (LevelObject2D*) malloc(sizeof(LevelObject2D));
    o->block = block;
    o->coordinate = coordinate;
    return o;
}

/**
 * Converts a LevelObject2D to a string.
 * @param block The LevelObject2D.
 */
char* LevelObject2D_toString(LevelObject2D* object) {
    char* block = Block_toString(object->block);
    char* coordinate = Coordinate2D_toString(object->coordinate);

    char* str = (char*) malloc(strlen(block) + strlen(coordinate) + 3);
    sprintf(str, "%s: %s", block, coordinate);

    return str;
}

/**
 * Converts a string to a LevelObject2D.
 * @param str The string representation of the LevelObject2D.
 * @return The LevelObject2D.
 */
LevelObject2D* LevelObject2D_fromString(char* str) {
    char* blockStr = strtok(str, ":");
    char* coordinateStr = strtok(0, ":");

    Block* block = Block_fromString(blockStr);
    Coordinate2D* coordinate = Coordinate2D_fromString(coordinateStr);

    return createLevelObject2D(block, coordinate);
}

/**
 * Utility Object for representing a Level Block and its Coordinate.
 */
typedef struct LevelObject3D {

    /**
     * The block of the object.
     */
    Block* block;

    /**
     * The 3D coordinate of the object.
     */
    Coordinate3D* coordinate;
} LevelObject3D;

/**
 * Creates a new LevelObject3D.
 * @param block The block of the object.
 * @param coordinate The 3D coordinate of the object.
 * @return A new LevelObject3D.
 */
LevelObject3D* createLevelObject3D(Block* block, Coordinate3D* coordinate) {
    LevelObject3D* o = (LevelObject3D*) malloc(sizeof(LevelObject3D));
    o->block = block;
    o->coordinate = coordinate;
    return o;
}

/**
 * Converts a LevelObject3D to a string.
 * @param block The LevelObject3D.
 */
char* LevelObject3D_toString(LevelObject3D* object) {
    char* block = Block_toString(object->block);
    char* coordinate = Coordinate3D_toString(object->coordinate);

    char* str = (char*) malloc(strlen(block) + strlen(coordinate) + 3);
    sprintf(str, "%s: %s", block, coordinate);

    return str;
}

/**
 * Converts a string to a LevelObject3D.
 * @param str The string representation of the LevelObject3D.
 * @return The LevelObject3D.
 */
LevelObject3D* LevelObject3D_fromString(char* str) {
    char* blockStr = strtok(str, ":");
    char* coordinateStr = strtok(0, ":");

    Block* block = Block_fromString(blockStr);
    Coordinate3D* coordinate = Coordinate3D_fromString(coordinateStr);

    return createLevelObject3D(block, coordinate);
}

#endif