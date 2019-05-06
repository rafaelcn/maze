#include "color.h"

#include <stdlib.h>

Color white = {1.0, 1.0, 1.0, 1.0};
Color black = {0.0, 0.0, 0.0, 1.0};
Color gray = {0.6, 0.6, 0.6, 1.0};
Color yellow = {1.0, 1.0, 0.0, 1.0};

Color light_gray = {0.9, 0.9, 0.9, 1.0};
Color light_yellow = {0.8, 0.8, 0.1, 0.9};
Color light_blue = {0.2, 0.3, 0.7, 1.0};

GLfloat *get_colorv(Color a) {

    GLfloat *color = malloc(4 * sizeof(GLfloat));

    color[0] = a.r;
    color[1] = a.g;
    color[2] = a.b;
    color[3] = a.a;

    return color;
}
