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
 * Exercise Q14 - Keyboard + Mouse Combo
 * Use w/s to move a square vertically and a mouse click to reset it.
 */
float squareY = 0.0f;
const float halfSize = 0.1f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2f(-halfSize, squareY - halfSize);
        glVertex2f( halfSize, squareY - halfSize);
        glVertex2f( halfSize, squareY + halfSize);
        glVertex2f(-halfSize, squareY + halfSize);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key == 'w') {
        squareY += 0.05f;
    } else if (key == 's') {
        squareY -= 0.05f;
    } else {
        return;
    }

    glutPostRedisplay();
}

void mouse(int, int state, int, int) {
    if (state == GLUT_DOWN) {
        squareY = 0.0f;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q14 - Keyboard and Mouse Combo");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
