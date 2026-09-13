#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        float radius = (i % 2 == 0) ? 0.7f : 0.3f;
        float angle = 3.14159f / 2.0f + i * 3.14159f / 5.0f;
        glVertex2f(radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Star Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
