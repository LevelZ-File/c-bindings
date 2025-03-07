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

char* __trim(const char* str) {
    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    int i = 0;
    while (isspace(str0[i])) i++;

    int j = strlen(str0) - 1;
    while (isspace(str0[j])) j--;

    char* str1 = (char*) malloc(j - i + 2);
    strncpy(str1, str0 + i, j - i + 1);
    str1[j - i + 1] = '\0';
    free(str0);

    return str1;
}

LevelHeader** __readHeaders(char** input) {
    LevelHeader** headers = 0;

    int index = 0;
    while (1) {
        char* line = input[index];
        if (line == 0) break;

        LevelHeader* header = LevelHeader_fromString(__trim(line));
        if (headers == 0)
            headers = (LevelHeader**) malloc(2 * sizeof(LevelHeader*));
        else
            headers = (LevelHeader**) realloc(headers, (index + 2) * sizeof(LevelHeader*));

        headers[index] = header;
        headers[index + 1] = 0;
        index++;
    }

    return headers;
}

Coordinate2D** __read2DPoints(const char* input) {
    Coordinate2D** points = 0;

    char* trimmed = __trim(input);
    char* str0 = (char*) malloc(strlen(trimmed) + 1);
    strcpy(str0, trimmed);

    char* start = str0;
    char* end;
    while (*start) {
        end = start;
        while (*end && *end != '*') end++;
        char* token = (char*) malloc(end - start + 1);
        strncpy(token, start, end - start);
        token[end - start] = '\0';

        if (token[0] == '(') {
            CoordinateMatrix2D* matrix = CoordinateMatrix2D_fromString(token);
            if (matrix == 0) {
                free(str0);
                return 0;
            }
            
            int size = CoordinateMatrix2D_size(matrix);

            if (points == 0)
                points = CoordinateMatrix2D_coordinates(matrix);
            else {
                int length = 0;
                while (points[length] != 0) length++;

                points = (Coordinate2D**) realloc(points, (length + size + 1) * sizeof(Coordinate2D));

                Coordinate2D** matrixPoints = CoordinateMatrix2D_coordinates(matrix);
                for (int i = 0; i < size; i++) {
                    points[length + i] = matrixPoints[i];
                }

                points[length + size] = 0;
            }
        } else {
            Coordinate2D* point = Coordinate2D_fromString(token);

            if (point == 0) {
                free(str0);
                return 0;
            }

            if (points == 0) {
                points = (Coordinate2D**) malloc(2 * sizeof(Coordinate2D));
                points[0] = point;
                points[1] = 0;
            } else {
                int length = 0;
                while (points[length] != 0) length++;

                points = (Coordinate2D**) realloc(points, (length + 2) * sizeof(Coordinate2D));
                
                points[length] = point;
                points[length + 1] = 0;
            }
        }

        start = (*end) ? end + 1 : end;
    }

    free(str0);
    return points;
}

Coordinate3D** __read3DPoints(char* input) {
    Coordinate3D** points = 0;

    char* trimmed = __trim(input);
    char* str0 = (char*) malloc(strlen(trimmed) + 1);
    strcpy(str0, trimmed);

    char* start = str0;
    char* end;
    while (*start) {
        end = start;
        while (*end && *end != '*') end++;
        char* token = (char*) malloc(end - start + 1);
        strncpy(token, start, end - start);
        token[end - start] = '\0';

        if (token[0] == '(') {
            CoordinateMatrix3D* matrix = CoordinateMatrix3D_fromString(token);
            if (matrix == 0) {
                free(str0);
                return 0;
            }
            
            int size = CoordinateMatrix3D_size(matrix);

            if (points == 0)
                points = CoordinateMatrix3D_coordinates(matrix);
            else {
                int length = 0;
                while (points[length] != 0) length++;

                points = (Coordinate3D**) realloc(points, (length + size + 1) * sizeof(Coordinate3D));

                Coordinate3D** matrixPoints = CoordinateMatrix3D_coordinates(matrix);
                for (int i = 0; i < size; i++) {
                    points[length + i] = matrixPoints[i];
                }

                points[length + size] = 0;
            }
        } else {
            Coordinate3D* point = Coordinate3D_fromString(token);

            if (point == 0) {
                free(str0);
                return 0;
            }

            if (points == 0) {
                points = (Coordinate3D**) malloc(2 * sizeof(Coordinate3D));
                points[0] = point;
                points[1] = 0;
            } else {
                int length = 0;
                while (points[length] != 0) length++;

                points = (Coordinate3D**) realloc(points, (length + 2) * sizeof(Coordinate3D));
                
                points[length] = point;
                points[length + 1] = 0;
            }
        }

        start = (*end) ? end + 1 : end;
    }

    free(str0);
    return points;
}

typedef struct LevelZLine2D {
    Block* block;
    Coordinate2D** coordinates;
} LevelZLine2D;

LevelZLine2D* __read2DLine(const char* input) {
    LevelZLine2D* line = (LevelZLine2D*) malloc(sizeof(LevelZLine2D));

    char* str0 = (char*) malloc(strlen(input) + 1);
    strcpy(str0, input);

    char* blockStr = __trim(strtok(str0, ":"));
    char* coordinateStr = __trim(strtok(0, ":"));

    Block* block = Block_fromString(blockStr);
    Coordinate2D** coordinates = __read2DPoints(coordinateStr);

    line->block = block;
    line->coordinates = coordinates;

    free(str0);
    return line;
}

typedef struct LevelZLine3D {
    Block* block;
    Coordinate3D** coordinates;
} LevelZLine3D;

LevelZLine3D* __read3DLine(const char* input) {
    LevelZLine3D* line = (LevelZLine3D*) malloc(sizeof(LevelZLine3D));

    char* str0 = (char*) malloc(strlen(input) + 1);
    strcpy(str0, input);

    char* blockStr = __trim(strtok(str0, ":"));
    char* coordinateStr = __trim(strtok(0, ":"));

    Block* block = Block_fromString(blockStr);
    Coordinate3D** coordinates = __read3DPoints(coordinateStr);
    line->block = block;
    line->coordinates = coordinates;

    free(str0);
    return line;
}

// Implementation

/**
 * Reads a Level2D from a string.
 * @param str The string representation of the Level2D.
 * @return The Level2D.
 */
Level2D* readLevel2D(const char* str) {
    Level2D* level = (Level2D*) malloc(sizeof(Level2D));

    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    char* token = strtok(str0, "\n");
    while (token != 0) {
        if (strcmp(token, LEVELZ_HEADER_END) == 0) {
            break;
        }

        LevelHeader* header = LevelHeader_fromString(__trim(token));
        if (header->name == "type" && header->value != "2") {
            free(str0);
            return 0;
        }

        Level2D_addHeader(level, header->name, header->value);

        if (header->name == "spawn") {
            Coordinate2D* spawn = Coordinate2D_fromString(header->value);
            level->spawn = spawn;
        }

        token = strtok(0, "\n");
    }

    token = strtok(0, "\n");
    while (token != 0) {
        if (strcmp(token, LEVELZ_END) == 0) {
            break;
        }

        LevelZLine2D* line = __read2DLine(__trim(token));
        
        for (int i = 0; i < sizeof(line->coordinates) / sizeof(Coordinate2D); i++) {
            LevelObject2D* obj = createLevelObject2D(line->block, line->coordinates[i]);
            Level2D_addBlock(level, obj);
        }

        token = strtok(0, "\n");
    }

    free(str0);
    return level;
}

/**
 * Reads a Level3D from a string.
 * @param str The string representation of the Level3D.
 * @return The Level3D.
 */
Level3D* readLevel3D(const char* str) {
    Level3D* level = createLevel3D(createCoordinate3D(0, 0, 0));

    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    char* token = strtok(str0, "\n");
    while (token != 0) {
        if (strcmp(token, LEVELZ_HEADER_END) == 0) {
            break;
        }

        LevelHeader* header = LevelHeader_fromString(__trim(token));
        if (header->name == "type" && header->value != "3") {
            free(str0);
            return 0;
        }

        Level3D_addHeader(level, header->name, header->value);

        if (header->name == "spawn") {
            Coordinate3D* spawn = Coordinate3D_fromString(header->value);
            level->spawn = spawn;
        }

        token = strtok(0, "\n");
    }

    token = strtok(0, "\n");
    while (token != 0) {
        if (strcmp(token, LEVELZ_END) == 0) {
            break;
        }

        LevelZLine3D* line = __read3DLine(__trim(token));

        for (int i = 0; i < sizeof(line->coordinates) / sizeof(Coordinate3D); i++) {
            LevelObject3D* obj = createLevelObject3D(line->block, line->coordinates[i]);
            Level3D_addBlock(level, obj);
        }

        token = strtok(0, "\n");
    }

    free(str0);
    return level;
}

/**
 * Parses a Level2D from a file.
 * @param path The path to the file.
 * @return The Level2D.
 */
Level2D* parseFile2D(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == 0) return 0;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*) malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);

    Level2D* level = readLevel2D(buffer);
    free(buffer);

    return level;
}

/**
 * Parses a Level3D from a file.
 * @param path The path to the file.
 * @return The Level3D.
 */
Level3D* parseFile3D(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == 0) return 0;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*) malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);

    Level3D* level = readLevel3D(buffer);
    free(buffer);

    return level;
}

#endif