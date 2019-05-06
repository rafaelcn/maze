#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/gl.h>

struct player {
    GLfloat x;
    GLfloat y;
    GLdouble speed;
    GLdouble width;
    GLdouble height;
};

typedef struct player Player;

void player_draw(Player *, bool);

#endif // PLAYER_H
