#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <cstdio>
#include <iostream>
using namespace std;

/*
 * Exercise Q15 - 30-Second Countdown Timer
 * Stop rescheduling the timer when the countdown reaches zero.
 */
int secondsRemaining = 30;
bool timeIsUp = false;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.25f, 0.0f);

    if (timeIsUp) {
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Time's up!");
    } else {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Time left: %d", secondsRemaining);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);
    }

    glFlush();
}

void tick(int) {
    if (secondsRemaining > 0) {
        secondsRemaining--;

        if (secondsRemaining == 0) {
            timeIsUp = true;
        }

        glutPostRedisplay();
    }

    if (secondsRemaining > 0) {
        glutTimerFunc(1000, tick, 0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Q15 - 30-Second Countdown Timer");
    glutDisplayFunc(display);
    glutTimerFunc(1000, tick, 0);
    glutMainLoop();
    return 0;
}
