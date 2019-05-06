#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define __windows _WIN32_

// C++-ish allocation type heh
#define new(x) (x*)malloc(sizeof(x))

#ifdef __linux
#include <unistd.h> // for usleep(...)
#elif __windows
#include <windows.h> // for sleep(...)
#endif

#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "oglo.h"
#include "player.h"
#include "maze.h"

// draw stuff on the screen
void draw(void);

// init OpenGL related stuff
void init(void);

// callback functions
void c_keyboard(GLFWwindow*, int, int, int, int);
void c_mousebutton(GLFWwindow*, int, int, int);
void c_mousepos(GLFWwindow*, double, double);

bool running = true;
bool debug = false;

int w_width;
int w_height;

// Game entities
Player *player;
Maze   *maze;
MazeFile mf;

// OpenGL objects

Light l0;

Color ambient_color;

int main(void) {

    GLFWwindow *window;

    w_width = 640;
    w_height = 480;

    if (!glfwInit()) {
        fprintf(stderr, "Error initializing GLFW3");
        return 1;
    }

    window = glfwCreateWindow(w_width, w_height, "Maze runner", NULL, NULL);

    if (!window) {
        printf("Window could not be created, exiting...\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, c_keyboard);
    glfwSetMouseButtonCallback(window, c_mousebutton);
    glfwSetCursorPosCallback(window, c_mousepos);

    glfwSetWindowSizeLimits(window, w_width, w_height, w_width, w_height);

    player = malloc(sizeof(Player));

    if (!player) {
        fprintf(stderr, "Player couldn't be created, exiting...\n");
        return 1;
    }

    player->x = 20.0;
    player->y = 450.0;
    player->speed = 2; // 2 pixels per press
    player->width = 15;
    player->height = 15;

    maze = malloc(sizeof(Maze));
    maze->line_width = 5;

    if (!maze) {
        fprintf(stderr, "Maze couldn't be created, exiting...\n");
        return 1;
    }

    mf.file = NULL;
    mf.path = "maze.txt";

    maze_load(&mf, &maze);

    init();

    // framerate variables
    double desired = 60.f;
    double start_time;
    double end_time;
    double elapsed = 0.f;
    double wait_time = 0.f;
    int frame_count = 0;

    while (!glfwWindowShouldClose(window) && running) {
        glClearColor(white.r, white.g, white.b, white.a);
        start_time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        end_time = glfwGetTime();
        elapsed = end_time-start_time;

        if (elapsed < 1.0f/desired) {
#ifdef __windows
            sleep(wait_time);
#else
            struct timespec wait_time = {.tv_sec = w};

            nanosleep(wait_time, NULL);

            elapsed = 0;

#endif // not windows

            ++frame_count;
        }

    }

    // releasing resources
    free(player);
    free(maze);

    glfwTerminate();

    return 0;
}

void init(void) {

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_width, w_height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Setting position of the light to the same as the player
    l0.position[0] = player->x;
    l0.position[1] = player->y;
    l0.position[2] = 0;

    l0.color[0] = l0.color[1] = 0.4;
    l0.color[2] = 0.0;
    l0.color[3] = 1;
    l0.direction[0] = l0.direction[1] = l0.direction[2] = 1;

    ambient_color.r = ambient_color.g = ambient_color.b = 0;
    ambient_color.a =  1;

    //
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 1.0f);

    // setting the ambient color
    glLightfv(GL_LIGHT1, GL_AMBIENT, get_colorv(ambient_color));
}

void draw(void) {

    glMaterialfv(GL_EMISSION, GL_AMBIENT, get_colorv(ambient_color));
    maze_collision(player, maze);
    maze_draw(maze, debug);

    glMaterialfv(GL_EMISSION, GL_SPECULAR, l0.color);
    player_draw(player, debug);
}

void c_keyboard(GLFWwindow* w, int k, int scancode, int action, int mods) {

    switch (k) {
    case GLFW_KEY_ESCAPE:
        running = 0;
        break;
    case GLFW_KEY_UP:
        player->y -= player->speed;
        l0.position[1] = player->y;
        break;
    case GLFW_KEY_DOWN:
        player->y += player->speed;
        l0.position[1] = player->y;
        break;
    case GLFW_KEY_LEFT:
        player->x -= player->speed;
        l0.position[0] = player->x;
        break;
    case GLFW_KEY_RIGHT:
        player->x += player->speed;
        l0.position[0] = player->x;
        break;
    }

    if (GLFW_PRESS == action && GLFW_KEY_D == k) {
        debug = !debug;
    }

    // reload the maze
    if (GLFW_PRESS == action && GLFW_KEY_R == k) {
        printf("Reloading map...\n");

        Maze *old = maze;
        maze = malloc(sizeof(Maze));
        maze->line_width = 5;
        free(old);

        maze_load(&mf, &maze);
    }

    glLightfv(GL_POSITION, GL_SPECULAR, l0.position);
}


void c_mousebutton(GLFWwindow *w, int button, int action, int mods) {

    if (debug) {
        double x, y;
        glfwGetCursorPos(w, &x, &y);

        if (GLFW_MOUSE_BUTTON_1 == button && GLFW_PRESS == action) {
            printf("Mouse click at x:%f y:%f\n", x, y);
        }
    }
}

void c_mousepos(GLFWwindow *w, double xpos, double ypos) {

#ifdef MOUSE_OUTPUT
    printf("Mouse position x:%f y:%f\n", xpos, ypos);
#endif // MOUSE_OUTPUT
}
