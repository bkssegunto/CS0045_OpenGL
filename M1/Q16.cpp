#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

float ballX = 0.0f, ballY = 0.0f;
float dx = 0.01f, dy = 0.008f;
const float radius = 0.1f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(ballX, ballY);
        for (int i = 0; i <= 40; i++) {
            float angle = i * 2.0f * 3.14159f / 40;
            glVertex2f(ballX + radius * cosf(angle),
                       ballY + radius * sinf(angle));
        }
    glEnd();

    glFlush();
}

void idle() {
    ballX += dx;
    ballY += dy;

    if (ballX + radius >= 1.0f || ballX - radius <= -1.0f) dx = -dx;
    if (ballY + radius >= 1.0f || ballY - radius <= -1.0f) dy = -dy;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Bouncing Ball");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}