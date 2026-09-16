#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void drawCircle() {
    const int segments = 40;
    const float PI = 3.14159265f;
    glColor3f(1.0f, 0.3f, 0.6f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.35f);
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 2.0f * PI;
            glVertex2f(0.3f * cosf(angle),
                       0.35f + 0.3f * sinf(angle));
        }
    glEnd();
}

void drawBase() {
    glColor3f(0.8f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.22f, -0.55f);
        glVertex2f( 0.22f, -0.55f);
        glVertex2f( 0.22f,  0.10f);
        glVertex2f(-0.22f,  0.10f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBase();
    drawCircle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Fan and Quad Composition");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
