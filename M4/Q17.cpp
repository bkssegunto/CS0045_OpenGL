#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
#include <cmath>
/* Q17 - Procedural Gear Shape */
const int teeth = 16, ringPoints = teeth * 2;
GLfloat vertices[(ringPoints + 1) * 3];
GLubyte evenIndices[(ringPoints / 2) * 3], oddIndices[(ringPoints / 2) * 3];

void buildGear() {
    const GLfloat pi = 3.14159265f;
    vertices[0] = vertices[1] = vertices[2] = 0;
    for (int i = 0; i < ringPoints; ++i) {
        GLfloat angle = 2 * pi * i / ringPoints;
        GLfloat radius = (i % 2 == 0) ? 0.82f : 0.62f;
        vertices[(i + 1) * 3] = radius * cos(angle);
        vertices[(i + 1) * 3 + 1] = radius * sin(angle);
        vertices[(i + 1) * 3 + 2] = 0;
    }
    int e = 0, o = 0;
    for (int i = 0; i < ringPoints; ++i) {
        GLubyte *list = (i % 2 == 0) ? evenIndices : oddIndices;
        int &p = (i % 2 == 0) ? e : o;
        list[p++] = 0;
        list[p++] = (GLubyte)(i + 1);
        list[p++] = (GLubyte)((i + 1) % ringPoints + 1);
    }
}

void gear() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor3f(1, 0.55f, 0.05f);
    glDrawElements(GL_TRIANGLES, (ringPoints / 2) * 3, GL_UNSIGNED_BYTE, evenIndices);
    glColor3f(0.85f, 0.15f, 0.1f);
    glDrawElements(GL_TRIANGLES, (ringPoints / 2) * 3, GL_UNSIGNED_BYTE, oddIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    gear();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Procedural Gear Shape");
    buildGear();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
