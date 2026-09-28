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
 * Exercise Q17 - Mouse-Controlled Stopwatch
 * Left click starts or resumes; right click pauses.
 */
int elapsedSeconds = 0;
bool running = false;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    char buffer[48];
    snprintf(buffer, sizeof(buffer), "Elapsed: %d seconds", elapsedSeconds);

    glRasterPos2f(-0.35f, 0.0f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);
    glFlush();
}

void mouse(int button, int state, int, int) {
    if (state != GLUT_DOWN) {
        return;
    }

    if (button == GLUT_LEFT_BUTTON) {
        running = true;
    } else if (button == GLUT_RIGHT_BUTTON) {
        running = false;
    }
}

void tick(int) {
    if (running) {
        elapsedSeconds++;
        glutPostRedisplay();
    }

    glutTimerFunc(1000, tick, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Q17 - Mouse-Controlled Stopwatch");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(1000, tick, 0);
    glutMainLoop();
    return 0;
}
