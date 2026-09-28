#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q04 - Square Plus Outline, Same Array */
void squareWithOutline() {
    GLfloat vertices[] = {-0.55f, -0.55f, 0, 0.55f, -0.55f, 0, 0.55f, 0.55f, 0, -0.55f, 0.55f, 0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor3f(0.15f, 0.55f, 0.95f);
    glDrawArrays(GL_QUADS, 0, 4);
    glColor3f(1, 1, 1);
    glLineWidth(4.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    squareWithOutline();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q04 - Square Plus Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
