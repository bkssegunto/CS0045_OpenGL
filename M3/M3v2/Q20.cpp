#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

/*
 * Exercise Q20 - Interactive Text Placer
 * Combine click placement, passive-motion coordinates, and idle pulsing.
 */
float markerX = 0.0f;
float markerY = 0.0f;
float hoverX = 0.0f;
float hoverY = 0.0f;
float pulseAngle = 0.0f;

const float baseSize = 0.08f;
const float pulseAmplitude = 0.02f;
const float twoPi = 6.2831853f;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void toGL(int x, int y, float& outX, float& outY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    outX = (2.0f * x / width) - 1.0f;
    outY = 1.0f - (2.0f * y / height);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float markerSize = baseSize + pulseAmplitude * sin(pulseAngle);

    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++) {
        float angle = twoPi * i / 40.0f;
        glVertex2f(markerX + cos(angle) * markerSize,
                   markerY + sin(angle) * markerSize);
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(markerX - 0.07f, markerY - 0.15f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Marker");

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Mouse: (%.2f, %.2f)", hoverX, hoverY);

    glRasterPos2f(-0.9f, 0.85f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toGL(x, y, markerX, markerY);
        glutPostRedisplay();
    }
}

void detectPassiveMotion(int x, int y) {
    toGL(x, y, hoverX, hoverY);
    glutPostRedisplay();
}

void animateMarker() {
    pulseAngle += 0.03f;

    if (pulseAngle > twoPi) {
        pulseAngle -= twoPi;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q20 - Interactive Text Placer");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(detectPassiveMotion);
    glutIdleFunc(animateMarker);
    glutMainLoop();
    return 0;
}
