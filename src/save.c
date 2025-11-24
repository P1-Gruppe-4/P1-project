#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void auto_save (lot** pointer, int length, int width)
{
    FILE* auto_save = fopen("autosave.txt", "w");
    fprintf(auto_save, "%d %d-", length, width); //burde virke da de første to værdier bliver læst i starten dvs. de er ikke tilgængelige for at blive indlæst senere igen
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<width; j++)
        {
            fprintf(auto_save, "%d %d-", pointer[i][j].status, pointer[i][j].handicap);
        }
        printf("\n");
    }
    printf("\n");
    fclose(auto_save);
    printf("Autosave completed, saved to %s\n", "autosave.txt");

}

lot** load_save(FILE* savefile) {
    int length, width;
    fscanf(savefile, "%d %d", &length, &width);

    lot **parkingLot = ArrayAlloc(length, width);
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            fscanf(savefile, "%d %d-", &parkingLot[i][j].status, &parkingLot[i][j].handicap);
        }
    }

    fclose(savefile);
    ArrayPrint(parkingLot, length, width);
    return parkingLot;
}
