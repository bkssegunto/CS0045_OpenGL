#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    const int segments = 7;
    const float PI = 3.14159265f;

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * PI;
            glVertex2f(0.7f * cosf(angle), 0.7f * sinf(angle));
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Half-Circle Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
