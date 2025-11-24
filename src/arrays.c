/*
 * OBS !!!!!
 * Denne kode stammer fra oprindeligt: https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * Da jeg havde problemer med at få allocationen af arena arrayet til at virke. Jeg har blot afproevet og aendret koden, saaledes, at den passer til projektet
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "main.h"
//todo: adapt whole to new project names
//todo: apply new struct names etc.
lot** ArrayAlloc (int length, int width)
{
    lot** pointer = malloc(sizeof(*pointer) * (size_t)length); //how many arrays do I want
    assert(pointer != NULL);

    for(size_t i=0; i<(size_t)width; i++) // how big are the inside-arrays
    {
        pointer[i] = malloc(sizeof(**pointer) * (size_t)width);
        assert(pointer[i] != NULL);
    }

    return pointer; 
}

lot** ArrayFill (lot** pointer, int length, int width){
    for(int i=0; i<width; i++) //using size_t, since sizeof() returns a size_t - at least as far as I understand
    {
        for(int j=0; j<length; j++)
        {
            pointer[i][j].status = 0;
            pointer[i][j].handicap = 0;
        }
    }

    return pointer;
}

//This functions print out the parkingLot array in a 2d grid. It is not necessarily suited for the later, user-interface
//of our application and should maybe rather only be used for inital debugging purposes
void ArrayPrint (lot** pointer, int length, int width)
{
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<width; j++)
        {
            printf("[Status: %d  Handicap: %d] ", pointer[i][j].status, pointer[i][j].handicap);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * The function below did for some reason not work, someone please review:
void ArrayFree (lot** pointer, int length, int width)
{

    for(int i=0; i<length; i++)
    {
        free(pointer[i]);
        pointer[i] = NULL;
    }
    free(pointer);
    pointer = NULL;
}
*/