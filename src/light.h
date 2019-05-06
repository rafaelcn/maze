#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>

struct light {
    GLfloat color[4];
    GLfloat direction[4];
    GLfloat position[3];
};


typedef struct light Light;

#endif // LIGHT_H
