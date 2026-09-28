#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q05 - GLint Vertex Data Type */
void integerTriangle() {
    GLint vertices[] = {0, 75, -70, -55, 70, -55};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.8f, 0.25f, 0.9f);
    glPushMatrix();
    glScalef(0.01f, 0.01f, 1);
    integerTriangle();
    glPopMatrix();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q05 - GLint Vertex Data Type");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
