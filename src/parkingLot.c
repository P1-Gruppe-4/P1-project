#include <stdio.h>
#include "main.h"


lot** carFill (lot** pointer, int length, int width){
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

lot** pathCreate(lot** pointer, int length, int width){

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


