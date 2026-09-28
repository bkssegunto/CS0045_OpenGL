#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
/* Q18 - Keyboard-Switched Vertex Arrays */
GLfloat triangle[] = {0, 0.75f, 0, -0.7f, -0.55f, 0, 0.7f, -0.55f, 0};
GLfloat quad[] = {-0.6f, -0.6f, 0, 0.6f, -0.6f, 0, 0.6f, 0.6f, 0, -0.6f, 0.6f, 0};
GLfloat pentagon[] = {
    0, 0.75f, 0, -0.71f, 0.23f, 0, -0.44f, -0.61f, 0, 0.44f, -0.61f, 0, 0.71f, 0.23f, 0};
int selection = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    if (selection == 1) {
        glColor3f(1, 0.3f, 0.2f);
        glVertexPointer(3, GL_FLOAT, 0, triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    } else if (selection == 2) {
        glColor3f(0.2f, 0.7f, 1);
        glVertexPointer(3, GL_FLOAT, 0, quad);
        glDrawArrays(GL_QUADS, 0, 4);
    } else {
        glColor3f(0.4f, 0.9f, 0.3f);
        glVertexPointer(3, GL_FLOAT, 0, pentagon);
        glDrawArrays(GL_POLYGON, 0, 5);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

void keyboard(unsigned char key, int, int) {
    if (key >= '1' && key <= '3') {
        selection = key - '0';
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q18 - Keyboard-Switched Vertex Arrays");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
