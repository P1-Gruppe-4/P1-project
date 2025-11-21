#include "main.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int lenght, width;
    printf("Enter length, then width as integers: ");
    scanf("%d %d", &lenght, &width);
    assert(width > 0 && lenght > 0); //debug

    int** lot = array_alloc(lenght, width);
    return 0;
}
