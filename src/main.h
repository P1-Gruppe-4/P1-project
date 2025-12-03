//
// Created by john on 21/11/2025.
//

#ifndef P1_GRUPPE4_MAIN_H
#define P1_GRUPPE4_MAIN_H

//necessary headerfiles
#include <stddef.h>
#include <stdio.h>

//enum passenger type
typedef enum {
    Adult,
    Child,
    Elderly
} passengerType;

//structs for project

typedef struct car {
    int length;
    int width;
    int doorLength;
    int handicap;
    double durationStay;
    char *size;
    passengerType passenger;
    char *role;
} car;

typedef struct lot {
    int status; //0 for free, 1 for occupied
    int handicap; //0 for no, 1 for yes
    double durationStay; // double for hours of duration staying
    int xIndex;
    int yIndex;
    char *size;
    passengerType passenger;
    char *role;
    car car;
} lot;

typedef struct lot lot;


typedef struct car car;

//prototypes from arrays.c
lot **ArrayAlloc(int length, int width);

lot **ArrayFill(lot **pointer, int length, int width);

void ArrayPrint(lot **pointer, int length, int width);

//void ArrayFree(lot** pointer, int length, int width);
void ArrangeCar(lot **parkingLot, car Car, int x0, int y0);

//prototypes from menu.c
void create_menu();

void ArrangeCar(lot **parkingLot, car Car, int x0, int y0);

//prototypes from save.c
void auto_save(lot **pointer, int length, int width);

lot **load_save(FILE *savefile);

//prototypes from mapToLot.c
int isHandicap(lot lot, int carHand);
int isType(lot lot, char *carType);
int isRole(lot lot, char *role);

lot *filterSpots(car carUser, lot **pLot, int length, int width, int *matches);

double durationScore(lot *l, car c);
double passengerScore(lot *l, car c);
double calcScore(double passengerScore, double durationScore);

void mapToLot(car carUser, lot **pLot, int length, int width, int *matchL, int *matchW);

#endif //P1_GRUPPE4_MAIN_H
