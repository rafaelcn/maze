#include "maze.h"
#include "color.h"

#include <math.h>
#include <ctype.h>

void print_line_points(const Point *a, const Point *b) {

    // Draw points over the line extremes to help identify which is the
    // beginning and the end.

    glPushMatrix();
    glColor4f(1, 0.0, 0.0, 0.9);
    glPointSize(5);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {

        float x = a->x - 3*cos(i);
        float y = a->y - 3*sin(i);

        glVertex2d(x, y);
    }
    glEnd();

    glColor4f(0, 0, 1, 0.9);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {

        float x = b->x - 3*cos(i);
        float y = b->y - 3*sin(i);

        glVertex2d(x, y);
    }
    glEnd();
    glPopMatrix();
}

bool maze_load(MazeFile *mf, Maze **maze) {
    // Every line of the file will be a pair of coordinates of the lines to be
    // rendered
    if (mf) {
        mf->file = fopen(mf->path, "r");

        if (!mf->file) {
            fprintf(stderr, "File could not be read, exiting...");
            exit(1);
        }

        int fline = 0;

        Point a, b;

        while (fscanf(mf->file, "%f,%f,%f,%f", &a.x, &a.y, &b.x, &b.y) == 4) {

#ifdef DEBUG
            printf("Points read %f %f %f %f on line %d\n", a.x, a.y, b.x,
                   b.y, fline);
#endif // DEBUG

            (*maze)->lines[fline].a = a;
            (*maze)->lines[fline].b = b;
            ++fline;
        }

#ifdef DEBUG
        printf("\nLines read: %d\n", fline);
#endif // DEBUG

        fclose(mf->file);
        return true;
    }

    fclose(mf->file);
    return false;
}

void maze_draw(Maze *maze, bool debug) {

    glLineWidth(maze->line_width);


    for (int i = 0; i < MAZE_SIZE; i++) {
        glPushMatrix();
          glColor4f(black.r, black.g, black.b, black.a);
          glBegin(GL_LINES);
            glVertex2f(maze->lines[i].a.x, maze->lines[i].a.y);
            glVertex2f(maze->lines[i].b.x, maze->lines[i].b.y);
          glEnd();
        glPopMatrix();

        // for each line printed, if debug, print its extreme points
        if (debug) {
            print_line_points(&(maze->lines[i].a), &(maze->lines[i].b));
        }
    }
}

void maze_collision(Player *player, Maze *maze) {

    // check first, collision with the boundaries of the maze.

    if (player->x <= 6+player->width/2) {
        player->x = 6+player->width/2;
    }

    if (player->x > 634-player->width/2) {
        player->x = 634-player->width/2;

        if (player->y-player->height/2 > 6 &&
            player->y+player->height/2 < 50) {
            printf("Você encontrou o caminho!\n");
        }
    }

    if (player->y <= 6+player->width/2) {
        player->y = 6+player->width/2;
    }

    if (player->y > 470-player->width/2) {
        player->y = 470-player->width/2;
    }

    // Algorithm: Measure the distance to each of the lines in a radius of the
    // player, if that distance is less than zero and it is intersecting a
    // force is added in the opposite direction
    for (int i = 0; i < MAZE_SIZE; i++) {
        Point a = maze->lines[i].a;
        Point b = maze->lines[i].b;

        double d = fabs((b.y - a.y)*player->x - (b.x - a.x)*player->y +
                        b.x*a.y - b.y*a.x);

        d = d/sqrt(pow(b.y-a.y, 2)+pow(b.x-a.x, 2));


        // Only test lines that are 10 pixels closer
        if (d < 10) {
            int line_height = b.y-a.y;
            // player box collision
            int pw = player->width/2;
            int ph = player->height/2;

            if (a.x < player->x + pw &&
                a.x + maze->line_width > player->x &&
                a.y < player->y + ph &&
                a.y + line_height > player->y) {
                player->x -= player->speed*1.5;
            }
        }
    }
}
