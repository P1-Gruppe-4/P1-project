#include <stdio.h>
#include "main.h"

#define pathSpace 3
#define carLength 2


//prints the paths of the parking lot layout
lot** pathCreator(lot** pointer, int length, int width){
  //for loop demon right here
  for(int i=0; i<length; i++){ //i & j loops tru whole parking lot 
    for(int j=0; j<width; j++){
      for(int x=0; x<pathSpace; x++){ //x & y loops tru the top and right side for pathspace size 
        pointer[x][j].status=2;
        if (j == width-pathSpace) {
          for(int y=width-pathSpace; y<width; y++){
          pointer[i][y].status=2;
          }
        }
      }
      for(int n=0; n<pathSpace; n++){ //inital path 
        pointer[carLength*2+pathSpace+n][j].status=2;
      }
      //makes a path every carlength*2
      for(int c=carLength*2+pathSpace*3+1; c+pathSpace<=length; c+=carLength*2+pathSpace){
        for(int n = 0; n < pathSpace; n++){
              pointer[c + n][j].status = 2;
        }
      }
    }
  }

return pointer;
}

//Denne funktion gennemgår parkeringpladsen og sætter nogle af de forskellige
//variabler

lot** lotAssigner(lot** pointer, int legth, int width){
  //bestem os for en exit og entrance
  //start med at angive hvor meget plads der skal bruges på hver size class
  //angiv hvor mange handicap spots der skal være og hvor
  //angiv hvilke pladser som prioritere hvilke stay durations
  //angiv hvilke pladser priotitere små børn og ældre
}









