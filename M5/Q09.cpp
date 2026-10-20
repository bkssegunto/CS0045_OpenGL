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

// Q09 - Two-VBO Colored Triangle
GLuint positionVBO, colorVBO;

void initScene() {
   GLfloat vertices[] = {
       0.0f,  0.5f, 0.0f,
      -0.5f, -0.4f, 0.0f,
       0.5f, -0.4f, 0.0f
   };
   GLfloat colors[] = {
      1.0f, 0.2f, 0.2f,
      0.2f, 1.0f, 0.2f,
      0.2f, 0.2f, 1.0f
   };
   glGenBuffers(1, &positionVBO);
   glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glGenBuffers(1, &colorVBO);
   glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glDrawArrays(GL_TRIANGLES, 0, 3);
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
   glDeleteBuffers(1, &positionVBO);
   glDeleteBuffers(1, &colorVBO);
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
   glutCreateWindow("Q09 - Two-VBO Colored Triangle");
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
