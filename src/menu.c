#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//Bjarne grrr code ahh

car create_car() {

    car newCar;
    char handicapInput[10];   // buffer to store "Yes" / "No"

    printf("Enter car length as doubles in meters: ");
    scanf("%d", &newCar.length);

    printf("Enter car width as doubles in meters: ");
    scanf("%d", &newCar.width);

    printf("Enter door length as doubles in meters: ");
    scanf("%d", &newCar.doorLength);

    printf("Enter stay duration time as intigers in seconds: ");
    scanf("%d", &newCar.stayDuration);

    printf("Enter handicap, type Yes or No: ");
    scanf("%9s", handicapInput);   // read string

    // Convert string to handicap value
    if (strcmp(handicapInput, "Yes") == 0 || strcmp(handicapInput, "yes") == 0) {
        newCar.handicap = 1;
    }
    else if (strcmp(handicapInput, "No") == 0 || strcmp(handicapInput, "no") == 0) {
        newCar.handicap = 0;
    }
    else {
        printf("Invalid input, defaulting handicap to 0\n");
        newCar.handicap = 0;
    }

    printf("Enter amount of passengers: ");
    scanf("%d", &newCar.passengers);

    return newCar;
}

void create_menu() {
    printf("Welcome to Lotimizer2D\n----------------------\nIf you want to create a new lot press 1\nIf you want to load from file press 2\n");
    int input;
    scanf("%d", &input);

    if (input == 1) {
        int length, width;
        printf("Enter length, then width as integers: ");
        scanf("%d %d", &length, &width);
        assert(width > 0 && length > 0); //debug

        lot** parkingLot = ArrayAlloc(length, width);
        ArrayFill(parkingLot, length, width);
        ArrayPrint(parkingLot, length, width);
        carFill(parkingLot, length, width);
        ArrayPrint(parkingLot, length, width);
        //car testcar = {3, 2, 1};
        //ArrangeCar(parkingLot, testcar, 1, 1); //is commented out to prevent temporary segmentationfaults
        //ArrayPrint(parkingLot, length, width);
        auto_save(parkingLot, length, width);

        //ArrayFree(parkingLot, length, width);
        free(parkingLot);
    }
    else if (input == 2) {
        printf("If you want to load from autosave press 1\nIf you want to load from a different file press 2\n");
        int input = 0;
        char autofile[] = "autosave.txt";
        char filename[100];
        scanf("%d", &input);

        switch (input) {
            case 1:
                    FILE* autosavefile = fopen(autofile, "r");

                    if (autosavefile == NULL) {
                        printf("ERROR! No auto saves found! Redirecting to the main menu.\n\n");
                        create_menu();
                        break;
                    }
                load_save(autosavefile);
                break;

            case 2: {
                while (1) {
                    printf("Please enter filename:\n");
                    scanf("%99s", filename);
                    FILE* savefile = fopen(filename, "r");

                    if (savefile == NULL) {
                        printf("ERROR! Invalid input, try again:\n\n");
                    }
                    else {
                        load_save(savefile);
                        break;
                    }
                }
                break;
            }
            default:
                printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
                create_menu();
        }
    }
    else {
        printf("ERROR! Invalid input, try again:\n\n");
        create_menu();
    }
}
