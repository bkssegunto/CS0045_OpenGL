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
 * Exercise Q18 - Entry + Idle Freeze Combo
 * Animate only while the pointer is inside the window.
 */
float squareX = -0.8f;
float speed = 0.003f;
bool inside = false;
const float halfSize = 0.1f;

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

void animateSquare();

void mouseEntry(int state) {
    if (state == GLUT_ENTERED) {
        inside = true;
        glutIdleFunc(animateSquare);
    } else if (state == GLUT_LEFT) {
        inside = false;
        glutIdleFunc(nullptr);
    }
}

void animateSquare() {
    if (inside) {
        squareX += speed;

        if (squareX > 0.9f || squareX < -0.9f) {
            speed = -speed;
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q18 - Entry and Idle Freeze Combo");
    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry);
    glutIdleFunc(nullptr);
    glutMainLoop();
    return 0;
}
