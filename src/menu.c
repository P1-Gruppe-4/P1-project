#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void create_menu() {
    printf("Welcome to Lotimizer2D\n----------------------\nIf you want to create a new lot press 1\nIf you want to load from file press 2\n");
    int input;
    scanf("%d", &input);

    if (input == 1) {
        int lenght, width;
        printf("Enter length, then width as integers: ");
        scanf("%d %d", &lenght, &width);
        assert(width > 0 && lenght > 0); //debug

        lot** parkingLot = ArrayAlloc(lenght, width);
        ArrayFill(parkingLot, lenght, width);
        ArrayPrint(parkingLot, lenght, width);

        //car testcar = {3, 2, 1};
        //ArrangeCar(parkingLot, testcar, 1, 1); is commented out to prevent temporary segmentationfaults
        ArrayPrint(parkingLot, lenght, width);
        auto_save(parkingLot, lenght, width) ;

        //ArrayFree(parkingLot, lenght, width);
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