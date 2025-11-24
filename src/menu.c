#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void create_menu() {
    printf("Welcome to Lotimizer2D\n----------------------\nType 1 to create a new lot, type 2 to read from file\n");
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
        auto_save(parkingLot, lenght, width);

        //ArrayFree(parkingLot, lenght, width);
        free(parkingLot);
    }
    else if (input == 2) {
        printf("If you want to load from autosave press 1\nIf you want to load from a different file press 2\n");
        int input = 0;
        scanf("%d", &input);
        switch (input) {
            case 1:
                FILE* savefile = fopen("autosave.txt", "r");
                load_save(savefile);
                break;
            case 2:
                printf("not yet implemented\n");
                exit(0);

        }
    }
    else {
        printf("ERROR! Invalid input, try again:\n\n");
        create_menu();
    }
}

