#include "main.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void ArrangeCar(lot** parkingLot, car Car, int x0, int y0);

int main(int argc, char* argv[])
{
    create_menu();
    return 0;
}

//This function takes a given car, and its assigned lot, and then puts said car into its spot inside the
//parkingLot array
void ArrangeCar(lot** parkingLot, car Car, int x0, int y0)
{
    int width = Car.width + Car.doorLength*2; //Takes each cars' doors into account (doors on both sides) so that the passenger(s) can still get out of the car
    int length = Car.length; //redudant

    //OBS! Currently this function has no sort of failsave, and therefore malicious input can result in
    //segmentationfaults. This is due to the fact, that this function is supposed to be run *after*
    //an adequate spot has been picked i.e. everything is already safe to go

    for (int i = y0; i < length+1; i++)
    {
        for (int j = x0; j < width+1; j++)
        {
            parkingLot[i][j].status = 1; //cause sigsegv
        }
    }
    printf("\nCar has recieved adequated spot\n");
}
