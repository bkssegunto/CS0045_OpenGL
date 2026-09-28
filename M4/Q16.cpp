#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
/* Q16 - glDrawArrays vs. glDrawElements, Side by Side */
// Left quad: 18 floats = 6 vertices, including 2 duplicated positions.
GLfloat drawArrayQuad[] = {-0.9f,
                           -0.5f,
                           0,
                           -0.1f,
                           -0.5f,
                           0,
                           -0.1f,
                           0.5f,
                           0,
                           -0.9f,
                           -0.5f,
                           0,
                           -0.1f,
                           0.5f,
                           0,
                           -0.9f,
                           0.5f,
                           0};
// Right quad: 12 floats = 4 unique vertices plus 6 indices.
GLfloat indexedQuad[] = {0.1f, -0.5f, 0, 0.9f, -0.5f, 0, 0.9f, 0.5f, 0, 0.1f, 0.5f, 0};
GLubyte indices[] = {0, 1, 2, 0, 2, 3};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.9f, 0.25f, 0.2f);
    glVertexPointer(3, GL_FLOAT, 0, drawArrayQuad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glColor3f(0.2f, 0.55f, 1);
    glVertexPointer(3, GL_FLOAT, 0, indexedQuad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Q16 - DrawArrays vs DrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
