#include "find.h"


//Function for finding a car in the parkinglot based on numberplate
int find_car_by_numberplate(lot **parking_lot, int length, int width, char *number_plate, int *loc_row, int *loc_col) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            //Checks for each lot in parking lot, if it has car and if strcmpr of it's numberplate and one we wish to find equals 0
            if (parking_lot[i][j].has_car == 1 && strcmp(parking_lot[i][j].current_car.number_plate, number_plate) == 0) {
                //if both conditions are met, the numberplate is found, and loc_row and loc_col are set to i and j respectively
                *loc_row = i;
                *loc_col = j;
                return 1;
            }
        }
    }
    return 0;
}