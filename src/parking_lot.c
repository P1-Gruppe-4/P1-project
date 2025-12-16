#include "parking_lot.h"


//prints the paths of the parking lot layout
lot **path_creator(lot **parking_lot, int length, int width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            //Initializing all spots as 0 and then just overrwriting the necessarry ones
            parking_lot[i][j].status = Status_Free;
            //Every third lot row is a row of paths
            if (i % 3 == 0) {
                parking_lot[i][j].status = Status_Path;
            }
            // The last column is a path, the top right corner is entrance and bottom right is exit
            if (j == width - 1) {
                if (i != 0 && i != length - 1) {
                    parking_lot[i][j].status = Status_Path;
                } else if (i == 0) {
                    parking_lot[i][j].status = Status_Entrance; // status for entrance
                } else if (i == length - 1) {
                    parking_lot[i][j].status = Status_Exit; // status for exit
                }
            }
            //Every spot is initialized with a width and length of 1 and does not have a car
            parking_lot[i][j].has_car = 0;
            parking_lot[i][j].spot_width = 1.0;
            parking_lot[i][j].spot_length = 1.0;
        }
    }
    //parking lot is returned
    return parking_lot;
}

// Function that assigns the parkinglot
lot **lot_assigner(lot **parking_lot, int length, int width) {
    //Initialize variables for total free spots, and the coordinates of the entrance
    int total_spots_free = 0;
    int ent_row = 0;
    int ent_col = width - 1;

    //i & j loops tru whole parking lot
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            //If the lot is free
            if (parking_lot[i][j].status == Status_Free) {
                //The row of the lot is i and col is j
                parking_lot[i][j].row = i;
                parking_lot[i][j].col = j;
                //The distance of the lot to the entrance is calculated via Manhattan and saved
                parking_lot[i][j].distance = abs(ent_row - i) + abs(ent_col - j);
                //Total spots free grows by 1
                total_spots_free++;
            }
        }
    }

    //Calculates how many of the different types of spots is need based on the defined ratios from parking_lot.h
    int handicap_spots = HANDICAP_RATIO * total_spots_free;
    int family_spots = FAMILY_RATIO * total_spots_free;
    int elderly_spots = ELDERLY_RATIO * total_spots_free;
    int vip_spots = VIP_SPOTS * total_spots_free;
    int worker_spots = WORKER_SPOTS * total_spots_free;

    //Allocate a temporary array of lots dynamically, using the amount of free spots
    lot *lot_temp = malloc(sizeof(lot) * total_spots_free);
    //If the array is NULL, return the parking_lot
    if (lot_temp == NULL) {
        return parking_lot;
    }
    //Loops through the whole parkinglot and puts all the free spots in the dynamically allocated array
    int k = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free) {
                lot_temp[k] = parking_lot[i][j];
                k++;
            }
        }
    }

    //sort_park is called with a function pointer to the comparison function
    int (*fptr)(const void *, const void *);
    fptr = &comp;
    sort_park(lot_temp, total_spots_free, fptr);

    //array of the 3 different types of duration stays from the corresponding ENUM
    double duration_options[3] = {
        SHORT_STAY_HOURS, // index 0
        MEDIUM_STAY_HOURS, // index 1
        LONG_STAY_HOURS // index 2
    };

    //array of the 3 different types of carsizes from the corresponding ENUM
    car_size size_options[3] = {
        Small, // 0
        Medium, // 1
        Large // 2
    };

    //adds all the parking_rows that actually are for parking to parking_row_index array, meaning that 0, 3 etc are paths.
    int parking_row_index[length];
    int parking_row = 0;
    for (int i = 0; i < length; i++) {
        if (i % 3 != 0) {
            parking_row_index[i] = parking_row;
            parking_row++;
        } else {
            parking_row_index[i] = -1;
        }
    }

    //Loops through all free spots
    for (int i = 0; i < total_spots_free; i++) {
        //Sets their base case handicap to 0, role to Guest, Passenger to Adult and duration to i%3 of duration options, so it loops back and forth between the 3
        lot_temp[i].is_handicap_spot = 0;
        lot_temp[i].allowed_role = Guest;
        lot_temp[i].preferred_passenger = Adult;
        lot_temp[i].max_duration = duration_options[i % 3];
        int r = lot_temp[i].row; //Row which i is on
        int index = parking_row_index[r]; // Index of the row
        lot_temp[i].max_size = size_options[index % 3]; // One row of each size
        //Checks if i is smaller than amount of handicap spots, as they are highest priority and closest to entrance
        if (i < handicap_spots) {
            //sets these spots handicap to 1
            lot_temp[i].is_handicap_spot = 1;
            //Then checks for vip_spots and sets role to VIP
        } else if (i < handicap_spots + vip_spots) {
            lot_temp[i].allowed_role = VIP;
            //Then checks for elderly and sets passenger to Elderly
        } else if (i < handicap_spots + elderly_spots + vip_spots) {
            lot_temp[i].preferred_passenger = Elderly;
            //Then checks for family and sets passenger to family
        } else if (i < handicap_spots + family_spots + vip_spots + elderly_spots) {
            lot_temp[i].preferred_passenger = Family;
            //Then checks for worker and sets role to worker and max duration to long, as worker spots have long hours
        } else if (i < handicap_spots + family_spots + vip_spots + elderly_spots + worker_spots) {
            lot_temp[i].allowed_role = Worker;
            lot_temp[i].max_duration = LONG_STAY_HOURS;
        }
    }

    // Loop all the spots from the total_spots_free array back to the parkinglot
    for (int i = 0; i < total_spots_free; i++) {
        parking_lot[lot_temp[i].row][lot_temp[i].col] = lot_temp[i];
    }

    //free lot_temp and return the parking lot
    free(lot_temp);
    return parking_lot;
}

// Comparison function with return type int that takes to void pointers as arguments
int comp(const void *a, const void *b) {
    const lot *A = a, *B = b;
    if (A->distance == B->distance) {
        return 0;
    } else if (A->distance > B->distance) {
        return 1;
    } else {
        return -1;
    }
}

//Function sort_park which calls qsort
void sort_park(lot parking_arr[], int last, int (*fptr)(const void *, const void *)) {
    //qsort is called with an array of parking spot, the number of elements, size of elements and function pointer to comparison function
    qsort(parking_arr, last, sizeof(lot), fptr);
}
