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

// Q17 - Thirty-Dash Ring
GLuint VBOid;

void initScene() {
   GLfloat vertices[30 * 2 * 3];
   for (int i = 0; i < 30; i++) {
      float angle = i * 6.2831853f / 30;
      float halfDash = 0.035f;
      int b = i * 6;
      vertices[b] = 0.7f * cosf(angle - halfDash);
      vertices[b + 1] = 0.7f * sinf(angle - halfDash);
      vertices[b + 2] = 0.0f;
      vertices[b + 3] = 0.7f * cosf(angle + halfDash);
      vertices[b + 4] = 0.7f * sinf(angle + halfDash);
      vertices[b + 5] = 0.0f;
   }
   glGenBuffers(1, &VBOid);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glLineWidth(4.0f);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.2f, 0.8f, 0.9f);
   glDrawArrays(GL_LINES, 0, 60);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}



void cleanup() {
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDeleteBuffers(1, &VBOid);
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
   glutCreateWindow("Q17 - Procedural 30-Dash Ring in One VBO");
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
