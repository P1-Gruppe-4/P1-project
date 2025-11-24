#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
void auto_save(lot** parkinglot, int length, int width) {
    FILE* autosave = fopen("autosave.txt", "w");
    assert(autosave != NULL);

    for (int i = 0; i < length; i++) {
        fwrite(parkinglot[i], sizeof(lot), (size_t)width, autosave);
    }
    printf("Autosave completed\n");
}
*/

void auto_save (lot** pointer, int length, int width)
{
    FILE* auto_save = fopen("autosave.txt", "w");
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
    lot **parkingLot;
    while (feof(savefile) <= 0) {
        int counter_1 = 0, counter_2 = 0;

        if (getc(savefile) == '\n') {
            counter_1++;
        }
        fscanf(savefile, "%[^-]d %[^-]d", parkingLot[counter_1][counter_2].status, parkingLot[counter_1][counter_2].handicap);
        counter_2++;
    }
    fclose(savefile);
    return parkingLot;
}
