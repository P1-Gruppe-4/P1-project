#include "main.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void ArrangeCar(lot** parkingLot, car Car, int x0, int y0);

int main(int argc, char* argv[])
{
    int lenght, width;
    printf("Enter length, then width as integers: ");
    scanf("%d %d", &lenght, &width);
    assert(width > 0 && lenght > 0); //debug

    lot** parkingLot = ArrayAlloc(lenght, width);
    ArrayFill(parkingLot, lenght, width);
    ArrayPrint(parkingLot, lenght, width);

    car testcar = {3, 2, 1};
    ArrangeCar(parkingLot, testcar, 1, 1);

    //ArrayFree(parkingLot, lenght, width);
    free(parkingLot);
    return 0;
}

//This function takes a given car, and its assigned lot, and then puts said car into its spot inside the
//parkingLot array
void ArrangeCar(lot** parkingLot, car Car, int x0, int y0)
{
    int width = Car.width + Car.doorLength; //so that the passenger can still get out of the car
    int length = Car.length; //redudant

    for (int i = y0; i < length+1; i++)
    {
        for (int j = x0; j < width+1; j++)
        {
            parkingLot[i][j].status = 1; //cause sigsegv
        }
    }
    printf("\nCar has recieved adequated spot\n");
}
