#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

void display() { 

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // light gray background 

    glClear(GL_COLOR_BUFFER_BIT); 

  

    glColor3f(0.0f, 0.0f, 0.0f);  // black square outline

    glBegin(GL_LINE_LOOP); 

        glVertex2f(-0.4f, -0.4f); 

        glVertex2f(-0.4f,  0.4f); 

        glVertex2f( 0.4f,  0.4f); 

        glVertex2f( 0.4f, -0.4f); 

    glEnd(); 

  

    glFlush(); 

} 

  

int main(int argc, char** argv) { 

    glutInit(&argc, argv); 

    glutInitWindowSize(600, 600); 

    glutCreateWindow("Q05 - Square Outline on Gray Background"); 

    glutDisplayFunc(display); 

    glutMainLoop(); 

    return 0; 

} 