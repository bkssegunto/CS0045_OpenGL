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

// Q20 - Animated Ship Over Indexed Ground
GLuint shipVBO, colorVBO, groundVBO, groundIndexVBO;
float offset = 0.0f;
float direction = 1.0f;

void initScene() {
   GLfloat shipVertices[] = {
       0.0f, 0.5f, 0.0f, -0.2f, 0.1f, 0.0f, 0.2f, 0.1f, 0.0f
   };
   GLfloat colors[] = {
      1.0f, 0.2f, 0.2f, 0.2f, 1.0f, 0.2f, 0.2f, 0.2f, 1.0f
   };
   GLfloat groundVertices[] = {
      -0.95f, -0.9f, 0.0f, 0.95f, -0.9f, 0.0f,
       0.95f, -0.6f, 0.0f, -0.95f, -0.6f, 0.0f
   };
   GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };
   glGenBuffers(1, &shipVBO);
   glBindBuffer(GL_ARRAY_BUFFER, shipVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(shipVertices), shipVertices, GL_DYNAMIC_DRAW);
   glGenBuffers(1, &colorVBO);
   glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
   glGenBuffers(1, &groundVBO);
   glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
   glGenBuffers(1, &groundIndexVBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.3f, 0.6f, 0.3f);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, shipVBO);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glFlush();
}

void animateStep(int) {
   float nextOffset = offset + direction * 0.1f;
   if (nextOffset >= 0.6f) {
      nextOffset = 0.6f;
      direction = -1.0f;
   } else if (nextOffset <= -0.6f) {
      nextOffset = -0.6f;
      direction = 1.0f;
   }
   glBindBuffer(GL_ARRAY_BUFFER, shipVBO);
   GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
   if (mapped) {
      float dx = nextOffset - offset;
      for (int i = 0; i < 3; i++) mapped[i * 3] += dx;
      glUnmapBuffer(GL_ARRAY_BUFFER);
      offset = nextOffset;
   }
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glutPostRedisplay();
   glutTimerFunc(1000, animateStep, 0);
}

void cleanup() {
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDeleteBuffers(1, &shipVBO);
   glDeleteBuffers(1, &colorVBO);
   glDeleteBuffers(1, &groundVBO);
   glDeleteBuffers(1, &groundIndexVBO);
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
   glutCreateWindow("Q20 - Animated Ship Over Indexed Ground");
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
   glutTimerFunc(1000, animateStep, 0);
   glutMainLoop();
   return 0;
}
