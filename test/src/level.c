#include <stdio.h>
#include <string.h>

#include "levelz.h"
#include "test.h"

int main() {
    int r = 0;

    // Headers

    LevelHeader* h1 = createLevelHeader("header", "value");

    r |= assert(strcmp(h1->name, "header") == 0);
    r |= assert(strcmp(h1->value, "value") == 0);
    r |= assert(strcmp(LevelHeader_toString(h1), "@header value") == 0);

    LevelHeader* h2 = LevelHeader_fromString("@header value");

    r |= assert(strcmp(h2->name, "header") == 0);
    r |= assert(strcmp(h2->value, "value") == 0);

    // Levels

    Level2D* l1 = createLevel2D(createCoordinate2D(0, 0));
    Level2D_addHeader(l1, "header", "value");

    r |= assert(l1->spawn->x == 0);
    r |= assert(l1->spawn->y == 0);
    r |= assert(strcmp(Level2D_getHeader(l1, "header"), "value") == 0);

    Level3D* l2 = createLevel3D(createCoordinate3D(0, 0, 0));
    Level3D_addHeader(l2, "header", "value");

    r |= assert(l2->spawn->x == 0);
    r |= assert(l2->spawn->y == 0);
    r |= assert(l2->spawn->z == 0);
    r |= assert(strcmp(Level3D_getHeader(l2, "header"), "value") == 0);

    Level2D* l3 = createLevel2D(createCoordinate2D(1, 2));
    Level2D_addBlock(l3, createLevelObject2D(createBlock("grass"), createCoordinate2D(0, 0)));
    Level2D_addBlock(l3, createLevelObject2D(createBlock("stone"), createCoordinate2D(1, 2)));
    Level2D_addMatrix(l3, createBlock("cobble"), create2DCoordinateMatrix(0, 2, 0, 2, createCoordinate2D(3, 3)));

    r |= assert(l3->spawn->x == 1);
    r |= assert(l3->spawn->y == 2);
    r |= assert(Level2D_getBlockCount(l3) == 11);
    r |= assert(strcmp(Level2D_getBlock(l3, createCoordinate2D(0, 0))->name, "grass") == 0);
    r |= assert(strcmp(Level2D_getBlock(l3, createCoordinate2D(1, 2))->name, "stone") == 0);
    r |= assert(Level2D_blockCount(l3, "cobble") == 9);

    Level3D* l4 = createLevel3D(createCoordinate3D(1, 2, 3));
    Level3D_addBlock(l4, createLevelObject3D(createBlock("grass"), createCoordinate3D(0, 0, 0)));
    Level3D_addBlock(l4, createLevelObject3D(createBlock("stone"), createCoordinate3D(1, 2, 3)));
    Level3D_addMatrix(l4, createBlock("cobble"), create3DCoordinateMatrix(0, 2, 0, 2, 0, 2, createCoordinate3D(3, 3, 3)));

    r |= assert(l4->spawn->x == 1);
    r |= assert(l4->spawn->y == 2);
    r |= assert(l4->spawn->z == 3);
    r |= assert(Level3D_getBlockCount(l4) == 29);
    r |= assert(strcmp(Level3D_getBlock(l4, createCoordinate3D(0, 0, 0))->name, "grass") == 0);
    r |= assert(strcmp(Level3D_getBlock(l4, createCoordinate3D(1, 2, 3))->name, "stone") == 0);
    r |= assert(Level3D_blockCount(l4, "cobble") == 27);

    return r;
}