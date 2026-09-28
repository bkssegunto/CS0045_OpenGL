#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
#include <cmath>
/* Q11 - Procedural Shaded Circle */
const int segments = 60;
GLfloat vertices[(segments + 2) * 3];
GLfloat colors[(segments + 2) * 3];

void buildCircle() {
    const GLfloat pi = 3.14159265f;
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;
    colors[0] = 1;
    colors[1] = 1;
    colors[2] = 1;
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = 2 * pi * i / segments;
        int p = (i + 1) * 3;
        vertices[p] = 0.75f * cos(angle);
        vertices[p + 1] = 0.75f * sin(angle);
        vertices[p + 2] = 0;
        colors[p] = (cos(angle) + 1) / 2;
        colors[p + 1] = (sin(angle) + 1) / 2;
        colors[p + 2] = (GLfloat)i / segments;
    }
}

void circle() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    circle();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q11 - Procedural Shaded Circle");
    buildCircle();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
