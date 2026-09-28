#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q02 - Filled Hexagon via Vertex Array */
void hexagon() {
    GLfloat vertices[] = {-0.35f,
                          0.60f,
                          0,
                          0.35f,
                          0.60f,
                          0,
                          0.70f,
                          0,
                          0,
                          0.35f,
                          -0.60f,
                          0,
                          -0.35f,
                          -0.60f,
                          0,
                          -0.70f,
                          0,
                          0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_POLYGON, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 0.9f);
    hexagon();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q02 - Filled Hexagon via Vertex Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
