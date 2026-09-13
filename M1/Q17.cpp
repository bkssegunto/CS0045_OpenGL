#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

int active = 0;

void circle(float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, y);
        for (int i = 0; i <= 40; i++) {
            float angle = i * 2.0f * 3.14159f / 40;
            glVertex2f(0.18f * cosf(angle), y + 0.18f * sinf(angle));
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, -0.8f);
        glVertex2f( 0.3f, -0.8f);
        glVertex2f( 0.3f,  0.8f);
        glVertex2f(-0.3f,  0.8f);
    glEnd();

    circle( 0.5f, active == 0 ? 1.0f : 0.2f, 0.0f, 0.0f);
    circle( 0.0f, active == 1 ? 1.0f : 0.2f,
                   active == 1 ? 1.0f : 0.2f, 0.0f);
    circle(-0.5f, 0.0f, active == 2 ? 1.0f : 0.2f, 0.0f);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n') {
        active = (active + 1) % 3;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 600);
    glutCreateWindow("Q17 - Traffic Light Simulator");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}