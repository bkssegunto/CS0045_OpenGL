#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
/* Q15 - Fully Array-Based Scene */
GLfloat sunVertices[] = {0.6f, 0.58f, 0,     0.6f, 0.78f, 0,     0.78f, 0.68f, 0,     0.78f, 0.48f,
                         0,    0.6f,  0.38f, 0,    0.42f, 0.48f, 0,     0.42f, 0.68f, 0};
GLubyte sunIndices[] = {0, 1, 2, 3, 4, 5, 6, 1};
GLfloat mountainVertices[] = {-0.95f,
                              -0.55f,
                              0,
                              -0.35f,
                              0.45f,
                              0,
                              0.05f,
                              -0.55f,
                              0,
                              -0.15f,
                              -0.55f,
                              0,
                              0.35f,
                              0.25f,
                              0,
                              0.85f,
                              -0.55f,
                              0};
GLfloat groundVertices[] = {-1, -0.55f, 0, 1, -0.55f, 0, 1, -1, 0, -1, -1, 0};

void sun() {
    glColor3f(1, 0.85f, 0.1f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, sunVertices);
    glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_BYTE, sunIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void mountains() {
    glColor3f(0.45f, 0.3f, 0.2f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, mountainVertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ground() {
    glColor3f(0.2f, 0.65f, 0.25f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    sun();
    mountains();
    ground();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q15 - Fully Array-Based Scene");
    glClearColor(0.35f, 0.65f, 0.95f, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
