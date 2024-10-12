#ifndef LEVELZ_MAIN_H
#define LEVELZ_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "levelz/coordinate.h"
#include "levelz/block.h"
#include "levelz/level.h"
#include "levelz/matrix.h"

/**
 * Marks the end of the header section
 */
const char* LEVELZ_HEADER_END = "---";

/**
 * Marks the end of the file
 */
const char* LEVELZ_END = "end";

// Internal

char* __trim(char* str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

LevelHeader* __readHeaders(char** input) {
    LevelHeader* headers = 0;

    int index = 0;
    while (1) {
        char* line = input[index];
        if (line == 0) break;

        char* name = strtok(line, " ");
        if (strncmp("@", name, 1) != 1) continue;
        name++;
        
        char* value = strtok(0, " ");

        LevelHeader* header = createLevelHeader(name, value);
        if (headers == 0) {
            headers = header;
        } else {
            int length = sizeof(headers) / sizeof(LevelHeader);
            headers = (LevelHeader*) realloc(headers, (length + 1) * sizeof(LevelHeader));
            headers[length] = *header;
        }

        index++;
    }

    return headers;
}

Coordinate2D** __read2DPoints(char* input) {
    Coordinate2D** points = NULL;

    char* token = strtok(input, "*");
    while (token != NULL) {
        int l = strlen(token);
        if (token[0] == '(' && token[l - 1] == ']') {
            CoordinateMatrix2D* matrix = CoordinateMatrix2D_fromString(token);

            Coordinate2D** matrixPoints = CoordinateMatrix2D_coordinates(matrix);
            if (points == 0)
                points = matrixPoints;
            else {
                int size = CoordinateMatrix2D_size(matrix);
                int length = sizeof(points) / sizeof(Coordinate2D);
                points = (Coordinate2D**) realloc(points, (length + size) * sizeof(Coordinate2D));

                for (int i = 0; i < size; i++) {
                    points[length + i] = matrixPoints[i];
                }
            }
        } else {
            Coordinate2D* point = Coordinate2D_fromString(token);

            if (points == 0)
                points[0] = point;
            else {
                int length = sizeof(points) / sizeof(Coordinate2D);
                points = (Coordinate2D**) realloc(points, 2 * sizeof(Coordinate2D));
                points[length - 1] = point;
            }
        }

        token = strtok(NULL, "*");
    }

    return points;
}

Coordinate3D** __read3DPoints(char* input) {
    Coordinate3D** points = NULL;

    char* token = strtok(input, "*");
    while (token != NULL) {
        int l = strlen(token);
        if (token[0] == '(' && token[l - 1] == ']') {
            CoordinateMatrix3D* matrix = CoordinateMatrix3D_fromString(token);

            Coordinate3D** matrixPoints = CoordinateMatrix3D_coordinates(matrix);
            if (points == 0)
                points = matrixPoints;
            else {
                int size = CoordinateMatrix3D_size(matrix);
                int length = sizeof(points) / sizeof(Coordinate3D);
                points = (Coordinate3D**) realloc(points, (length + size) * sizeof(Coordinate3D));

                for (int i = 0; i < size; i++) {
                    points[length + i] = matrixPoints[i];
                }
            }
        } else {
            Coordinate3D* point = Coordinate3D_fromString(token);

            if (points == 0)
                points[0] = point;
            else {
                int length = sizeof(points) / sizeof(Coordinate3D);
                points = (Coordinate3D**) realloc(points, 2 * sizeof(Coordinate3D));
                points[length - 1] = point;
            }
        }

        token = strtok(NULL, "*");
    }

    return points;
}

typedef struct LevelZLine2D {
    Block* block;
    Coordinate2D** coordinates;
} LevelZLine2D;

LevelZLine2D* __read2DLine(char* input) {
    LevelZLine2D* line = (LevelZLine2D*) malloc(sizeof(LevelZLine2D));

    char* blockStr = strtok(input, ":");
    char* coordinateStr = strtok(0, ":");

    Block* block = Block_fromString(blockStr);
    Coordinate2D** coordinates = __read2DPoints(coordinateStr);

    line->block = block;
    line->coordinates = coordinates;

    return line;
}

typedef struct LevelZLine3D {
    Block* block;
    Coordinate3D** coordinates;
} LevelZLine3D;

LevelZLine3D* __read3DLine(char* input) {
    LevelZLine3D* line = (LevelZLine3D*) malloc(sizeof(LevelZLine3D));

    char* blockStr = strtok(input, ":");
    char* coordinateStr = strtok(0, ":");

    Block* block = Block_fromString(blockStr);
    Coordinate3D** coordinates = __read3DPoints(coordinateStr);

    line->block = block;
    line->coordinates = coordinates;

    return line;
}

// Implementation

/**
 * Reads a Level2D from a string.
 * @param str The string representation of the Level2D.
 * @return The Level2D.
 */
Level2D* readLevel2D(char* str) {
    Level2D* level = (Level2D*) malloc(sizeof(Level2D));

    char* token = strtok(str, "\n");
    while (token != NULL) {
        if (strcmp(token, LEVELZ_HEADER_END) == 0) {
            break;
        }

        LevelHeader* header = LevelHeader_fromString(__trim(token));
        if (header->name == "type" && header->value != "2") return 0;

        Level2D_addHeader(level, header->name, header->value);

        if (header->name == "spawn") {
            Coordinate2D* spawn = Coordinate2D_fromString(header->value);
            level->spawn = spawn;
        }

        token = strtok(NULL, "\n");
    }

    token = strtok(NULL, "\n");
    while (token != NULL) {
        if (strcmp(token, LEVELZ_END) == 0) {
            break;
        }

        LevelZLine2D* line = __read2DLine(__trim(token));
        
        for (int i = 0; i < sizeof(line->coordinates) / sizeof(Coordinate2D); i++) {
            LevelObject2D* obj = createLevelObject2D(line->block, line->coordinates[i]);
            Level2D_addBlock(level, obj);
        }

        token = strtok(NULL, "\n");
    }

    return level;
}

/**
 * Reads a Level3D from a string.
 * @param str The string representation of the Level3D.
 * @return The Level3D.
 */
Level3D* readLevel3D(char* str) {
    Level3D* level = createLevel3D(createCoordinate3D(0, 0, 0));

    char* token = strtok(str, "\n");
    while (token != NULL) {
        if (strcmp(token, LEVELZ_HEADER_END) == 0) {
            break;
        }

        LevelHeader* header = LevelHeader_fromString(__trim(token));
        if (header->name == "type" && header->value != "3") return 0;

        Level3D_addHeader(level, header->name, header->value);

        if (header->name == "spawn") {
            Coordinate3D* spawn = Coordinate3D_fromString(header->value);
            level->spawn = spawn;
        }

        token = strtok(NULL, "\n");
    }

    token = strtok(NULL, "\n");
    while (token != NULL) {
        if (strcmp(token, LEVELZ_END) == 0) {
            break;
        }

        LevelZLine3D* line = __read3DLine(__trim(token));

        for (int i = 0; i < sizeof(line->coordinates) / sizeof(Coordinate3D); i++) {
            LevelObject3D* obj = createLevelObject3D(line->block, line->coordinates[i]);
            Level3D_addBlock(level, obj);
        }

        token = strtok(NULL, "\n");
    }

    return level;
}

#endif