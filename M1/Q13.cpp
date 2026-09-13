#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

void drawRect(float x0, float y0, float x1, float y1) {
    glBegin(GL_POLYGON);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 1.0f);

    drawRect(-0.5f, -0.7f, -0.3f, 0.7f);
    drawRect(-0.3f,  0.5f,  0.5f, 0.7f);
    drawRect(-0.3f,  0.0f,  0.3f, 0.2f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q13 - Letter F From Rectangles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}