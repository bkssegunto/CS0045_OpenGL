#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

void drawCircle(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 60; i++) {
        float angle = i * 2.0f * 3.14159f / 60;
        glVertex2f(radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(0.2f, 1.0f, 0.0f, 0.0f);
    drawCircle(0.4f, 0.0f, 1.0f, 0.0f);
    drawCircle(0.6f, 0.0f, 0.0f, 1.0f);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Concentric Circles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}