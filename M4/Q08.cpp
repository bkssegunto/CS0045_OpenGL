#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q08 - Three Triangles, One Array */
void threeTriangles() {
    GLfloat vertices[] = {-0.9f,  -0.45f, 0, -0.65f, 0.35f, 0, -0.4f, -0.45f, 0,
                          -0.25f, -0.45f, 0, 0,      0.35f, 0, 0.25f, -0.45f, 0,
                          0.4f,   -0.45f, 0, 0.65f,  0.35f, 0, 0.9f,  -0.45f, 0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.35f, 0.2f);
    threeTriangles();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q08 - Three Triangles, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
