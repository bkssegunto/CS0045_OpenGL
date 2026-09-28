#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
#include <cmath>
/* Q20 - Capstone: Procedural Flower Scene */
const int petals = 12, discSegments = 40;
GLfloat petalVertices[petals * 9], petalColors[petals * 9];
GLfloat discVertices[(discSegments + 2) * 3];
GLubyte discIndices[discSegments + 2];
GLfloat groundVertices[] = {-1, -0.65f, 0, 1, -0.65f, 0, 1, -1, 0, -1, -1, 0};

void buildFlower() {
    const GLfloat pi = 3.14159265f, centerY = 0.15f;
    for (int i = 0; i < petals; ++i) {
        GLfloat a = 2 * pi * i / petals, spread = pi / petals;
        int p = i * 9;
        petalVertices[p] = 0;
        petalVertices[p + 1] = centerY;
        petalVertices[p + 2] = 0;
        petalVertices[p + 3] = 0.65f * cos(a - spread);
        petalVertices[p + 4] = centerY + 0.65f * sin(a - spread);
        petalVertices[p + 5] = 0;
        petalVertices[p + 6] = 0.65f * cos(a + spread);
        petalVertices[p + 7] = centerY + 0.65f * sin(a + spread);
        petalVertices[p + 8] = 0;
        GLfloat r = (cos(a) + 1) / 2, g = (sin(a) + 1) / 2, b = 0.75f;
        for (int v = 0; v < 3; ++v) {
            petalColors[p + v * 3] = r;
            petalColors[p + v * 3 + 1] = g;
            petalColors[p + v * 3 + 2] = b;
        }
    }
    discVertices[0] = 0;
    discVertices[1] = centerY;
    discVertices[2] = 0;
    discIndices[0] = 0;
    for (int i = 0; i <= discSegments; ++i) {
        GLfloat a = 2 * pi * i / discSegments;
        int p = (i + 1) * 3;
        discVertices[p] = 0.20f * cos(a);
        discVertices[p + 1] = centerY + 0.20f * sin(a);
        discVertices[p + 2] = 0;
        discIndices[i + 1] = (GLubyte)(i + 1);
    }
}

void drawPetals() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, petalVertices);
    glColorPointer(3, GL_FLOAT, 0, petalColors);
    glDrawArrays(GL_TRIANGLES, 0, petals * 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drawDisc() {
    glColor3f(1, 0.75f, 0.05f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, discVertices);
    glDrawElements(GL_TRIANGLE_FAN, discSegments + 2, GL_UNSIGNED_BYTE, discIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGround() {
    glColor3f(0.2f, 0.65f, 0.25f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPetals();
    drawDisc();
    drawGround();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 650);
    glutCreateWindow("Q20 - Procedural Flower Scene");
    glClearColor(0.4f, 0.75f, 1, 1);
    buildFlower();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
