#include <stdio.h>
#include <string.h>

#include "levelz.h"
#include "test.h"

int main() {
    int r = 0;

    // Headers
    char** h1 = malloc(3 * sizeof(char*));
    h1[0] = "@header value";
    h1[1] = "@header2 value2";
    h1[2] = 0;

    LevelHeader** headers = __readHeaders(h1);
    r |= assert(strcmp(headers[0]->name, "header") == 0);
    r |= assert(strcmp(headers[0]->value, "value") == 0);
    r |= assert(strcmp(headers[1]->name, "header2") == 0);
    r |= assert(strcmp(headers[1]->value, "value2") == 0);

    free(h1);

    char** h2 = malloc(4 * sizeof(char*));
    h2[0] = "@type 2";
    h2[1] = "@spawn [0, 0]";
    h2[2] = "@custom value value2";
    h2[3] = 0;

    LevelHeader** headers2 = __readHeaders(h2);
    r |= assert(strcmp(headers2[0]->name, "type") == 0);
    r |= assert(strcmp(headers2[0]->value, "2") == 0);
    r |= assert(strcmp(headers2[1]->name, "spawn") == 0);
    r |= assert(strcmp(headers2[1]->value, "[0, 0]") == 0);
    r |= assert(strcmp(headers2[2]->name, "custom") == 0);
    r |= assert(strcmp(headers2[2]->value, "value value2") == 0);

    free(h2);
    // Coordinates

    char* c1 = "[0, 0]*[0, 1]*[0, 2]";
    Coordinate2D** coordinates = __read2DPoints(c1);

    r |= assert(coordinates[0]->x == 0);
    r |= assert(coordinates[0]->y == 0);
    r |= assert(coordinates[1]->x == 0);
    r |= assert(coordinates[1]->y == 1);
    r |= assert(coordinates[2]->x == 0);
    r |= assert(coordinates[2]->y == 2);

    char* c2 = "[0, 0, 0]*[0, 1, 2]*[0, 2, 4]";

    Coordinate3D** coordinates2 = __read3DPoints(c2);
    r |= assert(coordinates2[0]->x == 0);
    r |= assert(coordinates2[0]->y == 0);
    r |= assert(coordinates2[0]->z == 0);
    r |= assert(coordinates2[1]->x == 0);
    r |= assert(coordinates2[1]->y == 1);
    r |= assert(coordinates2[1]->z == 2);
    r |= assert(coordinates2[2]->x == 0);
    r |= assert(coordinates2[2]->y == 2);
    r |= assert(coordinates2[2]->z == 4);

    // Lines

    char* l1 = "block: [0, 0]*[0, 1]*[0, 2]";

    LevelZLine2D* line = __read2DLine(l1);

    r |= assert(strcmp(line->block->name, "block") == 0);
    r |= assert(line->coordinates[0]->x == 0);
    r |= assert(line->coordinates[0]->y == 0);
    r |= assert(line->coordinates[1]->x == 0);
    r |= assert(line->coordinates[1]->y == 1);
    r |= assert(line->coordinates[2]->x == 0);
    r |= assert(line->coordinates[2]->y == 2);

    char* l2 = "block: [0, 0, 0]*[0, 1, 2]*[0, 2, 4]";
    LevelZLine3D* line2 = __read3DLine(l2);

    r |= assert(strcmp(line2->block->name, "block") == 0);
    r |= assert(line2->coordinates[0]->x == 0);
    r |= assert(line2->coordinates[0]->y == 0);
    r |= assert(line2->coordinates[0]->z == 0);
    r |= assert(line2->coordinates[1]->x == 0);
    r |= assert(line2->coordinates[1]->y == 1);
    r |= assert(line2->coordinates[1]->z == 2);
    r |= assert(line2->coordinates[2]->x == 0);
    r |= assert(line2->coordinates[2]->y == 2);
    r |= assert(line2->coordinates[2]->z == 4);

    char* l3 = "block<key=value>: [0, 2]*(0, 2, 0, 2)^[0, 1]";
    
    LevelZLine2D* line3 = __read2DLine(l3);

    r |= assert(strcmp(line3->block->name, "block") == 0);
    r |= assert(strcmp(Block_getProperty(line3->block, "key"), "value") == 0);
    r |= assert(line3->coordinates[0]->x == 0);
    r |= assert(line3->coordinates[0]->y == 2);

    char* l4 = "block<key=value,key2=value2>: [0, 2, 0]*(0, 2, 0, 2, 0, 2)^[0, 4, 4]";

    LevelZLine3D* line4 = __read3DLine(l4);

    r |= assert(strcmp(line4->block->name, "block") == 0);
    r |= assert(strcmp(Block_getProperty(line4->block, "key"), "value") == 0);
    r |= assert(strcmp(Block_getProperty(line4->block, "key2"), "value2") == 0);

    return r;
}