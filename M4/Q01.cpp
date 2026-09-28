#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q01 - Vertex Array X-Pattern Points */
void xPattern() {
    GLfloat vertices[] = {
        -0.6f, 0.6f, 0, 0.6f, 0.6f, 0, 0.0f, 0.0f, 0, -0.6f, -0.6f, 0, 0.6f, -0.6f, 0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glPointSize(18.0f);
    glDrawArrays(GL_POINTS, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.4f, 0.2f);
    xPattern();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q01 - Vertex Array X-Pattern Points");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
