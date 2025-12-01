//
// Created by john on 21/11/2025.
//

#ifndef P1_GRUPPE4_MAIN_H
#define P1_GRUPPE4_MAIN_H

//necessary headerfiles
#include <stddef.h>
#include <stdio.h>
#endif //P1_GRUPPE4_MAIN_H

//structs for project

typedef struct lot{
    int status; //0 for free, 1 for occupied
    int handicap; //0 for no, 1 for yes
} lot;

typedef struct tempLot{
  int sizeClass; //skal måske være en struct for sig selv?
  double stayDuration;
  int handicap; // 0=no, 1=yes
  int passengers; //children or elderly so just a bool
  //int staff; //also bool
}tLot;

typedef struct car
{
    //de først tre er temp
    int doorLength;
    int length;
    int width;

    int sizeClass; //skal måske være en struct for sig selv?
    double stayDuration;
    int handicap; // 0=no, 1=yes
    int passengers; //either childre or elderly so really just a bool
    //int staff; //also bool

} car;

//prototypes from arrays.c
lot** ArrayAlloc(int length, int width);
lot** ArrayFill(lot** pointer, int length, int width);
void ArrayPrint(lot** pointer, int length, int width);
//void ArrayFree(lot** pointer, int length, int width);
void ArrangeCar(lot** parkingLot, car Car, int x0, int y0);

//prototypes from menu.c
void create_menu();
void ArrangeCar(lot** parkingLot, car Car, int x0, int y0);

//prototypes from save.c
void auto_save (lot** pointer, int length, int width);
lot** load_save(FILE* savefile);
//prototypes from optimizer.c
tLot** scoreAssigner(tLot** parkingLot);
void usrInput();
void scoreCalculator();
void spaceAllocater();

//prototypes for parkingLot.c (mby temp fil idk)
lot** carFill(lot** pointer, int length, int width);
lot** pathCreate(lot** pointer, int length, int width);
void ArrayPrint(lot** pointer, int length, int width);

