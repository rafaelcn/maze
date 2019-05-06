/**
 * MIT License
 *
 * Copyright (c) 2018 Rafael Campos Nunes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE  SOFTWARE.
 */

#ifndef MATHEXT_H
#define MATHEXT_H

#ifndef M_E
#define M_E 2.718281828459045  // defined as exp(1.0)
#endif // M_E

#ifndef M_PI
#define M_PI 3.141592653589793 // defined as acos(-1.0)
#endif // M_PI

struct point {
    double x;
    double y;
};

struct vector {
    double x;
    double y;
    double length;
};

typedef struct point Point;
typedef struct vector Vector;

#endif // MATHEXT_H
