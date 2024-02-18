#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "funciones.h"

void test_numRandom() {
    int min = 5, max = 10;
    int result = numRandom(min, max);

    printf("Testing numRandom(%d, %d): %d\n", min, max, result);
}

void test_estaEnArray() {
    char **arr = (char *[]){"Materia1", "Materia2", "Materia3"};
    int size = 3;

    assert(estaEnArray(&arr, "Materia2", size) == 1);
    assert(estaEnArray(&arr, "Materia4", size) == 0);
}

int main() {
    test_numRandom();
    test_estaEnArray();

    return 0;
}