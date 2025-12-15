//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_MAP_TO_LOT_H
#define P1_GRUPPE4_MAP_TO_LOT_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"


int is_handicap(lot lot, int car_hand);
int is_type(lot lot, car_size size);
int is_role(lot lot, role_venue role);

lot *filter_spots(car car_user, lot **p_lot, int length, int width, int *matches);

double duration_score(lot *l, car c);
double passenger_score(lot *l, car c);
double calc_score(double passengerScore, double durationScore);

void map_to_lot(car car_user, lot **p_lot, int length, int width);

#endif //P1_GRUPPE4_MAP_TO_LOT_H