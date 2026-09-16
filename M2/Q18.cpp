#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_FLAT);

    const int pairCount = 6;
    float x[pairCount] = {-0.9f, -0.55f, -0.2f, 0.15f, 0.5f, 0.85f};

    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < pairCount; i++) {
            if (i % 2 == 0)
                glColor3f(1.0f, 0.3f, 0.2f);
            else
                glColor3f(0.2f, 0.7f, 1.0f);

            glVertex2f(x[i], -0.35f);
            glVertex2f(x[i],  0.35f);
        }
    glEnd();

    glShadeModel(GL_SMOOTH);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q18 - Alternating-Color Ribbon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
