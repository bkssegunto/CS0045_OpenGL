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
 * Exercise Q05 - Mouse Button Text Color
 * A left click shows green text; a right click shows red text.
 */
int selectedButton = -1;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (selectedButton == GLUT_LEFT_BUTTON) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos2f(-0.35f, 0.0f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Left button text");
    } else if (selectedButton == GLUT_RIGHT_BUTTON) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.4f, 0.0f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Right button text");
    }

    glFlush();
}

void mouse(int button, int state, int, int) {
    if (state == GLUT_DOWN &&
        (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)) {
        selectedButton = button;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q05 - Mouse Button Text Color");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
