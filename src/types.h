//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_TYPES_H
#define P1_GRUPPE4_TYPES_H


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

#endif //P1_GRUPPE4_TYPES_H