#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <cstdio>
#include <iostream>
using namespace std;

/*
 * Exercise Q19 - HUD Score with Color Milestones
 * Add one point per click and change color at every multiple of five.
 */
int score = 0;
float shapeColor[3] = {1.0f, 0.2f, 0.2f};

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(shapeColor[0], shapeColor[1], shapeColor[2]);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f( 0.3f, -0.3f);
        glVertex2f( 0.3f,  0.3f);
        glVertex2f(-0.3f,  0.3f);
    glEnd();

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Score: %d", score);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f, 0.85f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glFlush();
}

void updateMilestoneColor() {
    int stage = (score / 5) % 3;

    if (stage == 0) {
        shapeColor[0] = 1.0f;
        shapeColor[1] = 0.2f;
        shapeColor[2] = 0.2f;
    } else if (stage == 1) {
        shapeColor[0] = 0.2f;
        shapeColor[1] = 1.0f;
        shapeColor[2] = 0.2f;
    } else {
        shapeColor[0] = 0.2f;
        shapeColor[1] = 0.4f;
        shapeColor[2] = 1.0f;
    }
}

void mouse(int button, int state, int, int) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        score++;

        if (score % 5 == 0) {
            updateMilestoneColor();
        }

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - HUD Score with Color Milestones");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
