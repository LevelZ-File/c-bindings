#include <stdio.h>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;

    Coordinate2D* c = createCoordinate2D(1, 2);
    r |= assert(c->x == 1);
    r |= assert(c->y == 2);

    Coordinate3D* c2 = createCoordinate3D(1, 2, 3);
    r |= assert(c2->x == 1);
    r |= assert(c2->y == 2);
    r |= assert(c2->z == 3);

    Coordinate2D* c3 = Coordinate2D_fromString("[1, 2]");
    r |= assert(c3->x == 1);
    r |= assert(c3->y == 2);

    Coordinate3D* c4 = Coordinate3D_fromString("[1, 2, 3]");
    r |= assert(c4->x == 1);
    r |= assert(c4->y == 2);
    r |= assert(c4->z == 3);

    Coordinate2D* c5 = Coordinate2D_fromString("[1.5, -2]");
    r |= assert(c5->x == 1.5);
    r |= assert(c5->y == -2);

    Coordinate3D* c6 = Coordinate3D_fromString("[1.5, -2, 3.75]");
    r |= assert(c6->x == 1.5);
    r |= assert(c6->y == -2);
    r |= assert(c6->z == 3.75);

    return r;
}