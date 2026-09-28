#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/* Q19 - Interleaved + Indexed Hexagon */
void hexagon() {
    GLfloat data[] = {-0.35f, 0.60f,  0, 1,    0.2f, 0.2f, 0.35f,  0.60f,  0, 1,    0.7f, 0.1f,
                      0.70f,  0,      0, 0.3f, 1,    0.2f, 0.35f,  -0.60f, 0, 0.1f, 0.8f, 1,
                      -0.35f, -0.60f, 0, 0.3f, 0.3f, 1,    -0.70f, 0,      0, 0.9f, 0.2f, 1};
    GLubyte indices[] = {0, 1, 2, 3, 4, 5};
    GLsizei stride = 6 * sizeof(GLfloat);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, stride, data);
    glColorPointer(3, GL_FLOAT, stride, data + 3);
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    hexagon();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q19 - Interleaved Indexed Hexagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
