#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
using namespace std;

/*
 * Exercise Q03 - Custom Window Setup
 * Configure size, position, and title before creating the window.
 */
void display() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("My Custom Window");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
