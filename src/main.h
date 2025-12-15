//
// Created by john on 21/11/2025.
//

#ifndef P1_GRUPPE4_MAIN_H
#define P1_GRUPPE4_MAIN_H

//necessary headerfiles
#include <stddef.h>
#include <stdio.h>

//Enum for the different passenger types
typedef enum {
    Adult,
    Family,
    Elderly
} passenger_type;

//Enum for the different type of status which the individual lot can have
typedef enum {
    Status_Free,
    Status_Reserved,
    Status_Path,
    Status_Entrance,
    Status_Exit
} lot_status;

//Enum for the different type of car sizes
typedef enum {
    Small,
    Medium,
    Large,
    Special
} car_size;

//Enum for different types of roles at the venue
typedef enum {
    Worker,
    VIP,
    Guest
} role_venue;

//Structs that will be used in the project
typedef struct car {
    // Whether the car is with handicapped passengers 0 for no, 1 for yes
    int handicap;
    // The duration which the drivers wish to stay at the venue
    double duration_stay;
    // The size of the car
    car_size size;
    // The types of passengers e.g. family with children or elderly
    passenger_type passenger;
    // The role of the passengers at the venue
    role_venue role;

    // The plate number of the car
    char number_plate[16];
} car;

typedef struct lot {
    //Whether the cell is Free, Reserved, Path, Entrance or Exit
    lot_status status;

    //Whether spot is for handicap 0 for no, 1 for yes
    int is_handicap_spot;
    // double for hours of max duration to stay on specific spot
    double max_duration;
    //The carsize which the spot is made for
    car_size max_size;
    //The preffered type of passenger the spot is made for e.g. elderly or families with children
    passenger_type preferred_passenger;
    //The role which the spot is made for e.g. VIP, guest or worker
    role_venue allowed_role;

    // Length and width of the spot, not used in logical model
    double spot_width;
    double spot_length;

    // If there is a car in the spot 0 if no 1 if yes
    int has_car;
    // The car that is in the spot if hasCar is 1
    car current_car;

    //Positions in grid and distance to entrance
    int distance;
    int row;
    int col;
} lot;

//prototypes from arrays.c
lot **array_alloc(int length, int width);

lot **array_fill(lot **pointer, int length, int width);

void array_free(lot **pointer, int length);

void array_print(lot **pointer, int length, int width);


//void ArrayFree(lot** pointer, int length, int width);
void arrange_car(lot **parking_lot, car Car, int x0, int y0);

//prototypes from menu.c
void main_menu();
void lot_menu(lot **parking_lot, int length, int width) ;
void add_cars(lot **parking_lot, int length, int width);

//prototypes from save.c
void auto_save(lot **pointer, int length, int width);

lot **load_save(FILE *save_file, int *length, int *width);

//prototypes from mapToLot.c
int is_handicap(lot lot, int car_hand);
int is_type(lot lot, car_size size);
int is_role(lot lot, role_venue role);

lot *filter_spots(car car_user, lot **p_lot, int length, int width, int *matches);

double duration_score(lot *l, car c);
double passenger_score(lot *l, car c);
double calc_score(double passengerScore, double durationScore);

void map_to_lot(car car_user, lot **p_lot, int length, int width);


//prototypes fra parking_lot.c
int comp(const void *a, const void *b);
void sort_park(lot parking_arr[], int last, int (*fptr)(const void *, const void *));
lot **lot_assigner(lot **parking_lot, int length, int width);
lot **path_creator(lot **parking_lot, int length, int width);

//prototypes from find.c
int find_car_by_numberplate(lot **parking_lot, int length, int width, char *number_plate, int *loc_row, int *loc_col);

//prototypes from delete.c
int delete_car(lot **parking_lot, int length, int width, char *number_plate);

#endif //P1_GRUPPE4_MAIN_H
