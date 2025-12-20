//
// Created by matei on 20/12/2025.
//

#ifndef P1_GRUPPE4_OCCUPANCY_H
#define P1_GRUPPE4_OCCUPANCY_H

#include "types.h"

/**
 * @brief Calculates how big a percentage of the lot is free
 *
 *  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.s
 *
 * @return percentage of lot that is free
 */
double occupancy_lot(lot **parking_lot, int length, int width);

#endif //P1_GRUPPE4_OCCUPANCY_H