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
 * Exercise Q08 - Clamped Keyboard Movement
 * Move the square with a and d while keeping its edges on-screen.
 */
float squareX = 0.0f;
const float halfSize = 0.1f;
const float step = 0.05f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glVertex2f(squareX - halfSize, -halfSize);
        glVertex2f(squareX + halfSize, -halfSize);
        glVertex2f(squareX + halfSize,  halfSize);
        glVertex2f(squareX - halfSize,  halfSize);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'a') {
        squareX -= step;
    } else if (key == 'd') {
        squareX += step;
    } else {
        return;
    }

    const float leftLimit = -1.0f + halfSize;
    const float rightLimit = 1.0f - halfSize;

    if (squareX < leftLimit) {
        squareX = leftLimit;
    }

    if (squareX > rightLimit) {
        squareX = rightLimit;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q08 - Clamped Keyboard Movement");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
