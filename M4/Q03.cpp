#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q03 - Two Lines, One Array */
void twoLines() {
    GLfloat vertices[] = {-0.8f, 0.45f, 0, 0.8f, 0.45f, 0, -0.8f, -0.45f, 0, 0.8f, -0.45f, 0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.8f, 0);
    twoLines();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q03 - Two Lines, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
