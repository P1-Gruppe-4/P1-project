#include "map_to_lot.h"


//Function to check if car and parkingspot match on handicap parameter
int is_handicap(lot lot, int car_hand) {
    if (lot.is_handicap_spot == car_hand) {
        return 1;
    } else {
        return 0;
    }
}

//Function to check if car and parkingspot match on carType parameter
int is_type(lot lot, car_size size) {
    if (lot.max_size == size) {
        return 1;
    } else {
        return 0;
    }
}

//Function to check if car and parkingspot match on role parameter
int is_role(lot lot, role_venue role) {
    if (lot.allowed_role == role) {
        return 1;
    } else {
        return 0;
    }
}

//Function to filter away all the spots that do not match the car on the parameters role, handicap and type, and to return a dynamic array with ones that fit
lot *filter_spots(car car_user, lot **parking_lot, int length, int width, int *matches) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free && parking_lot[i][j].has_car == 0) {
                if (is_handicap(parking_lot[i][j], car_user.handicap) == 1 && is_type(parking_lot[i][j], car_user.size) == 1
                    && is_role(
                        parking_lot[i][j], car_user.role) == 1) {
                    count++;
                }
            }
        }
    }
    if (count == 0) {
        *matches = 0;
        return NULL;
    }
    lot *result = malloc(sizeof(lot) * count);
    if (result == NULL) {
        // malloc fails
        *matches = 0; // if malloc fails then there are no matches to work with
        return NULL;
    }
    int count2 = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (parking_lot[i][j].status == Status_Free && parking_lot[i][j].has_car == 0) {
                if (is_handicap(parking_lot[i][j], car_user.handicap) == 1 && is_type(parking_lot[i][j], car_user.size) == 1
                    && is_role(
                        parking_lot[i][j], car_user.role) == 1) {
                    result[count2] = parking_lot[i][j];
                    count2++;
                }
            }
        }
    }
    *matches = count;
    return result;
}

//Function to calculate a durations score based on the duration time of the parking space and the car
double duration_score(lot *l, car c) {
    //if the car needs to be parked longer than the space allows, return 0
    if (c.duration_stay > l->max_duration) {
        return 0;
    }
    double difference = l->max_duration - c.duration_stay;
    double max_diff = 4;
    //you don't want the difference in the parking space and the car's time is over 4 hours, it's too much waste.

    if (difference > max_diff) {
        return 0; //If difference is bigger than 4, return 0
    } else {
        return 1 - (difference / max_diff);
        //Returns a value based on how big the difference is between difference and max_diff
    }
}

//Function to return a passengerscore, based on how well the parkingspot matches the car
double passenger_score(lot *l, car c) {
    int val = c.passenger - l->preferred_passenger;
    if (val == 0) {
        return 1.0;
    } else if (val == 1 || val == -1) {
        return 0.5;
    } else {
        return 0.0;
    }
}

//Function to calculate the score the spot gets
double calc_score(double passenger_score, double duration_score) {
    return 50 * passenger_score + 50 * duration_score;
}

//Function that maps car to the parking spot that fits it best, and sets it as taken by the specific car
void map_to_lot(car car_user, lot **parking_lot, int length, int width) {
    int matches = 0;
    double match_score = 0;
    double max_match_score = -1;
    double d_score;
    double p_score;
    int match_l = 0;
    int match_w = 0;

    lot *match_lot = filter_spots(car_user, parking_lot, length, width, &matches);
    //Stops function if no matches or match_lot is empty
    if (matches == 0 || match_lot == NULL) {
        printf("No parking space matches your car\n");
        //Frees match_lot
        free(match_lot);
        return;
    }

    //loops through all the matches
    for (int i = 0; i < matches; i++) {
        // durations and passengerscore are calculated for each match
        d_score = duration_score(&match_lot[i], car_user);
        p_score = passenger_score(&match_lot[i], car_user);
        //match score is calculated for each match
        match_score = calc_score(p_score, d_score);
        //if match_score is bigger than max_match_score, match_score is the new max, and its col and row are saved in match_l and match_w
        if (match_score > max_match_score) {
            max_match_score = match_score;
            match_l = match_lot[i].row;
            match_w = match_lot[i].col;
        }
    }
    //The lot that matches the car best is updated accordingly
    parking_lot[match_l][match_w].row = match_l;
    parking_lot[match_l][match_w].col = match_w;
    parking_lot[match_l][match_w].current_car = car_user;
    parking_lot[match_l][match_w].has_car = 1;
    parking_lot[match_l][match_w].status = Status_Reserved;

    //match_lot is freed
    free(match_lot);
}
