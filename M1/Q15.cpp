#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

float squareX = 0.0f;
float squareY = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(squareX - 0.1f, squareY - 0.1f);
        glVertex2f(squareX + 0.1f, squareY - 0.1f);
        glVertex2f(squareX + 0.1f, squareY + 0.1f);
        glVertex2f(squareX - 0.1f, squareY + 0.1f);
    glEnd();

    glFlush();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  squareX -= 0.05f;
    if (key == GLUT_KEY_RIGHT) squareX += 0.05f;
    if (key == GLUT_KEY_UP)    squareY += 0.05f;
    if (key == GLUT_KEY_DOWN)  squareY -= 0.05f;

    if (squareX < -0.9f) squareX = -0.9f;
    if (squareX >  0.9f) squareX =  0.9f;
    if (squareY < -0.9f) squareY = -0.9f;
    if (squareY >  0.9f) squareY =  0.9f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Move a Square with Arrow Keys");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}