#include "delete.h"

//Function for deleting a car in the parkinglot based on numberplate
int delete_car(lot **parking_lot, int length, int width, char *number_plate) {
    int row, col;
    //calls find_car_by_numberplate to see if the car we wanna find exist, and saves in result
    int result = find_car_by_numberplate(parking_lot, length, width, number_plate, &row, &col);

    //if it exists, has car in that lot is now set to 0 and Status is set to Status_Free
    if (result == 1) {
        parking_lot[row][col].has_car = 0;
        parking_lot[row][col].status = Status_Free;
        return 1;
        //Else the car was not in the lot in the first place
    } else return 0;
}
