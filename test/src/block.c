#include <stdio.h>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;

    Block* c1 = createBlock("block");
    Block_setProperty(c1, "key", "value");

    r |= assert(c1->name == "block");
    r |= assert(Block_getProperty(c1, "key") == "value");

    Block* c2 = createBlock("block");
    Block_setProperty(c2, "key", "value");
    Block_setProperty(c2, "key2", "value2");

    r |= assert(c2->name == "block");
    r |= assert(c2->propertyCount == 2);

    return r;
}