//
// Created by john on 21/11/2025.
//

#ifndef P1_GRUPPE4_MAIN_H
#define P1_GRUPPE4_MAIN_H
#include <stddef.h>

#endif //P1_GRUPPE4_MAIN_H

//structs for project

typedef struct lot{
    int status; //0 for free, 1 for occupied
    int handicap; //0 for no, 1 for yes
} lot;

typedef struct car
{
    int length;
    int width;
    int doorLength;
} car;

//prototypes from arrays.c
lot** ArrayAlloc(int length, int width);
lot** ArrayFill(lot** pointer, int length, int width);
void ArrayPrint(lot** pointer, int length, int width);
void ArrayFree(lot** pointer, int length, int width);


