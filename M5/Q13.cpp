#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// Q13 - ESC Cleanup of Two VBOs
GLuint leftVBO, rightVBO;

void initScene() {
   GLfloat leftVertices[] = {
      -0.55f, 0.5f, 0.0f, -0.9f, -0.4f, 0.0f, -0.2f, -0.4f, 0.0f
   };
   GLfloat rightVertices[] = {
       0.55f, 0.5f, 0.0f, 0.2f, -0.4f, 0.0f, 0.9f, -0.4f, 0.0f
   };
   glGenBuffers(1, &leftVBO);
   glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(leftVertices), leftVertices, GL_STATIC_DRAW);
   glGenBuffers(1, &rightVBO);
   glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(rightVertices), rightVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(1.0f, 0.4f, 0.1f);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.1f, 0.4f, 1.0f);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}



void cleanup() {
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDeleteBuffers(1, &leftVBO);
   glDeleteBuffers(1, &rightVBO);
}

void monitorKeyboard(unsigned char key, int, int) {
   if (key == 27) {
      cleanup();
      exit(0);
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Q13 - ESC Cleanup of Two VBOs");
   glutDisplayFunc(display);
   glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
   GLenum err = glewInit();
   if (err != GLEW_OK) {
      cerr << glewGetErrorString(err) << endl;
      return 1;
   }
#endif
   initScene();
   glutMainLoop();
   return 0;
}
