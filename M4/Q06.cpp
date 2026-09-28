#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q06 - glDrawElements Index Order */
void indexedTriangle() {
    GLfloat vertices[] = {-0.7f, -0.55f, 0, 0.7f, -0.55f, 0, 0, 0.70f, 0};
    GLubyte indices[] = {2, 0, 1}; // Visit top, bottom-left, bottom-right.
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.3f, 0.9f, 0.4f);
    indexedTriangle();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - glDrawElements Index Order");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
