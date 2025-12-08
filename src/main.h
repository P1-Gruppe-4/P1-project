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
    Family,
    Elderly
} passengerType;

typedef enum {
    Status_Free,
    Status_Reserved,
    Status_Path,
    Status_Entrance,
    Status_Exit
} LotStatus;

typedef enum {
    Small,
    Medium,
    Big,
    Special
} carSize;

typedef enum {
    Worker,
    VIP,
    Guest
} roleVenue;


//structs for project

typedef struct car {
    int handicap;
    double durationStay;
    carSize size;
    passengerType passenger;
    roleVenue role;
} car;

typedef struct lot {
    LotStatus status;
    int isHandicapSpot; //0 for no, 1 for yes
    double maxDuration; // double for hours of duration staying
    int xIndex;
    int yIndex;
    carSize maxSize;
    passengerType preferredPassenger;
    roleVenue allowedRole;
    car* car;
    int distance;
} lot;

//prototypes from arrays.c
lot **ArrayAlloc(int length, int width);

lot **ArrayFill(lot **pointer, int length, int width);

void ArrayPrint(lot **pointer, int length, int width);

//void ArrayFree(lot** pointer, int length, int width);
void ArrangeCar(lot **parkingLot, car Car, int x0, int y0);

//prototypes from menu.c
void create_menu();

//prototypes from save.c
void auto_save(lot **pointer, int length, int width);

lot **load_save(FILE *savefile);

//prototypes from mapToLot.c
int isHandicap(lot lot, int carHand);
int isType(lot lot, carSize size);
int isRole(lot lot, roleVenue role);

lot *filterSpots(car carUser, lot **pLot, int length, int width, int *matches);

double durationScore(lot *l, car c);
double passengerScore(lot *l, car c);
double calcScore(double passengerScore, double durationScore);

void mapToLot(car carUser, lot **pLot, int length, int width);


//prototypes fra parkingLot.c
int comp(const void *a, const void *b);
void sortPark(lot parkingArr[], int last, int (*fptr)(const void *, const void *));
lot **lotAssigner(lot **parkingLot, int length, int width);
lot **pathCreator(lot **parkingLot, int length, int width);

#endif //P1_GRUPPE4_MAIN_H
