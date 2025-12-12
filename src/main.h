//
// Created by john on 21/11/2025.
//

#ifndef P1_GRUPPE4_MAIN_H
#define P1_GRUPPE4_MAIN_H

//necessary headerfiles
#include <stddef.h>
#include <stdio.h>

//Enum for the different passenger types
typedef enum {
    Adult,
    Family,
    Elderly
} passengerType;

//Enum for the different type of status which the individual lot can have
typedef enum {
    Status_Free,
    Status_Reserved,
    Status_Path,
    Status_Entrance,
    Status_Exit
} LotStatus;

//Enum for the different type of car sizes
typedef enum {
    Small,
    Medium,
    Large,
    Special
} carSize;

//Enum for different types of roles at the venue
typedef enum {
    Worker,
    VIP,
    Guest
} roleVenue;


//Structs that will be used in the project

typedef struct car {
    // Whether the car is with handicapped passengers 0 for no, 1 for yes
    int handicap;
    // The duration which the drivers wish to stay at the venue
    double durationStay;
    // The size of the car
    carSize size;
    // The types of passengers e.g. family with children or elderly
    passengerType passenger;
    // The role of the passengers at the venue
    roleVenue role;
} car;

typedef struct lot {
    //Whether the cell is Free, Reserved, Path, Entrance or Exit
    LotStatus status;

    //Whether spot is for handicap 0 for no, 1 for yes
    int isHandicapSpot;
    // double for hours of max duration to stay on specific spot
    double maxDuration;
    //The carsize which the spot is made for
    carSize maxSize;
    //The preffered type of passenger the spot is made for e.g. elderly or families with children
    passengerType preferredPassenger;
    //The role which the spot is made for e.g. VIP, guest or worker
    roleVenue allowedRole;

    // Length and width of the spot, not used in logical model
    double spotWidth;
    double spotLength;

    // If there is a car in the spot 0 if no 1 if yes
    int hasCar;
    // The car that is in the spot if hasCar is 1
    car currentCar;

    //Positions in grid and distance to entrance
    int distance;
    int row;
    int col;
} lot;

//prototypes from arrays.c
lot **ArrayAlloc(int length, int width);

lot **ArrayFill(lot **pointer, int length, int width);

void ArrayFree(lot **pointer, int length);

void ArrayPrint(lot **pointer, int length, int width);


//void ArrayFree(lot** pointer, int length, int width);
void ArrangeCar(lot **parkingLot, car Car, int x0, int y0);

//prototypes from menu.c
void create_menu();
void add_cars(lot **parkingLot, int length, int width);

//prototypes from save.c
void auto_save(lot **pointer, int length, int width);

lot **load_save(FILE *savefile, int *length, int *width);

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
