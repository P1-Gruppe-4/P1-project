//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_PARKING_LOT_H
#define P1_GRUPPE4_PARKING_LOT_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"


#define HANDICAP_RATIO 0.08   // 8% handicap-pladser
#define FAMILY_RATIO   0.10   // 10% pladser til familier (børn)
#define ELDERLY_RATIO  0.07   // 7% pladser til ældre

#define SHORT_STAY_HOURS  1.0
#define MEDIUM_STAY_HOURS 4.0
#define LONG_STAY_HOURS   8.0

#define VIP_SPOTS 0.03
#define WORKER_SPOTS 0.02


/**
 * @brief Comparison function used in QSort, returns whether an items is bigger than next, equal or smaller
 * @brief In the code it compares based on distance to the entrance for each parking spot
 *
 * @param a Void pointer
 * @param b Void pointer
 *
 * @return 0 if they are equal, 1 if a>b and -1 if b>a
 */
int comp(const void *a, const void *b);

/**
 * @brief Sort function that uses QSort and is used to sort array of free parking spots based on distance to entrance
 *
 * @param parking_arr One dimensional array of parking spots that are empty
 * @param last Amount of elements in the array
 * @param fptr Function fptr to the comp function
 *
 */
void sort_park(lot parking_arr[], int last, int (*fptr)(const void *, const void *));

/**
 * @brief Assigns all the parking spots sizes, whether they are for handicapped, duration and other info..
 *
 *  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 *
 * @return The parking lot with assigned values for size ect..
 */
lot **lot_assigner(lot **parking_lot, int length, int width);

/**
 * @brief Creates the parkinglot by making some lots paths, some parkingspots and entrance/exit.
 *
 *  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 *
 * @return The parking lot with designated spots, paths ect.
 */
lot **path_creator(lot **parking_lot, int length, int width);


#endif //P1_GRUPPE4_PARKING_LOT_H
