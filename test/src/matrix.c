#include <stdio.h>
#include <string.h>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;

    CoordinateMatrix2D* m1 = create2DCoordinateMatrix(0, 3, 0, 3, createCoordinate2D(0, 0));

    r |= assert(m1->minX == 0);
    r |= assert(m1->maxX == 3);
    r |= assert(m1->minY == 0);
    r |= assert(m1->maxY == 3);
    r |= assert(m1->start->x == 0);
    r |= assert(m1->start->y == 0);
    r |= assert(CoordinateMatrix2D_size(m1) == 16);
    r |= assert(strcmp(CoordinateMatrix2D_toString(m1), "(0, 3, 0, 3)^[0, 0]") == 0);

    CoordinateMatrix3D* m2 = create3DCoordinateMatrix(0, 3, 0, 3, 0, 3, createCoordinate3D(0, 0, 0));

    r |= assert(m2->minX == 0);
    r |= assert(m2->maxX == 3);
    r |= assert(m2->minY == 0);
    r |= assert(m2->maxY == 3);
    r |= assert(m2->minZ == 0);
    r |= assert(m2->maxZ == 3);
    r |= assert(m2->start->x == 0);
    r |= assert(m2->start->y == 0);
    r |= assert(m2->start->z == 0);
    r |= assert(CoordinateMatrix3D_size(m2) == 64);
    r |= assert(strcmp(CoordinateMatrix3D_toString(m2), "(0, 3, 0, 3, 0, 3)^[0, 0, 0]") == 0);

    CoordinateMatrix2D* m3 = CoordinateMatrix2D_fromString("(-1, 4, -1, 4)^[2, 3.5]");

    r |= assert(m3->minX == -1);
    r |= assert(m3->maxX == 4);
    r |= assert(m3->minY == -1);
    r |= assert(m3->maxY == 4);
    r |= assert(m3->start->x == 2);
    r |= assert(m3->start->y == 3.5);
    r |= assert(CoordinateMatrix2D_size(m3) == 36);

    CoordinateMatrix3D* m4 = CoordinateMatrix3D_fromString("(-1, 4, -1, 4, -1, 4)^[2, 3.5, 4.25]");

    r |= assert(m4->minX == -1);
    r |= assert(m4->maxX == 4);
    r |= assert(m4->minY == -1);
    r |= assert(m4->maxY == 4);
    r |= assert(m4->minZ == -1);
    r |= assert(m4->maxZ == 4);
    r |= assert(m4->start->x == 2);
    r |= assert(m4->start->y == 3.5);
    r |= assert(m4->start->z == 4.25);
    r |= assert(CoordinateMatrix3D_size(m4) == 216);

    return r;
}