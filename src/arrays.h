//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_ARRAYS_H
#define P1_GRUPPE4_ARRAYS_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"


/**
 * @brief Allocates a parking lot as a dynamically allocated 2D array.
 *
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 *
 * @return Pointer to the array on success,
 *         or NULL if memory allocation fails.
 */
lot **array_alloc(int length, int width);

/**
 * @brief Fills the dynamically allocated parking lot 2D array with some standard values.
 *
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 * @param pointer The parking lot 2D array
 *
 *
 */
void **array_fill(lot **pointer, int length, int width);

//Function array_free with void return type that takes the parkinglot as an argument and the length of the array,
//the function frees the dynamically allocated array
/**
 * @brief Frees the dynamically allocated parking lot 2D array.
 *
 * @param length Number of rows in the parking lot.
 * @param pointer The parking lot 2D array
 *
 *
 */
void array_free(lot **pointer, int length);


/**
 * @brief Prints the dynamically allocated parking lot 2D array.
 *
*  @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 * @param pointer The parking lot 2D array
 *
 *
 */
void array_print(lot **pointer, int length, int width);

#endif //P1_GRUPPE4_ARRAYS_H