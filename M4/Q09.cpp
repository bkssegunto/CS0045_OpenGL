#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q09 - Indexed Triangle Fan Pentagon */
void pentagonFan() {
    GLfloat vertices[] = {0,
                          0,
                          0,
                          0,
                          0.75f,
                          0,
                          -0.71f,
                          0.23f,
                          0,
                          -0.44f,
                          -0.61f,
                          0,
                          0.44f,
                          -0.61f,
                          0,
                          0.71f,
                          0.23f,
                          0};
    GLubyte indices[] = {0, 1, 2, 3, 4, 5, 1};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.55f, 0.1f);
    pentagonFan();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q09 - Indexed Triangle Fan Pentagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
