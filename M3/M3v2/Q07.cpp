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
 * Exercise Q07 - Stroke Font Practice
 * Draw "HI" as scalable vector text using GLUT_STROKE_ROMAN.
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 1.0f);
    glLineWidth(2.0f);

    glPushMatrix();
    glTranslatef(-0.4f, -0.2f, 0.0f);
    glScalef(0.003f, 0.003f, 1.0f);

    const char* message = "HI";
    for (const char* c = message; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }

    glPopMatrix();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q07 - Stroke Font Practice");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
