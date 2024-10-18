#ifndef LEVELZ_MATRIX_H
#define LEVELZ_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coordinate.h"

/**
 * Represents a matrix of coordinates in a 2D space.
 */
typedef struct CoordinateMatrix2D {
    /**
     * The minimum x value of the matrix.
     */
    int minX;
    /**
     * The maximum x value of the matrix.
     */
    int maxX;
    /**
     * The minimum y value of the matrix.
     */
    int minY;
    /**
     * The maximum y value of the matrix.
     */
    int maxY;

    /**
     * The starting coordinate of the matrix.
     */
    Coordinate2D* start;
} CoordinateMatrix2D;

/**
 * Creates a new CoordinateMatrix2D.
 * @param minX The minimum x value of the matrix.
 * @param maxX The maximum x value of the matrix.
 * @param minY The minimum y value of the matrix.
 * @param maxY The maximum y value of the matrix.
 * @param start The starting coordinate of the matrix.
 * @return A new CoordinateMatrix2D.
 */
CoordinateMatrix2D* create2DCoordinateMatrix(int minX, int maxX, int minY, int maxY, Coordinate2D* start) {
    CoordinateMatrix2D* matrix = (CoordinateMatrix2D*) malloc(sizeof(CoordinateMatrix2D));
    matrix->minX = minX;
    matrix->maxX = maxX;
    matrix->minY = minY;
    matrix->maxY = maxY;
    matrix->start = start;
    return matrix;
}

/**
 * Gets the size of a CoordinateMatrix2D.
 * @param matrix The matrix.
 * @return The size of the matrix.
 */
int CoordinateMatrix2D_size(CoordinateMatrix2D* matrix) {
    return ((matrix->maxX + 1) - matrix->minX) * ((matrix->maxY + 1) - matrix->minY);
}

/**
 * Gets the coordinates of a CoordinateMatrix2D.
 * @param matrix The matrix.
 * @return A list of coordinates in the matrix.
 */
Coordinate2D** CoordinateMatrix2D_coordinates(CoordinateMatrix2D* matrix) {
    int size = CoordinateMatrix2D_size(matrix);
    Coordinate2D** coordinates = (Coordinate2D**) malloc(size * sizeof(Coordinate2D));

    int minX = matrix->minX + matrix->start->x;
    int minY = matrix->minY + matrix->start->y;
    int maxX = matrix->maxX + matrix->start->x;
    int maxY = matrix->maxY + matrix->start->y;

    int index = 0;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            coordinates[index] = createCoordinate2D(x, y);
            index++;
        }
    }

    return coordinates;
}

/**
 * Gets the coordinate at a specific index.
 * @param matrix The matrix.
 * @param index The index.
 * @return The coordinate at the index.
 */
Coordinate2D* CoordinateMatrix2D_coordinateAt(CoordinateMatrix2D* matrix, int index) {
    int x = matrix->minX + (index % (matrix->maxX - matrix->minX));
    int y = matrix->minY + (index / (matrix->maxX - matrix->minX));
    return createCoordinate2D(x, y);
}

/**
 * Converts a CoordinateMatrix2D to a string.
 * @param matrix The matrix.
 * @return The string representation of the matrix.
 */
char* CoordinateMatrix2D_toString(CoordinateMatrix2D* matrix) {
    if (matrix == 0) return 0;

    int size = snprintf(NULL, 0, "(%d, %d, %d, %d)^%s", matrix->minX, matrix->maxX, matrix->minY, matrix->maxY, Coordinate2D_toString(matrix->start));
    char* str = (char*) malloc(size);
    sprintf(str, "(%d, %d, %d, %d)^%s", matrix->minX, matrix->maxX, matrix->minY, matrix->maxY, Coordinate2D_toString(matrix->start));
    return str;
}

/**
 * Converts a string to a CoordinateMatrix2D.
 * @param str The string representation of the matrix.
 * @return The CoordinateMatrix2D.
 */
CoordinateMatrix2D* CoordinateMatrix2D_fromString(const char* str) {
    if (str == 0) return 0;

    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    int minX, minY, maxX, maxY;
    double x, y;

    char* token = strtok(str0, "()[]^, \t");
    int i = 0;
    while (token != 0) {
        switch (i) {
            case 0: minX = atoi(token); break;
            case 1: maxX = atoi(token); break;
            case 2: minY = atoi(token); break;
            case 3: maxY = atoi(token); break;
            case 4: x = atof(token); break;
            case 5: y = atof(token); break;
        }

        token = strtok(0, "()[]^, \t");
        i++;
    }

    free(str0);
    Coordinate2D* start = createCoordinate2D(x, y);
    return create2DCoordinateMatrix(minX, maxX, minY, maxY, start);
}

/**
 * Represents a matrix of coordinates in a 3D space.
 */
typedef struct CoordinateMatrix3D {
    /**
     * The minimum x value of the matrix.
     */
    int minX;
    /**
     * The maximum x value of the matrix.
     */
    int maxX;
    /**
     * The minimum y value of the matrix.
     */
    int minY;
    /**
     * The maximum y value of the matrix.
     */
    int maxY;
    /**
     * The minimum z value of the matrix.
     */
    int minZ;
    /**
     * The maximum z value of the matrix.
     */
    int maxZ;

    /**
     * The starting coordinate of the matrix.
     */
    Coordinate3D* start;
} CoordinateMatrix3D;

/**
 * Creates a new CoordinateMatrix3D.
 * @param minX The minimum x value of the matrix.
 * @param maxX The maximum x value of the matrix.
 * @param minY The minimum y value of the matrix.
 * @param maxY The maximum y value of the matrix.
 * @param minZ The minimum z value of the matrix.
 * @param maxZ The maximum z value of the matrix.
 * @param start The starting coordinate of the matrix.
 * @return A new CoordinateMatrix3D.
 */
CoordinateMatrix3D* create3DCoordinateMatrix(int minX, int maxX, int minY, int maxY, int minZ, int maxZ, Coordinate3D* start) {
    CoordinateMatrix3D* matrix = (CoordinateMatrix3D*) malloc(sizeof(CoordinateMatrix3D));
    matrix->minX = minX;
    matrix->maxX = maxX;
    matrix->minY = minY;
    matrix->maxY = maxY;
    matrix->minZ = minZ;
    matrix->maxZ = maxZ;
    matrix->start = start;
    return matrix;
}

/**
 * Gets the size of a CoordinateMatrix3D.
 * @param matrix The matrix.
 * @return The size of the matrix.
 */
int CoordinateMatrix3D_size(CoordinateMatrix3D* matrix) {
    return ((matrix->maxX + 1) - matrix->minX) * ((matrix->maxY + 1) - matrix->minY) * ((matrix->maxZ + 1) - matrix->minZ);
}

/**
 * Gets the coordinates of a CoordinateMatrix3D.
 * @param matrix The matrix.
 * @return A list of coordinates in the matrix.
 */
Coordinate3D** CoordinateMatrix3D_coordinates(CoordinateMatrix3D* matrix) {
    int size = CoordinateMatrix3D_size(matrix);
    Coordinate3D** coordinates = (Coordinate3D**) malloc(size * sizeof(Coordinate3D));

    int minX = matrix->minX + matrix->start->x;
    int minY = matrix->minY + matrix->start->y;
    int minZ = matrix->minZ + matrix->start->z;
    int maxX = matrix->maxX + matrix->start->x;
    int maxY = matrix->maxY + matrix->start->y;
    int maxZ = matrix->maxZ + matrix->start->z;

    int index = 0;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            for (int z = minZ; z <= maxZ; z++) {
                coordinates[index] = createCoordinate3D(x, y, z);
                index++;
            }
        }
    }

    return coordinates;
}

/**
 * Gets the coordinate at a specific index.
 * @param matrix The matrix.
 * @param index The index.
 * @return The coordinate at the index.
 */
Coordinate3D* CoordinateMatrix3D_coordinateAt(CoordinateMatrix3D* matrix, int index) {
    int x = matrix->minX + (index % (matrix->maxX - matrix->minX));
    int y = matrix->minY + ((index / (matrix->maxX - matrix->minX)) % (matrix->maxY - matrix->minY));
    int z = matrix->minZ + (index / ((matrix->maxX - matrix->minX) * (matrix->maxY - matrix->minY)));
    return createCoordinate3D(x, y, z);
}

/**
 * Converts a CoordinateMatrix3D to a string.
 * @param matrix The matrix.
 * @return The string representation of the matrix.
 */
char* CoordinateMatrix3D_toString(CoordinateMatrix3D* matrix) {
    if (matrix == 0) return 0;

    int size = snprintf(NULL, 0, "(%d, %d, %d, %d, %d, %d)^%s", matrix->minX, matrix->maxX, matrix->minY, matrix->maxY, matrix->minZ, matrix->maxZ, Coordinate3D_toString(matrix->start));
    char* str = (char*) malloc(size);
    sprintf(str, "(%d, %d, %d, %d, %d, %d)^%s", matrix->minX, matrix->maxX, matrix->minY, matrix->maxY, matrix->minZ, matrix->maxZ, Coordinate3D_toString(matrix->start));
    return str;
}

/**
 * Converts a string to a CoordinateMatrix3D.
 * @param str The string representation of the matrix.
 * @return The CoordinateMatrix3D.
 */
CoordinateMatrix3D* CoordinateMatrix3D_fromString(char* str) {
    if (str == 0) return 0;

    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    int minX, minY, maxX, maxY, minZ, maxZ;
    double x, y, z;

    char* token = strtok(str0, "()[]^, \t");
    int i = 0;
    while (token != 0) {
        switch (i) {
            case 0: minX = atoi(token); break;
            case 1: maxX = atoi(token); break;
            case 2: minY = atoi(token); break;
            case 3: maxY = atoi(token); break;
            case 4: minZ = atoi(token); break;
            case 5: maxZ = atoi(token); break;
            case 6: x = atof(token); break;
            case 7: y = atof(token); break;
            case 8: z = atof(token); break;
        }

        token = strtok(0, "()[]^, \t");
        i++;
    }

    free(str0);
    Coordinate3D* start = createCoordinate3D(x, y, z);
    return create3DCoordinateMatrix(minX, maxX, minY, maxY, minZ, maxZ, start);
}

#endif