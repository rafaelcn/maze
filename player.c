#include "player.h"
#include "color.h"

void player_draw(Player *player, bool debug) {

    GLdouble pw = player->width;
    GLdouble ph = player->height;

    glPointSize(8);

    // Head
    /*glPushMatrix();
    glColor4f(light_blue.r, light_blue.g, light_blue.b, light_blue.a);
    glBegin(GL_POINTS);
    glVertex2d(player->x-pw/2, player->y-ph);
    glEnd();
    */
    /*glLineWidth(2);

    // Body
    glBegin(GL_LINES);
    glVertex2d(player->x-pw/2, player->y-ph);
    glVertex2d(player->x-pw/2, player->y-ph/2);
    glEnd();

    // First leg
    glBegin(GL_LINES);
    glVertex2d(player->x-pw/2, player->y-ph/2);
    glVertex2d(player->x-pw/2-3, player->y+2);
    glEnd();

    // Second leg
    glBegin(GL_LINES);
    glVertex2d(player->x-pw/2, player->y-ph/2);
    glVertex2d(player->x-pw/2+3, player->y+2);
    glEnd();

    // Arm
    glBegin(GL_LINES);
    glVertex2d(player->x-pw/2-10, player->y-ph/2);
    glVertex2d(player->x-pw/2+10, player->y-ph/2);
    glEnd();

    glPopMatrix();*/

    glPointSize(player->height);

    glBegin(GL_POINTS);
    glVertex2d(player->x, player->y);
    glEnd();

    if (debug) {
        glPushMatrix();
        if (debug) {
            glBegin(GL_LINES);
            for (int i = 0; i < 360; i++) {

                float x = player->x - 35*cos(i);
                float y = player->y - 35*sin(i);

                glVertex2f(x, y);
            }
            glEnd();
        }
        glPopMatrix();
    }
}
