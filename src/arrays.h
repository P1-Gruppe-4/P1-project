//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_ARRAYS_H
#define P1_GRUPPE4_ARRAYS_H

#include <stdlib.h>
#include <stdio.h>
#include <types.h>


//prototypes from arrays.c
lot **array_alloc(int length, int width);

lot **array_fill(lot **pointer, int length, int width);

void array_free(lot **pointer, int length);

void array_print(lot **pointer, int length, int width);

#endif //P1_GRUPPE4_ARRAYS_H