#ifndef GAME_H
#define GAME_H

int play(char** map, int row, int column);

typedef struct {
    char pos; /* Is player standing on road or empty space */
    int row;
    int col;
} Player;

typedef struct {
    char dir;
    int row;
    int col;
} Car;

#endif