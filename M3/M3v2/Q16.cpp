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
 * Exercise Q16 - Click-and-Drag Square
 * The square follows the cursor only while the left button is held.
 */
float squareX = 0.0f;
float squareY = 0.0f;
const float halfSize = 0.1f;
bool dragging = false;

void toOpenGLCoords(int x, int y, float& outX, float& outY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    outX = (2.0f * x / width) - 1.0f;
    outY = 1.0f - (2.0f * y / height);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(squareX - halfSize, squareY - halfSize);
        glVertex2f(squareX + halfSize, squareY - halfSize);
        glVertex2f(squareX + halfSize, squareY + halfSize);
        glVertex2f(squareX - halfSize, squareY + halfSize);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            dragging = true;
            toOpenGLCoords(x, y, squareX, squareY);
            glutPostRedisplay();
        } else if (state == GLUT_UP) {
            dragging = false;
        }
    }
}

void detectMotion(int x, int y) {
    if (dragging) {
        toOpenGLCoords(x, y, squareX, squareY);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Click-and-Drag Square");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(detectMotion);
    glutMainLoop();
    return 0;
}
