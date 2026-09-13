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

    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.3f);
        glVertex2f(-1.0f, -0.3f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.6f, 0.5f);
        for (int i = 0; i <= 40; i++) {
            float angle = i * 2.0f * 3.14159f / 40;
            glVertex2f(0.6f + 0.18f * cosf(angle),
                       0.5f + 0.18f * sinf(angle));
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q14 - Simple Landscape");
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}