#ifndef LEVELZ_COORDINATE_H
#define LEVELZ_COORDINATE_H

#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

/**
 * Represents a coordinate in a 2D space.
 */
typedef struct Coordinate2D {
    /**
     * The x value of the coordinate.
     */
    double x;

    /**
     * The y value of the coordinate.
     */
    double y;
} Coordinate2D;

/**
 * Creates a new Coordinate2D.
 * @param x The x value of the coordinate.
 * @param y The y value of the coordinate.
 * @return A new Coordinate.
 */
Coordinate2D* createCoordinate2D(double x, double y) {
    Coordinate2D* c = (Coordinate2D*) malloc(sizeof(Coordinate2D));
    c->x = x;
    c->y = y;
    return c;
}

/**
 * Calculates the distance between two 2D coordinates.
 * @param a The first coordinate.
 * @param b The second coordinate.
 * @return The distance between the two coordinates.
 */
double Coordinate2D_distance(Coordinate2D* a, Coordinate2D* b) {
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}

/**
 * Calculates the magnitude of a 2D coordinate.
 * @param a The coordinate.
 * @return The magnitude of the coordinate.
 */
double Coordinate2D_magnitude(Coordinate2D* a) {
    return sqrt(pow(a->x, 2) + pow(a->y, 2));
}

/**
 * Adds two 2D coordinates.
 * @param a The coordinate.
 * @param b The second coordinate.
 * @return The sum of the two coordinates.
 */
Coordinate2D* Coordinate2D_add(Coordinate2D* a, Coordinate2D* b) {
    return createCoordinate2D(a->x + b->x, a->y + b->y);
}

/**
 * Subtracts two 2D coordinates.
 * @param a The coordinate.
 * @param b The second coordinate.
 * @return The difference of the two coordinates.
 */
Coordinate2D* Coordinate2D_subtract(Coordinate2D* a, Coordinate2D* b) {
    return createCoordinate2D(a->x - b->x, a->y - b->y);
}

/**
 * Converts a Coordinate2D to a string.
 * @param c The coordinate.
 * @return The string representation of the coordinate.
 */
char* Coordinate2D_toString(Coordinate2D* c) {
    char* str = (char*) malloc(20);
    sprintf(str, "[%g, %g]", c->x, c->y);
    return str;
}

/**
 * Converts a string to a Coordinate2D.
 * @param str The string representation of the coordinate.
 * @return The Coordinate2D.
 */
Coordinate2D* Coordinate2D_fromString(const char* str) {
    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    char* x0 = strtok(str0, "[], \t");
    double x = atof(x0);

    char* y0 = strtok(0, "[], \t");
    double y = atof(y0);

    free(str0);
    return createCoordinate2D(x, y);
}

/**
 * Represents a coordinate in a 3D space.
 */
typedef struct Coordinate3D {
    /**
     * The x value of the coordinate.
     */
    double x;

    /**
     * The y value of the coordinate.
     */
    double y;

    /**
     * The z value of the coordinate.
     */
    double z;
} Coordinate3D;

/**
 * Creates a new Coordinate3D.
 * @param x The x value of the coordinate.
 * @param y The y value of the coordinate.
 * @param z The z value of the coordinate.
 * @return A new Coordinate.
 */
Coordinate3D* createCoordinate3D(double x, double y, double z) {
    Coordinate3D* c = (Coordinate3D*) malloc(sizeof(Coordinate3D));
    c->x = x;
    c->y = y;
    c->z = z;
    return c;
}

/**
 * Calculates the distance between two 3D coordinates.
 * @param a The first coordinate.
 * @param b The second coordinate.
 * @return The distance between the two coordinates.
 */
double Coordinate3D_distance(Coordinate3D* a, Coordinate3D* b) {
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

/**
 * Calculates the magnitude of a 3D coordinate.
 * @param a The coordinate.
 * @return The magnitude of the coordinate.
 */
double Coordinate3D_magnitude(Coordinate3D* a) {
    return sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

/**
 * Adds two 3D coordinates.
 * @param a The coordinate.
 * @param b The second coordinate.
 * @return The sum of the two coordinates.
 */
Coordinate3D* Coordinate3D_add(Coordinate3D* a, Coordinate3D* b) {
    return createCoordinate3D(a->x + b->x, a->y + b->y, a->z + b->z);
}

/**
 * Subtracts two 3D coordinates.
 * @param a The coordinate.
 * @param b The second coordinate.
 * @return The difference of the two coordinates.
 */
Coordinate3D* Coordinate3D_subtract(Coordinate3D* a, Coordinate3D* b) {
    return createCoordinate3D(a->x - b->x, a->y - b->y, a->z - b->z);
}

/**
 * Converts a Coordinate3D to a string.
 * @param c The coordinate.
 * @return The string representation of the coordinate.
 */
char* Coordinate3D_toString(Coordinate3D* c) {
    char* str = (char*) malloc(20);
    sprintf(str, "[%g, %g, %g]", c->x, c->y, c->z);
    return str;
}

/**
 * Converts a string to a Coordinate3D.
 * @param str The string representation of the coordinate.
 * @return The Coordinate3D.
 */
Coordinate3D* Coordinate3D_fromString(char* str) {
    char* str0 = (char*) malloc(strlen(str) + 1);
    strcpy(str0, str);

    char* x0 = strtok(str0, "[], \t");
    double x = atof(x0);

    char* y0 = strtok(0, "[], \t");
    double y = atof(y0);

    char* z0 = strtok(0, "[], \t");
    double z = atof(z0);

    free(str0);
    return createCoordinate3D(x, y, z);
}

#endif