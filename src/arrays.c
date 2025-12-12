/*
 * OBS !!!!!
 * Denne kode stammer fra oprindeligt: https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * Da jeg havde problemer med at få allocationen af arena arrayet til at virke. Jeg har blot afproevet og aendret koden, saaledes, at den passer til projektet
 */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"

// Function that dynamically allocates a two dimensional array for the parkinglot
lot **array_alloc(int length, int width) {
    lot **parking_lot = malloc(sizeof(*parking_lot) * (size_t) length);

    for (size_t i = 0; i < (size_t) length; i++) {
        parking_lot[i] = malloc(sizeof(**parking_lot) * (size_t) width);
    }

    return parking_lot;
}

// Function that sets status to free for all elements in array
lot **array_fill(lot **parking_lot, int length, int width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            parking_lot[i][j].status = Status_Free;
        }
    }

    return parking_lot;
}

// Function that frees the dynamically allocated array
void array_free(lot **parking_lot, int length) {
    for (int i = 0; i < length; i++) {
        free(parking_lot[i]);
    }
    free(parking_lot);
}

//This functions print out the parkingLot array in a 2d grid. It is not necessarily suited for the later, user-interface
//of our application and should maybe rather only be used for inital debugging purposes
void array_print(lot **parking_lot, int length, int width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == 0) {
                printf("[ ]");
            } else {
                printf("[%d]", parking_lot[i][j].status);
            }
        }
        printf("\n");
    }
    printf("\n");
}


