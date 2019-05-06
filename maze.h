#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdbool.h>

#include "player.h"

#define MAZE_SIZE 100

typedef struct point {
    GLfloat x;
    GLfloat y;
} Point;

typedef struct line {
    Point a;
    Point b;
} Line;

struct maze {
    // Maze lines
    Line lines[MAZE_SIZE];
    // Maze line width
    int line_width;
};

struct maze_file {
    char* path;
    FILE* file;
};


typedef struct maze Maze;
typedef struct maze_file MazeFile;

bool maze_load(MazeFile *, Maze **);
void maze_draw(Maze *, bool);
void maze_collision(Player *, Maze *);

#endif // MAZE_H
