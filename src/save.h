//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_SAVE_H
#define P1_GRUPPE4_SAVE_H

#include <stdio.h>
#include "types.h"

/**
 * @brief Saves parkinglot by writing info about each parkingspot in the parkinglot to autosave.txt
 *
*  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 */
void auto_save(lot **pointer, int length, int width);

/**
 * @brief Loads parkinglot by reading info about each parkingspot in the parkinglot from autosave.txt or other file
 *
*  @param save_file Pointer to the file the parkinglot is saved in
 * @param length Pointer to the number of rows in the parking lot.
 * @param width  Pointer to the number of columns in the parking lot.
 *
 * @return The loaded parking lot
 */
lot **load_save(FILE *save_file, int *length, int *width);

#endif //P1_GRUPPE4_SAVE_H