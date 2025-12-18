//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_MAP_TO_LOT_H
#define P1_GRUPPE4_MAP_TO_LOT_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/**
 * @brief Check if spot is handicap or not
 *
*  @param lot A parking spot in the parking lot
 * @param car_hand Pointer to the number of rows in the parking lot.
 *
 * @return 1 if handicap 0 if not
 */
int is_handicap(lot lot, int car_hand);

/**
 * @brief Check if spot matches the size of the car
 *
*  @param lot A parking spot in the parking lot
 * @param size The size of the car
 *
 * @return 1 if size of car and spot match, else 0
 */
int is_type(lot lot, car_size size);

/**
 * @brief Check if spots role matches car role
 *
*  @param lot A parking spot in the parking lot
 * @param role The role of the car
 *
 * @return 1 if role of car and usercar match, else 0
 */
int is_role(lot lot, role_venue role);

/**
 * @brief Check if spots role matches car role
 *
 * @param car_user The car of the user of type car
 * @param p_lot The parking lot two dimensional array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 * @param matches Pointer to amount of spots that match users car
 *
 * @return Array of spots that fit user car
 */
lot *filter_spots(car car_user, lot **p_lot, int length, int width, int *matches);

/**
 * @brief Gives a score bassed of how well the duration capability of the spot fits with the needs of the car
 *
*  @param l A parking spot in the parking lot
 * @param c The car of the user
 *
 * @return A score from 0-1
 */
double duration_score(lot l, car c);

/**
 * @brief  Gives a score based of how well the passenger capability of the spot fits with the needs of the cars passenger
 *
*  @param l A parking spot in the parking lot
 * @param c The car of the user
 *
 * @return A score from 0-1
 */
double passenger_score(lot l, car c);

/**
 * @brief Calculates a score from 0-100 based on passengerscore and durationscore
 *
*  @param l A parking spot in the parking lot
 * @param c The car of the user
 *
 * @return A score from 0-100
 */
double calc_score(double passenger_score, double duration_score);

/**
 * @brief Maps the car of the user to the parking spot in the parking lot that has the highest score
 *
 * @param car_user The car of the user of type car
 * @param p_lot The parking lot two dimensional array
 * @param length Number of rows in the parking lot.
 * @param width  Number of columns in the parking lot.
 */
void map_to_lot(car car_user, lot **p_lot, int length, int width);

#endif //P1_GRUPPE4_MAP_TO_LOT_H
