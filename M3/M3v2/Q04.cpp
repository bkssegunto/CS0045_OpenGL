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
 * Exercise Q04 - Keyboard Background Color Switch
 * Press r, g, or b to select the window's clear color.
 */
float backgroundRed = 0.0f;
float backgroundGreen = 0.0f;
float backgroundBlue = 0.0f;

void display() {
    glClearColor(backgroundRed, backgroundGreen, backgroundBlue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'r':
            backgroundRed = 1.0f;
            backgroundGreen = 0.0f;
            backgroundBlue = 0.0f;
            break;
        case 'g':
            backgroundRed = 0.0f;
            backgroundGreen = 1.0f;
            backgroundBlue = 0.0f;
            break;
        case 'b':
            backgroundRed = 0.0f;
            backgroundGreen = 0.0f;
            backgroundBlue = 1.0f;
            break;
        default:
            return;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q04 - Keyboard Background Color Switch");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
