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
    glColor3f(1.0f, 0.0f, 0.0f);  // red triangle, left 

    glBegin(GL_POLYGON); 

        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.5f, 0.3f);
        glVertex2f(-0.2f, -0.3f);

    glEnd(); 

    glColor3f(0.0f, 0.0f, 1.0f);  // blue triangle, right

    glBegin(GL_POLYGON); 

        glVertex2f(0.2f, -0.3f);
        glVertex2f(0.5f, 0.3f); 
        glVertex2f(0.8f, -0.3f);

    glEnd(); 

    glFlush(); 

} 

int main(int argc, char** argv) { 

    glutInit(&argc, argv); 
    glutInitWindowSize(600, 600); 
    glutCreateWindow("Q07 - Two Triangles"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 

} 