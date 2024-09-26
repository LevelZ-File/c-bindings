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

    return r;
}