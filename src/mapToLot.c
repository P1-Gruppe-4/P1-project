#include "main.h"
#include <stdlib.h>
#include <math.h>

//Function to check if car and parkingspot match on handicap parameter
int isHandicap(lot lot, int carHand) {
    if (lot.isHandicapSpot == carHand) {
        return 1;
    } else {
        return 0;
    }
}

//Function to check if car and parkingspot match on carType parameter
int isType(lot lot, carSize size) {
    if (lot.maxSize == size) {
        return 1;
    } else {
        return 0;
    }
}

//Function to check if car and parkingspot match on role parameter
int isRole(lot lot, roleVenue role) {
    if (lot.allowedRole == role) {
        return 1;
    } else {
        return 0;
    }
}

//Function to filter away all the spots that do not match the car on the parameters role, handicap and type, and to return a dynamic array with ones that fit
lot *filterSpots(car carUser, lot **parking_lot, int length, int width, int *matches) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free && parking_lot[i][j].hasCar == 0) {
                if (isHandicap(parking_lot[i][j], carUser.handicap) == 1 && isType(parking_lot[i][j], carUser.size) == 1
                    && isRole(
                        parking_lot[i][j], carUser.role) == 1) {
                    count++;
                }
            }
        }
    }
    if (count == 0) {
        *matches = 0;
        return NULL;
    }
    lot *result = malloc(sizeof(lot) * count);
    if (result == NULL) {
        // malloc fails
        *matches = 0; // if malloc fails then there are no matches to work with
        return NULL;
    }
    int count2 = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free && parking_lot[i][j].hasCar == 0) {
                if (isHandicap(parking_lot[i][j], carUser.handicap) == 1 && isType(parking_lot[i][j], carUser.size) == 1
                    && isRole(
                        parking_lot[i][j], carUser.role) == 1) {
                    result[count2] = parking_lot[i][j];
                    count2++;
                }
            }
        }
    }
    *matches = count;
    return result;
}

//Function to calculate a durations score based on the duration time of the parking space and the car
double durationScore(lot *l, car c) {
    //if the car needs to be parked longer than the space allows, return 0
    if (c.durationStay > l->maxDuration) {
        return 0;
    }

    double difference = l->maxDuration - c.durationStay;
    double maxDiff = 4;
    //you don't want the difference in the parking space and the car's time is over 4 hours, it's too much waste.

    if (difference > maxDiff) {
        return 0; //hvis det over 4 timer så return 0
    } else {
        return 1 - (difference / maxDiff);
        //Returns a value based on how big the difference is between difference and maxDiff
    }
}

//Function to return a passengerscore, based on how well the parkingspot matches the car
double passengerScore(lot *l, car c) {
    int val = c.passenger - l->preferredPassenger;
    if (val == 0) {
        return 1.0;
    } else if (val == 1 || val == -1) {
        return 0.5;
    } else {
        return 0.0;
    }
}

//Function to calculate the score the spot gets
double calcScore(double passengerScore, double durationScore) {
    return 50 * passengerScore + 50 * durationScore;
}

//Function that maps car to the parking spot that fits it best, and sets it as taken by the specific car
void mapToLot(car carUser, lot **parking_lot, int length, int width) {
    int matches = 0;
    double matchScore = 0;
    double maxMatchScore = -1;
    double dScore;
    double pScore;
    int matchL = 0;
    int matchW = 0;

    lot *matchLot = filterSpots(carUser, parking_lot, length, width, &matches);
    //Stops function if no matches or matchLot is empty
    if (matches == 0 || matchLot == NULL) {
        printf("No parking space matches your car\n");
        free(matchLot);
        return;
    }


    for (int i = 0; i < matches; i++) {
        dScore = durationScore(&matchLot[i], carUser);
        pScore = passengerScore(&matchLot[i], carUser);
        matchScore = calcScore(pScore, dScore);
        if (matchScore > maxMatchScore) {
            maxMatchScore = matchScore;
            matchL = matchLot[i].row;
            matchW = matchLot[i].col;
        }
    }
    parking_lot[matchL][matchW].row = matchL;
    parking_lot[matchL][matchW].col = matchW;
    parking_lot[matchL][matchW].currentCar = carUser;
    parking_lot[matchL][matchW].hasCar = 1;
    parking_lot[matchL][matchW].status = Status_Reserved;

    free(matchLot);
}
