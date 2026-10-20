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

// Q18 - Interleaved Indexed Hexagon
GLuint VBOid, indexVBO;

void initScene() {
   GLfloat vertices[] = {
       0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
       0.35f, 0.6062f, 0.0f, 1.0f, 1.0f, 0.0f,
      -0.35f, 0.6062f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.7f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -0.35f, -0.6062f, 0.0f, 0.0f, 0.0f, 1.0f,
       0.35f, -0.6062f, 0.0f, 1.0f, 0.0f, 1.0f
   };
   GLubyte indices[] = { 0, 1, 2, 3, 4, 5 };
   glGenBuffers(1, &VBOid);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glGenBuffers(1, &indexVBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   GLsizei stride = 6 * sizeof(GLfloat);
   glVertexPointer(3, GL_FLOAT, stride, 0);
   glColorPointer(3, GL_FLOAT, stride, (void*)(3 * sizeof(GLfloat)));
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
   glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}



void cleanup() {
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDeleteBuffers(1, &VBOid);
   glDeleteBuffers(1, &indexVBO);
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
   glutCreateWindow("Q18 - Interleaved + Indexed Hexagon");
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
