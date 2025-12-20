//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_MENU_H
#define P1_GRUPPE4_MENU_H

#include <stdio.h>
#include <ctype.h>
#include "types.h"
#include "save.h"
#include "arrays.h"
#include "parking_lot.h"
#include "map_to_lot.h"
#include "delete.h"
#include "find.h"
#include "occupancy.h"

/**
 * @brief Continously shows user the main options (creating new lot, loading existing ect..) until user leaves app
 */
void main_menu();

/**
 * @brief Continously shows user the options they can do to their parking lot after loading/creating a new one, until they leave app
*
*  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 */
void lot_menu(lot **parking_lot, int length, int width) ;


/**
 * @brief Continously asks user whether they want to add a new car until user types 'n', calls add_cars and map_to_lot to add them
*
*  @param parking_lot Pointer to the allocated parkinglot array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 */
void add_cars(lot **parking_lot, int length, int width);

/**
 * @brief creates a new car, and is called by add_cars
*
*  @return the new car
 */
car create_car();

#endif //P1_GRUPPE4_MENU_H