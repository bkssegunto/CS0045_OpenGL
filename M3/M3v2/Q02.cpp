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
 * Exercise Q02 - Font Size Comparison
 * Based on Ex02: display one phrase using three bitmap fonts.
 */
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(-0.5f, 0.45f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_10, "Hello World");

    glRasterPos2f(-0.5f, 0.0f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Hello World");

    glRasterPos2f(-0.5f, -0.45f);
    drawBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Hello World");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q02 - Font Size Comparison");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
