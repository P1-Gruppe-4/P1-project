#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

car create_car(){
    car newCar;
    char handicapInput[10];   // buffer to store "Yes" / "No"

    printf("Enter stay duration hours: ");
    scanf("%lf", &newCar.durationStay);

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

    printf("Who is travelling in the car? 0 for Service Technician, 1 for VIP's, 2 for Guests, any key for none: ");
    int temp;
    scanf("%d", &temp);
    switch (temp)
    {
    case '0':
      newCar.role = temp;
      break;
    case '1':
      newCar.role = temp;
      break;  
    case '2':
      newCar.role = temp;
      break;
    default:
        newCar.role = 2;
    }

    printf("If any, what passengers are in the car? 0 for Adult, 1 for Family, 2 for Elderly, any key for none: ");
    scanf("%d", &temp);
    switch (temp)
    {
    case '0':
      newCar.passenger = temp;
      break;
    case '1':
      newCar.passenger = temp-'0';
      break;
    case '2':
      newCar.passenger = temp-'0';
      break;
    default:
      newCar.passenger = 0;
    }

    printf("How big is your Car?: 0 for Small, 1 for Medium, 2 for Large, 3 for other");
    scanf("%d", &temp);
    switch (temp)
    {
    case '0':
        newCar.size = temp;
        break;
    case '1':
        newCar.size = temp;
        break;
    case '2':
        newCar.size = temp;
        break;
    default:
        newCar.size = 2;
    }

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
        //ArrayFill(parkingLot, length, width); debug
        pathCreator(parkingLot, length, width);
        parkingLot = lotAssigner(parkingLot, length, width);
        ArrayPrint(parkingLot, length, width);
        //car testcar = {3, 2, 1};
        //ArrangeCar(parkingLot, testcar, 1, 1); //is commented out to prevent temporary segmentationfaults
        //ArrayPrint(parkingLot, length, width);
        char c = 'y';

        while (c != 'n')
        {
            printf("Do you wish to set cars into the lot? (y/n): ");
            scanf(" %c", &c);
            if (c == 'y')
            {
                //get car etc.
                car new_car = create_car();
                mapToLot(new_car, parkingLot, length, width);
            }
        }

        auto_save(parkingLot, length, width);

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
