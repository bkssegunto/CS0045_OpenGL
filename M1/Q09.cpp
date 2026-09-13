#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    const int size = 4;
    const float cellSize = 0.4f;
    const float start = -0.8f;

    // Outer loop: rows
    for (int row = 0; row < size; row++) {
        // Inner loop: columns
        for (int col = 0; col < size; col++) {
            float x1 = start + col * cellSize;
            float y1 = start + row * cellSize;
            float x2 = x1 + cellSize;
            float y2 = y1 + cellSize;

            // Alternate between black and white.
            if ((row + col) % 2 == 0) {
                glColor3f(0.0f, 0.0f, 0.0f);
            } else {
                glColor3f(1.0f, 1.0f, 1.0f);
            }

            glBegin(GL_QUADS);
                glVertex2f(x1, y1); // bottom-left
                glVertex2f(x2, y1); // bottom-right
                glVertex2f(x2, y2); // top-right
                glVertex2f(x1, y2); // top-left
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - 4x4 Checkerboard");

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}