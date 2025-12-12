#include <stdio.h>
#include "main.h"
#include <stdlib.h>

#define HANDICAP_RATIO 0.08   // 8% handicap-pladser
#define FAMILY_RATIO   0.10   // 10% pladser til familier (børn)
#define ELDERLY_RATIO  0.07   // 7% pladser til ældre

#define SHORT_STAY_HOURS  1.0
#define MEDIUM_STAY_HOURS 4.0
#define LONG_STAY_HOURS   8.0

#define VIP_SPOTS 0.03
#define WORKER_SPOTS 0.02


//prints the paths of the parking lot layout
lot **pathCreator(lot **parkingLot, int length, int width) {
    //for loop demon right here
    for (int i = 0; i < length; i++) {
        //i & j loops tru whole parking lot
        for (int j = 0; j < width; j++) {
            //Initializing all spots as 0 and then just overrwriting the necessarry ones
            parkingLot[i][j].status = Status_Free;
            if (i % 3 == 0) {
                parkingLot[i][j].status = Status_Path;
            }
            if (j == width - 1) {
                if (i != 0 && i != length - 1) {
                    parkingLot[i][j].status = Status_Path;
                } else if (i == 0) {
                    parkingLot[i][j].status = Status_Entrance; // status for entrance
                } else if (i == length - 1) {
                    parkingLot[i][j].status = Status_Exit; // status for exit
                }
            }
            parkingLot[i][j].hasCar = 0;
            parkingLot[i][j].spotWidth = 1.0;
            parkingLot[i][j].spotLength = 1.0;
        }
    }
    return parkingLot;
}

//Denne funktion gennemgår parkeringpladsen og sætter nogle af de forskellige
//variabler

lot **lotAssigner(lot **parkingLot, int length, int width) {
    int totalSpotsFree = 0;
    int entRow = 0;
    int entCol = width - 2; // middle of entry

    for (int i = 0; i < length; i++) {
        //i & j loops tru whole parking lot
        for (int j = 0; j < width; j++) {
            if (parkingLot[i][j].status == Status_Free) {
                parkingLot[i][j].row = i;
                parkingLot[i][j].col = j;
                parkingLot[i][j].distance = abs(entRow - i) + abs(entCol - j);
                totalSpotsFree++;
            }
        }
    }

    int handicapSpots = HANDICAP_RATIO * totalSpotsFree;
    int familySpots = FAMILY_RATIO * totalSpotsFree;
    int elderlySpots = ELDERLY_RATIO * totalSpotsFree;
    int vipSpots = VIP_SPOTS * totalSpotsFree;
    int workerSpots = WORKER_SPOTS * totalSpotsFree;

    lot *lotTemp = malloc(sizeof(lot) * totalSpotsFree);
    if (lotTemp == NULL) {
        // kunne evt. printe fejl eller bare returnere parkingLot
        return parkingLot;
    }
    int k = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parkingLot[i][j].status == Status_Free) {
                lotTemp[k] = parkingLot[i][j];
                k++;
            }
        }
    }

    int (*fptr)(const void *, const void *);
    fptr = &comp;
    sortPark(lotTemp, totalSpotsFree, fptr);

    double durationOptions[3] = {
        SHORT_STAY_HOURS, // index 0
        MEDIUM_STAY_HOURS, // index 1
        LONG_STAY_HOURS // index 2
    };

    carSize sizeOptions[4] = {
        Small, // 0
        Medium, // 1
        Large, // 2
        Special // 3
    };

    int parking_row_index[length];
    int parking_row = 0;
    for (int i = 0; i < length; i++) {
        if (i%3 != 0) {
            parking_row_index[i] = parking_row;
            parking_row++;
        } else {
            parking_row_index[i] = -1;
        }
    }

    for (int i = 0; i < totalSpotsFree; i++) {
        lotTemp[i].isHandicapSpot = 0;
        lotTemp[i].allowedRole = Guest;
        lotTemp[i].preferredPassenger = Adult;
        lotTemp[i].maxDuration = durationOptions[i % 3];
        int r = lotTemp[i].row; //Row which i is on
        int index = parking_row_index[r];
        lotTemp[i].maxSize = sizeOptions[index % 4]; // One row of each size
        if (i < handicapSpots) {
            lotTemp[i].isHandicapSpot = 1;
        } else if (i < handicapSpots + vipSpots) {
            lotTemp[i].allowedRole = VIP;
        } else if (i < handicapSpots + elderlySpots + vipSpots) {
            lotTemp[i].preferredPassenger = Elderly;
        } else if (i < handicapSpots + familySpots + vipSpots + elderlySpots) {
            lotTemp[i].preferredPassenger = Family;
        } else if (i < handicapSpots + familySpots + vipSpots + elderlySpots + workerSpots) {
            lotTemp[i].allowedRole = Worker;
            lotTemp[i].maxDuration = LONG_STAY_HOURS;
        }
    }

    for (int i = 0; i < totalSpotsFree; i++) {
        parkingLot[lotTemp[i].row][lotTemp[i].col] = lotTemp[i];
    }

    free(lotTemp);
    return parkingLot;
}

//Sammenlignings funktion som modtager to void pointere som argument
int comp(const void *a, const void *b) {
    const lot *A = a, *B = b;
    if (A->distance == B->distance) {
        return 0;
    } else if (A->distance > B->distance) {
        return 1;
    } else {
        return -1;
    }
}

//funktion sortPark som kalder qsort
void sortPark(lot parkingArr[], int last, int (*fptr)(const void *, const void *)) {
    //qsort kaldes med array af parkingspladser, antallet af elementer samt en funktionspuntioner til sammenligningsfunktionen
    qsort(parkingArr, last, sizeof(lot), fptr);
}
