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
 * Exercise Q06 - Shape with Caption
 * Draw a filled triangle followed by a descriptive bitmap label.
 */
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.7f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.3f, -0.2f);
        glVertex2f( 0.3f, -0.2f);
        glVertex2f( 0.0f,  0.4f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.35f, -0.55f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "A filled triangle");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - Shape with Caption");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
