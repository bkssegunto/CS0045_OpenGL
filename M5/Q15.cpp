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

// Q15 - Bouncing Quad
GLuint VBOid;
float offset = 0.0f;
float direction = 1.0f;

void initScene() {
   GLfloat vertices[] = {
      -0.3f, -0.2f, 0.0f,
       0.3f, -0.2f, 0.0f,
       0.3f,  0.2f, 0.0f,
      -0.3f,  0.2f, 0.0f
   };
   glGenBuffers(1, &VBOid);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.16f, 0.72f, 0.08f);
   glDrawArrays(GL_QUADS, 0, 4);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}

void animateStep(int) {
   float nextOffset = offset + direction * 0.02f;
   if (nextOffset >= 0.5f) {
      nextOffset = 0.5f;
      direction = -1.0f;
   } else if (nextOffset <= -0.5f) {
      nextOffset = -0.5f;
      direction = 1.0f;
   }
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
   if (mapped) {
      float dy = nextOffset - offset;
      for (int i = 0; i < 4; i++) mapped[i * 3 + 1] += dy;
      glUnmapBuffer(GL_ARRAY_BUFFER);
      offset = nextOffset;
   }
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glutPostRedisplay();
   glutTimerFunc(30, animateStep, 0);
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
   glutCreateWindow("Q15 - Continuous Bouncing glMapBuffer Animation");
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
   glutTimerFunc(30, animateStep, 0);
   glutMainLoop();
   return 0;
}
