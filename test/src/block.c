#include <stdio.h>

#include "test.h"
#include "levelz.h"

int main() {
    int r = 0;

    Block* b1 = createBlock("block");

    r |= assert(strcmp(b1->name, "block") == 0);

    Block* b2 = createBlock("block");
    Block_setProperty(b2, "key", "value");
    Block_setProperty(b2, "key2", "value2");

    r |= assert(strcmp(b2->name, "block") == 0);
    r |= assert(b2->propertyCount == 2);
    r |= assert(strcmp(Block_getProperty(b2, "key"), "value") == 0);
    r |= assert(strcmp(Block_getProperty(b2, "key2"), "value2") == 0);

    Block* b3 = Block_fromString("block<key=value>");

    r |= assert(strcmp(b3->name, "block") == 0);
    r |= assert(b3->propertyCount == 1);
    r |= assert(strcmp(Block_getProperty(b3, "key"), "value") == 0);

    Block* b4 = Block_fromString("block<key=value,key2=value2,key3=value3>");

    r |= assert(strcmp(b4->name, "block") == 0);
    r |= assert(b4->propertyCount == 3);
    r |= assert(strcmp(Block_getProperty(b4, "key"), "value") == 0);
    r |= assert(strcmp(Block_getProperty(b4, "key2"), "value2") == 0);
    r |= assert(strcmp(Block_getProperty(b4, "key3"), "value3") == 0);
    r |= assert(strcmp(Block_getProperty(b4, "key4"), "") == 0);

    Block* b5 = createBlock("block");
    Block_setProperty(b5, "property", "1");

    char* str = Block_toString(b5);

    r |= assert(strcmp(str, "block<property=1>") == 0);

    return r;
}