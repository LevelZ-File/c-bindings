#ifndef LEVELZ_TEST_H
#define LEVELZ_TEST_H

int count = 1;

int assert(int condition) {
    printf("#%d: %s\n", count, condition ? "PASS" : "FAIL");
    count++;
    return !condition;
}

#endif