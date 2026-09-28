#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
/* Q10 - Checkerboard Row via glDrawElements */
GLfloat vertices[] = {-0.8f, -0.3f, 0,    -0.8f, 0.3f, 0,     -0.4f, -0.3f, 0,    -0.4f,
                      0.3f,  0,     0.0f, -0.3f, 0,    0.0f,  0.3f,  0,     0.4f, -0.3f,
                      0,     0.4f,  0.3f, 0,     0.8f, -0.3f, 0,     0.8f,  0.3f, 0};
GLubyte quad0[] = {0, 2, 3, 1};
GLubyte quad1[] = {2, 4, 5, 3};
GLubyte quad2[] = {4, 6, 7, 5};
GLubyte quad3[] = {6, 8, 9, 7};

void checkerboard() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor3f(0, 0, 0);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad0);
    glColor3f(1, 1, 1);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad1);
    glColor3f(0, 0, 0);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad2);
    glColor3f(1, 1, 1);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    checkerboard();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 350);
    glutCreateWindow("Q10 - Checkerboard Row via glDrawElements");
    glClearColor(0.35f, 0.35f, 0.35f, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
