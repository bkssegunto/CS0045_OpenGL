#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
/* Q13 - Pinwheel via glDrawElements */
GLfloat vertices[] = {0,     0,     0, -0.5f,  0.10f,  0, -0.5f,  -0.10f, 0,
                      0.5f,  0.10f, 0, 0.5f,   -0.10f, 0, -0.10f, 0.5f,   0,
                      0.10f, 0.5f,  0, -0.10f, -0.5f,  0, 0.10f,  -0.5f,  0};
GLfloat colors[] = {1, 1, 1, 1, 0, 0, 0, 1, 0,    0, 0,    1, 1, 1,
                    0, 1, 0, 1, 0, 1, 1, 1, 0.5f, 0, 0.5f, 0, 1};
GLubyte indices[] = {0, 1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8};

void pinwheel() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    pinwheel();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q13 - Pinwheel via glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
