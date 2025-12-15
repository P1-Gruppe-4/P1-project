#include <delete.h>

//Function for deleting a car in the parkinglot based on numberplate
int delete_car(lot **parking_lot, int length, int width, char *number_plate) {
    int row, col;
    int result = find_car_by_numberplate(parking_lot, length, width, number_plate, &row, &col);

    if (result == 1) {
        parking_lot[row][col].has_car = 0;
        parking_lot[row][col].status = Status_Free;
        return 1;
    } else return 0;
}
