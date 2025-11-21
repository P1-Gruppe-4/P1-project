/*
 * OBS !!!!!
 * Denne kode stammer fra oprindeligt: https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * Da jeg havde problemer med at få allocationen af arena arrayet til at virke. Jeg har blot afproevet og aendret koden, saaledes, at den passer til projektet
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "main.h"

int** array_alloc (int length, int width)
{
    int** pointer = malloc(sizeof(*pointer) * (size_t)length);
    assert(pointer != NULL);

    for(size_t i=0; i<(size_t)length; i++)
    {
        pointer[i] = malloc(sizeof(**pointer) * (size_t)width);
        assert(pointer[i] != NULL);
    }

    return pointer;
}

int** arena_fill (int** pointer, size_t arena_size){
    for(size_t i=0; i<arena_size; i++) //using size_t, since sizeof() returns a size_t - at least as far as I understand
    {
        for(size_t j=0; j<arena_size; j++)
        {
            pointer[i][j] = 9;
        }
    }

    return pointer;
}

void arena_print (int** pointer, size_t arena_size)
{
    for(size_t i=0; i<arena_size; i++)
    {
        for(size_t j=0; j<arena_size; j++)
        {
            printf("%d  ", pointer[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void arena_free (int** pointer, size_t arena_size)
{

    for(size_t i=0; i<arena_size; i++)
    {
        free(pointer[i]);
        pointer[i] = NULL;
    }
    free(pointer);
    pointer = NULL;
}