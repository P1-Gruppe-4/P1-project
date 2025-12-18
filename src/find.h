//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_FIND_H
#define P1_GRUPPE4_FIND_H

#include <string.h>
#include "types.h"

/**
 * @brief Finds a car in the parkinglot based on it's numberplate, and returns whether it is in the parkinglot and the row and col where it is
 *
 *  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 * @param number_plate Array of char (string) that contains car plate number
 * @param loc_row  Row where number_plate is located
 * @param loc_col Column where number_plate is located
 *
 * @return 1 if numberplate is found, 0 if it is not
 */
int find_car_by_numberplate(lot **parking_lot, int length, int width, char *number_plate, int *loc_row, int *loc_col);

#endif //P1_GRUPPE4_FIND_H