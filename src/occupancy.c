//
// Created by matei on 20/12/2025.
//

#include "occupancy.h"

double occupancy_lot(lot **parking_lot, int length, int width) {
    // variables for amount of free spots and amount of total spots
    double spots_free = 0;
    double spots_total = 0;
    //loop through parking lot to count amount of free and total spots
    for (int i = 0; i<length; i++) {
        for (int j = 0; j<width;j++) {
            if (parking_lot[i][j].status == Status_Free || parking_lot[i][j].status == Status_Reserved) {
                spots_total++;
            }
            if (parking_lot[i][j].status == Status_Free) {
            spots_free++;
            }
        }
    }
    // return percentage of all spots that is free
    return (spots_free/spots_total)*100;
}