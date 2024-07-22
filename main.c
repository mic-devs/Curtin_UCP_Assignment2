#include <stdio.h>
#include <stdlib.h>
#include "build.h"
#include "game.h"

int main(int argc, char* argv[])
{
    FILE* fileName;
    char** map;
    int row, column, i, j, stat;
 
/* Checking Arguments */
    if (argc != 2)
    {
        printf("Error: Pass 2 arguments only!\n");
        return 1;
    }
    else /* Check if filename is null */
    {
        fileName = fopen(argv[1],"r");
        if (fileName == NULL)
        {
            printf("Error: File is null!\n");
        }
    }
/* Checking Arguments */

    fscanf(fileName, "%d %d", &row, &column); /* Obtain size from file */
    row += 2; /* Add 2 rows for borders */
    column += 2; /* Add 2 columns for borders */

/* Malloc the 2D array */
    map = (char**)malloc(row * sizeof(char*)); 
    for (i = 0; i < row; i++) 
    { 
        map[i] = (char*)malloc(column * sizeof(char));
    }
/* Malloc the 2D array */

/* Get map info from file */
    while (fgetc(fileName) != EOF)
    {
        for (i = 1; i < row-1; i++)
        {
            for (j = 1; j < column - 1; j++)
            {
                fscanf(fileName, " %c ", &map[i][j]);
            }
        }
    }
/* Get map info from file */

    map = build(map, row, column);

    stat = play(map, row, column);

    if (stat == 1)
    {
        printf("\nYou win!\n");
    }
    else if (stat == 2)
    {
        printf("\nYou lose!\n");
    }

    /* The following code to free the malloc 'map' array causes a segmentation error

    for(i = 0; i < row; i++)
    {
        free(map[i]);
        map[i] = NULL;
    }
    free(map);
    map = NULL;

    */

    return 0;
}