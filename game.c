#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "terminal.h"

int play(char** map, int row, int column)
{
    int status = 0; /* 0 for in-game, 1 for win, 2 for lose */
    int i, j;
    char move, temp;
    Player p;
    Car c;

/* Search for player and car, then store in respective struct */

    for (i = 1; i < row-1; i++)
    {
        for (j = 1; j < column-1; j++)
        {
            if (map[i][j] == 'P')
            { /* find and allocate player */
                p.row = i;
                p.col = j;
                p.pos = ' ';
            }
            else if (map[i][j] == '>')
            { /* find and allocate car */
                c.dir = '>';
                c.row = i;
                c.col = j;
            }
        }
    }

/* Search for player and car, then store in respective struct */

    while (status == 0)
    {   
        system("clear"); /* clears the terminal screen */
        for (i = 0; i < row; i++) /* Prints the play area map */
        { 
            for (j = 0; j < column; j++) 
            {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        printf("Press w to move up\n");
        printf("Press s to move down\n");
        printf("Press a to move left\n");
        printf("Press d to move right\n");
        printf("Press u to undo\n");

        disableBuffer();
        scanf("%c", &move); /* take player movement */
        enableBuffer();

/* Player Movement */
        if (move == 's') /* move down */
        {
            if ( (p.row+1) != (row-1) ) /* ensure player doesn't pass border */
            {
                temp = map[ p.row+1 ][ p.col ]; /* destination */
                
                map[ p.row ][ p.col ] = p.pos; /* mark origin appropriately */

                if (temp == 'G')
                { /* if destination is blank, origin must be road */
                    status = 1; /* Game ends, player wins */
                }
                else if ((temp == '.') || (temp == ' '))
                {
                    p.pos = temp;
                }
                else
                {
                    p.pos = '.';
                }

                p.row = p.row + 1; /* Update player coordinates */
            }
        }
        else if (move == 'w') /* move up */
        {
            if ( (p.row-1) != 0 ) /* ensure player doesn't pass border */
            {
                temp = map[ p.row-1 ][ p.col ]; /* destination */
                
                map[ p.row ][ p.col ] = p.pos; /* mark origin appropriately */

                if (temp == 'G')
                { /* if destination is blank, origin must be road */
                    status = 1; /* Game ends, player wins */
                }
                else if ((temp == '.') || (temp == ' '))
                {
                    p.pos = temp;
                }
                else
                {
                    p.pos = '.';
                }

                p.row = p.row - 1; /* Update player coordinates */
            }
        }
        else if (move == 'a') /* move left */
        {
            if ( (p.col-1) != 0 ) /* ensure player doesn't pass border */
            {
                temp = map[ p.row ][ p.col-1 ]; /* destination */
                map[ p.row ][ p.col ] = p.pos; /* mark origin appropriately */

                if (temp == 'G')
                { 
                    status = 1; /* Game ends, player wins */
                }
                else if ((temp == '.') || (temp == ' '))
                {
                    p.pos = temp;
                }
                else
                {
                    p.pos = '.';
                }

                p.col = p.col - 1; /* Update player coordinates */
            }
        }
        else if (move == 'd') /* move right */
        {
            if ( (p.col+1) != column-1 ) /* ensure player doesn't pass border */
            {
                temp = map[ p.row ][ p.col+1 ]; /* destination */
                map[ p.row ][ p.col ] = p.pos; /* mark origin appropriately */

                if (temp == 'G')
                { 
                    status = 1; /* Game ends, player wins */
                }
                else if ((temp == '.') || (temp == ' '))
                {
                    p.pos = temp;
                }
                else
                {
                    p.pos = '.';
                }

                p.col = p.col + 1; /* Update player coordinates */
            }
        }
        else
        {
            /* nothing happens if user enters invalid input */
        }
/* Player Movement */

/* Car Movement */
        if ((move == 'w') || (move == 'a') || (move == 's') || (move == 'd'))
        { /* only move car if player moves */
            if (c.dir == '>')
            { /* when car is facing east */
                if (map[c.row][c.col+1] == '.')
                { /* check front of car */
                    map[c.row][c.col] = '.'; /* set origin back to road */
                    map[c.row][c.col+1] = '>';
                    c.col++;
                } 
                else if (map[c.row+1][c.col] == '.')
                { /* check right of car */
                    map[c.row][c.col] = '.';
                    map[c.row+1][c.col] = 'v';
                    c.row++;
                    c.dir = 'v';
                } 
                else if (map[c.row-1][c.col] == '.')
                { /* check left of car */
                    map[c.row][c.col] = '.';
                    map[c.row-1][c.col] = '^';
                    c.row--;
                    c.dir = '^';
                }
            }
            else if (c.dir == '^')
            { /* when car is facing north */
                if (map[c.row-1][c.col] == '.')
                { /* check front of car */
                    map[c.row][c.col] = '.';
                    map[c.row-1][c.col] = '^';
                    c.row--;
                } 
                else if (map[c.row][c.col+1] == '.')
                { /* check right of car */
                    map[c.row][c.col] = '.';
                    map[c.row][c.col+1] = '>';
                    c.col++;
                    c.dir = '>';
                } 
                else if (map[c.row][c.col-1] == '.')
                { /* check left of car */
                    map[c.row][c.col] = '.';
                    map[c.row][c.col-1] = '<';
                    c.col--;
                    c.dir = '<';
                }
            }
            else if (c.dir == '<')
            { /* when car is facing west */
                if (map[c.row][c.col-1] == '.')
                { /* check front of car */
                    map[c.row][c.col] = '.';
                    map[c.row][c.col-1] = '<';
                    c.col--;
                } 
                else if (map[c.row-1][c.col] == '.')
                { /* check right of car */
                    map[c.row][c.col] = '.';
                    map[c.row-1][c.col] = '^';
                    c.row--;
                    c.dir = '^';
                } 
                else if (map[c.row+1][c.col] == '.')
                { /* check left of car */
                    map[c.row][c.col] = '.';
                    map[c.row+1][c.col] = 'v';
                    c.row++;
                    c.dir = 'v';
                }
            }
            else if (c.dir == 'v')
            { /* when car is facing south */
                if (map[c.row+1][c.col] == '.')
                { /* check front of car */
                    map[c.row][c.col] = '.';
                    map[c.row+1][c.col] = 'v';
                    c.row++;
                } 
                else if (map[c.row][c.col-1] == '.')
                { /* check right of car */
                    map[c.row][c.col] = '.';
                    map[c.row][c.col-1] = '<';
                    c.col--;
                    c.dir = '<';
                } 
                else if (map[c.row][c.col+1] == '.')
                { /* check left of car */
                    map[c.row][c.col] = '.';
                    map[c.row][c.col+1] = '>';
                    c.col++;
                    c.dir = '>';
                }
            }
        }
/* Car Movement */

        map[p.row][p.col] = 'P'; /* Mark player on the map */

        /* Check if player has collided with car */
        if ( (p.row == c.row) && (p.col == c.col) )
        {
            status = 2;
        }
    }        

    system("clear"); /* clears the terminal screen */
    for (i = 0; i < row; i++) /* Prints the map */
    { 
        for (j = 0; j < column; j++) 
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    
/* Free the map */
    for(i = 0; i < row; i++)
    {
        free(map[i]);
        map[i] = NULL;
    }
    free(map);
    map = NULL;
/* Free the map */

    return status;
}