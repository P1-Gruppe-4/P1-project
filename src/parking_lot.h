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


int comp(const void *a, const void *b);
void sort_park(lot parking_arr[], int last, int (*fptr)(const void *, const void *));
lot **lot_assigner(lot **parking_lot, int length, int width);
lot **path_creator(lot **parking_lot, int length, int width);


#endif //P1_GRUPPE4_PARKING_LOT_H