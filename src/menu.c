#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

car create_car() {
    car newCar;
    char handicapInput; // buffer to store "y" / "n"

    printf("Enter stay duration hours: ");
    scanf("%lf", &newCar.durationStay);

    printf("Enter handicap, type y or n: ");
    scanf(" %c", &handicapInput); // read string

    // Convert string to handicap value
    if (tolower(handicapInput) == 'y') {
        newCar.handicap = 1;
    } else if (tolower(handicapInput) == 'n') {
        newCar.handicap = 0;
    } else {
        printf("Invalid input, defaulting handicap to no\n");
        newCar.handicap = 0;
    }

    printf("Who is travelling in the car? 0 for Worker, 1 for VIP's, 2 for Guests ");
    int temp;
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.role = Worker;
            break;
        case 1:
            newCar.role = VIP;
            break;
        case 2:
            newCar.role = Guest;
            break;
        default:
            newCar.role = Guest;
    }

    printf("If any, what passengers are in the car? 0 for Adult, 1 for Family, 2 for Elderly ");
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.passenger = Adult;
            break;
        case 1:
            newCar.passenger = Family;
            break;
        case 2:
            newCar.passenger = Elderly;
            break;
        default:
            newCar.passenger = Adult;
    }

    printf("How big is your Car?: 0 for Small, 1 for Medium, 2 for Large, 3 for special");
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.size = Small;
            break;
        case 1:
            newCar.size = Medium;
            break;
        case 2:
            newCar.size = Large;
            break;
        case 3:
            newCar.size = Special;
            break;
        default:
            newCar.size = Small;
    }
    return newCar;
}

void create_menu() {
    int done = 0;
    int lengthLot, widthLot;
    while (done == 0) {
        printf(
            "Welcome to Lotimizer2D\n----------------------\nIf you want to create a new lot press 1\nIf you want to load from file press 2\n If you want to exit the program press 3\n");
        int input;
        scanf("%d", &input);

        switch (input) {
            case 1: {
                int length, width;
                do {
                    printf("Enter length and width: ");
                    scanf("%d %d", &length, &width);
                } while (length <= 0 || width <= 0);

                lot **parking_lot = ArrayAlloc(length, width);
                //ArrayFill(parking_lot, length, width); debug
                pathCreator(parking_lot, length, width);
                parking_lot = lotAssigner(parking_lot, length, width);
                ArrayPrint(parking_lot, length, width);
                add_cars(parking_lot, length, width);
                break;
            }

            case 2: {
                printf(
                    "If you want to load from autosave press 1\nIf you want to load from a different file press 2, 0 to go back to main menu\n");
                int loadChoice = 0;
                char autofile[] = "autosave.txt";
                char filename[100];
                scanf("%d", &loadChoice);

                switch (loadChoice) {
                    case 1: {
                        FILE *autosavefile = fopen(autofile, "r");

                        if (autosavefile == NULL) {
                            printf("ERROR! No auto saves found! Redirecting to the main menu.\n\n");
                            break;
                        }
                        lot **parking_lot = load_save(autosavefile, &lengthLot, &widthLot);
                        if (parking_lot != NULL) {
                            add_cars(parking_lot, lengthLot, widthLot);
                        }
                        break;
                    }
                    case 2: {
                        while (1) {
                            printf("Please enter filename:\n");
                            scanf("%99s", filename);
                            FILE *savefile = fopen(filename, "r");

                            if (savefile == NULL) {
                                printf("ERROR! Invalid input, try again:\n\n");
                            } else {
                                lot **parking_lot = load_save(savefile, &lengthLot, &widthLot);
                                if (parking_lot != NULL) {
                                    add_cars(parking_lot, lengthLot, widthLot);
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 0: {
                        break;
                    }
                    default: {
                        printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
                    }
                }
                break;
            }
            case 3: {
                done = 1;
                break;
            }
            default: {
                printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
            }
        }
    }
}

// Helper function to add cars to the loaded array
void add_cars(lot **parking_lot, int length, int width) {
    char c = 'y';
    while (tolower(c) != 'n') {
        printf("Do you wish to set cars into the lot? (y/n): ");
        scanf(" %c", &c);
        if (tolower(c) == 'y') {
            car new_car = create_car();
            mapToLot(new_car, parking_lot, length, width);
        }
    }
    auto_save(parking_lot, length, width);
    ArrayFree(parking_lot, length);
}
