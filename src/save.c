#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*This function extracts the current parking-lot data and writes it into an autosave.txt file
 *Doing this ensure that there is always at least one fallback save for the user.
 *This function additionally creates an autosave-file if there is none yet. Do not, that the autosave file
 *ONLY contains the latest save, not multiple saves.
 */
void auto_save (lot** pointer, int length, int width)
{
    FILE* auto_save = fopen("autosave.txt", "w");
    fprintf(auto_save, "%d %d-", length, width); //burde virke da de første to værdier bliver læst i starten dvs. de er ikke tilgængelige for at blive indlæst senere igen
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<width; j++)
        {
            fprintf(auto_save, "%d %d-", pointer[i][j].status, pointer[i][j].isHandicapSpot); //writes every individual array-cell into autosave.txt
        }
    }
    printf("\n");
    fclose(auto_save);
    printf("Autosave completed, saved to %s\n", "autosave.txt"); //debug

}

//This function extracts saved data in the correct format from the provided savefile
lot** load_save(FILE* savefile) {
    int length, width;
    fscanf(savefile, "%d %d", &length, &width);

    lot **parkingLot = ArrayAlloc(length, width);
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {

            //todo: fix -2 bug
            fscanf(savefile, "%d %d-", &parkingLot[i][j].status, &parkingLot[i][j].isHandicapSpot);
        }
    }

    fclose(savefile);
    ArrayPrint(parkingLot, length, width);
    return parkingLot;
}
