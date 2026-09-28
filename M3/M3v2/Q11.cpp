#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
using namespace std;

/*
 * Exercise Q11 - Entry-Driven Background
 * Use glutEntryFunc to switch between light and dark gray.
 */
float backgroundGray = 0.2f;

void display() {
    glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouseEntry(int state) {
    if (state == GLUT_ENTERED) {
        backgroundGray = 0.8f;
    } else if (state == GLUT_LEFT) {
        backgroundGray = 0.2f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q11 - Entry-Driven Background");
    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry);
    glutMainLoop();
    return 0;
}
