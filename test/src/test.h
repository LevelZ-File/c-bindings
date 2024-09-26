#ifndef LEVELZ_TEST_H
#define LEVELZ_TEST_H

int assert(int condition) {
    if (!condition) return 1;

    return 0;
}

#endif