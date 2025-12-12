#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*This function extracts the current parking-lot data and writes it into an autosave.txt file
 *Doing this ensure that there is always at least one fallback save for the user.
 *This function additionally creates an autosave-file if there is none yet. Do not, that the autosave file
 *ONLY contains the latest save, not multiple saves.
 */
void auto_save(lot **parking_lot, int length, int width) {
    //File pointer to autosave that opens autosave.txt in write mode
    FILE *auto_save = fopen("autosave.txt", "w");
    // Check if file auto_save opens
    if (!auto_save) {
        printf("ERROR: Could not open file autosave.txt for writing\n");
        return;
    }
    // Save length and width of the array
    fprintf(auto_save, "%d %d\n", length, width);
    //writes every individual array-cell into autosave.txt
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            //Writes the status of the lot, whether it is handicapped and whether it has a car into autosave.txt
            fprintf(auto_save,
                    "%d %d %lf %d %d %d %lf %lf %d %d %d %d",
                    parking_lot[i][j].status,
                    parking_lot[i][j].isHandicapSpot,
                    parking_lot[i][j].maxDuration,
                    parking_lot[i][j].maxSize,
                    parking_lot[i][j].preferredPassenger,
                    parking_lot[i][j].allowedRole,
                    parking_lot[i][j].spotWidth,
                    parking_lot[i][j].spotLength,
                    parking_lot[i][j].hasCar,
                    parking_lot[i][j].distance,
                    parking_lot[i][j].row,
                    parking_lot[i][j].col
            );
            //If it has a car, the car is also saved
            if (parking_lot[i][j].hasCar == 1) {
                fprintf(auto_save, " %lf %d %d %d %d", parking_lot[i][j].currentCar.durationStay,
                        parking_lot[i][j].currentCar.handicap, parking_lot[i][j].currentCar.passenger,
                        parking_lot[i][j].currentCar.role, parking_lot[i][j].currentCar.size);
            }
            fprintf(auto_save, "\n");
        }
    }
    fclose(auto_save);
    printf("Autosave completed, saved to %s\n", "autosave.txt"); //debug
}

//This function extracts saved data in the correct format from the provided savefile
lot **load_save(FILE *savefile, int *length, int *width) {
    int lengthArr, widthArr;
    fscanf(savefile, "%d %d", &lengthArr, &widthArr);
    *length = lengthArr;
    *width = widthArr;

    lot **parking_lot = ArrayAlloc(lengthArr, widthArr);
    for (int i = 0; i < lengthArr; i++) {
        for (int j = 0; j < widthArr; j++) {
            fscanf(savefile,
                     "%d %d %lf %d %d %d %lf %lf %d %d %d %d",
                     &parking_lot[i][j].status,
                     &parking_lot[i][j].isHandicapSpot,
                     &parking_lot[i][j].maxDuration,
                     &parking_lot[i][j].maxSize,
                     &parking_lot[i][j].preferredPassenger,
                     &parking_lot[i][j].allowedRole,
                     &parking_lot[i][j].spotWidth,
                     &parking_lot[i][j].spotLength,
                     &parking_lot[i][j].hasCar,
                     &parking_lot[i][j].distance,
                     &parking_lot[i][j].row,
                     &parking_lot[i][j].col
             );
            if (parking_lot[i][j].hasCar == 1) {
                fscanf(savefile, " %lf %d %d %d %d", &parking_lot[i][j].currentCar.durationStay,
                       &parking_lot[i][j].currentCar.handicap, &parking_lot[i][j].currentCar.passenger,
                       &parking_lot[i][j].currentCar.role, &parking_lot[i][j].currentCar.size);
            }
        }
    }
    fclose(savefile);
    ArrayPrint(parking_lot, lengthArr, widthArr);
    return parking_lot;
}