/*
 * Group of colors to be used with OpenGL glClearColor() or glColor4d() or
 * glColor4f() or anything else that suits your purpose.
 *
 */

#ifndef COLOR_H
#define COLOR_H

#include <GL/gl.h>

struct color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

typedef struct color Color;

// predefined colors

Color white;
Color black;
Color yellow;
Color green;
Color red;
Color blue;
Color light_blue;
Color gray;

GLfloat *get_colorv(Color c);

#endif // COLOR_H
