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

// Q04 - Full Cleanup Checklist
GLuint VBOid;

void initScene() {
   GLfloat vertices[] = {
       0.0f,  0.5f, 0.0f,
      -0.5f, -0.4f, 0.0f,
       0.5f, -0.4f, 0.0f
   };
   glGenBuffers(1, &VBOid);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.16f, 0.72f, 0.08f);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}



void cleanup() {
   // Undo the enabled vertex array state.
   glDisableClientState(GL_VERTEX_ARRAY);
   // Undo the binding to the vertex buffer.
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   // Release the GPU buffer created by glGenBuffers.
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
   glutCreateWindow("Q04 - Full Cleanup Checklist");
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
