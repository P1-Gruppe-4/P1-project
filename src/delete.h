//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_DELETE_H
#define P1_GRUPPE4_DELETE_H

#include "types.h"
#include "find.h"

/**
 * @brief Deletes a car in the parkinglot based on it's numberplate, and returns whether it was deleted or not
 *
 *  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 * @param number_plate Array of char (string) that contains car plate number
 *
 * @return 1 if numberplate is deleted, 0 if it is not
 */
int delete_car(lot **parking_lot, int length, int width, char *number_plate);


#endif //P1_GRUPPE4_DELETE_H