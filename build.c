#include <stdio.h>
#include <stdlib.h>
#include "build.h"

char** build(char** area, int row, int column)
{
    int i, j;


/* Making the borders */
    for (i = 0; i < column; i++) /* Set top & bottom borders */
    { 
        area[0][i] = '*';
        area[row-1][i]= '*';
    }

    for (i = 0; i < row; i++) /* Set left & right borders */
    {
        area[i][0] = '*';
        area[i][column-1] = '*';
    }
/* Making the borders */

/* Replace numbers with empty space, road, player and goal */

    for (i = 1; i < row-1; i++)
    {
        for (j = 1; j < column-1; j++)
        {
            if (area[i][j] == '0')
            { 
                area[i][j] = ' ';
            }
            else if (area[i][j] == '1')
            { 
                area[i][j] = '.';
            }
            else if (area[i][j] == '2')
            { 
                area[i][j] = '>';
            }
            else if (area[i][j] == '3')
            { 
                area[i][j] = 'P';
            }
            else if (area[i][j] == '4')
            { 
                area[i][j] = 'G';
            }
        }
    }

/* Replace numbers with empty space, road, player and goal */

    return area;

/* Free the area */
    for(i = 0; i < row; i++)
    {
        free(area[i]);
        area[i] = NULL;
    }
    free(area);
    area = NULL;
/* Free the area */

}