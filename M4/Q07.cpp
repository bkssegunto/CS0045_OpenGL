#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q07 - Vertex + Color Array Triangle */
void coloredTriangle() {
    GLfloat vertices[] = {0, 0.75f, 0, -0.75f, -0.55f, 0, 0.75f, -0.55f, 0};
    GLfloat colors[] = {1, 0.3f, 0.1f, 0.1f, 1, 0.4f, 0.2f, 0.4f, 1};
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    coloredTriangle();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q07 - Vertex and Color Array Triangle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
