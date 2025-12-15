#include <parking_lot.h>



//prints the paths of the parking lot layout
lot **path_creator(lot **parking_lot, int length, int width) {
    //for loop demon right here
    for (int i = 0; i < length; i++) {
        //i & j loops tru whole parking lot
        for (int j = 0; j < width; j++) {
            //Initializing all spots as 0 and then just overrwriting the necessarry ones
            parking_lot[i][j].status = Status_Free;
            if (i % 3 == 0) {
                parking_lot[i][j].status = Status_Path;
            }
            if (j == width - 1) {
                if (i != 0 && i != length - 1) {
                    parking_lot[i][j].status = Status_Path;
                } else if (i == 0) {
                    parking_lot[i][j].status = Status_Entrance; // status for entrance
                } else if (i == length - 1) {
                    parking_lot[i][j].status = Status_Exit; // status for exit
                }
            }
            parking_lot[i][j].has_car = 0;
            parking_lot[i][j].spot_width = 1.0;
            parking_lot[i][j].spot_length = 1.0;
        }
    }
    return parking_lot;
}

//Denne funktion gennemgår parkeringpladsen og sætter nogle af de forskellige
//variabler

lot **lot_assigner(lot **parking_lot, int length, int width) {
    int total_spots_free = 0;
    int ent_row = 0;
    int ent_col = width - 2; // middle of entry

    for (int i = 0; i < length; i++) {
        //i & j loops tru whole parking lot
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free) {
                parking_lot[i][j].row = i;
                parking_lot[i][j].col = j;
                parking_lot[i][j].distance = abs(ent_row - i) + abs(ent_col - j);
                total_spots_free++;
            }
        }
    }

    int handicap_spots = HANDICAP_RATIO * total_spots_free;
    int family_spots = FAMILY_RATIO * total_spots_free;
    int elderly_spots = ELDERLY_RATIO * total_spots_free;
    int vip_spots = VIP_SPOTS * total_spots_free;
    int worker_spots = WORKER_SPOTS * total_spots_free;

    lot *lot_temp = malloc(sizeof(lot) * total_spots_free);
    if (lot_temp == NULL) {
        // kunne evt. printe fejl eller bare returnere parking_lot
        return parking_lot;
    }
    int k = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free) {
                lot_temp[k] = parking_lot[i][j];
                k++;
            }
        }
    }

    int (*fptr)(const void *, const void *);
    fptr = &comp;
    sort_park(lot_temp, total_spots_free, fptr);

    double duration_options[3] = {
        SHORT_STAY_HOURS, // index 0
        MEDIUM_STAY_HOURS, // index 1
        LONG_STAY_HOURS // index 2
    };

    car_size size_options[4] = {
        Small, // 0
        Medium, // 1
        Large, // 2
        Special // 3
    };

    int parking_row_index[length];
    int parking_row = 0;
    for (int i = 0; i < length; i++) {
        if (i%3 != 0) {
            parking_row_index[i] = parking_row;
            parking_row++;
        } else {
            parking_row_index[i] = -1;
        }
    }

    for (int i = 0; i < total_spots_free; i++) {
        lot_temp[i].is_handicap_spot = 0;
        lot_temp[i].allowed_role = Guest;
        lot_temp[i].preferred_passenger = Adult;
        lot_temp[i].max_duration = duration_options[i % 3];
        int r = lot_temp[i].row; //Row which i is on
        int index = parking_row_index[r];
        lot_temp[i].max_size = size_options[index % 4]; // One row of each size
        if (i < handicap_spots) {
            lot_temp[i].is_handicap_spot = 1;
        } else if (i < handicap_spots + vip_spots) {
            lot_temp[i].allowed_role = VIP;
        } else if (i < handicap_spots + elderly_spots + vip_spots) {
            lot_temp[i].preferred_passenger = Elderly;
        } else if (i < handicap_spots + family_spots + vip_spots + elderly_spots) {
            lot_temp[i].preferred_passenger = Family;
        } else if (i < handicap_spots + family_spots + vip_spots + elderly_spots + worker_spots) {
            lot_temp[i].allowed_role = Worker;
            lot_temp[i].max_duration = LONG_STAY_HOURS;
        }
    }

    for (int i = 0; i < total_spots_free; i++) {
        parking_lot[lot_temp[i].row][lot_temp[i].col] = lot_temp[i];
    }

    free(lot_temp);
    return parking_lot;
}

//Sammenlignings funktion som modtager to void pointere som argument
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

//funktion sort_park som kalder qsort
void sort_park(lot parking_arr[], int last, int (*fptr)(const void *, const void *)) {
    //qsort kaldes med array af parkingspladser, antallet af elementer samt en funktionspuntioner til sammenligningsfunktionen
    qsort(parking_arr, last, sizeof(lot), fptr);
}
