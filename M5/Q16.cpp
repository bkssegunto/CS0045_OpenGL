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

// Q16 - Sun Ground and Tree
GLuint sunVBO, groundVBO, groundIndexVBO, trunkVBO, leavesVBO;

void initSun() {
   GLfloat vertices[33 * 3];
   vertices[0] = 0.55f; vertices[1] = 0.55f; vertices[2] = 0.0f;
   for (int i = 0; i <= 31; i++) {
      float angle = i * 6.2831853f / 31;
      int b = (i + 1) * 3;
      vertices[b] = 0.55f + 0.18f * cosf(angle);
      vertices[b + 1] = 0.55f + 0.18f * sinf(angle);
      vertices[b + 2] = 0.0f;
   }
   glGenBuffers(1, &sunVBO);
   glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void initGround() {
   GLfloat vertices[] = {
      -0.95f, -0.9f, 0.0f, 0.95f, -0.9f, 0.0f,
       0.95f, -0.55f, 0.0f, -0.95f, -0.55f, 0.0f
   };
   GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };
   glGenBuffers(1, &groundVBO);
   glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glGenBuffers(1, &groundIndexVBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void initTree() {
   GLfloat trunk[] = {
      -0.5f, -0.55f, 0.0f, -0.4f, -0.55f, 0.0f,
      -0.4f, -0.1f, 0.0f, -0.5f, -0.1f, 0.0f
   };
   GLfloat leaves[] = {
      -0.45f, 0.5f, 0.0f, -0.75f, -0.15f, 0.0f, -0.15f, -0.15f, 0.0f
   };
   glGenBuffers(1, &trunkVBO);
   glBindBuffer(GL_ARRAY_BUFFER, trunkVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(trunk), trunk, GL_STATIC_DRAW);
   glGenBuffers(1, &leavesVBO);
   glBindBuffer(GL_ARRAY_BUFFER, leavesVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(leaves), leaves, GL_STATIC_DRAW);
}

void initScene() {
   glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
   initSun();
   initGround();
   initTree();
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.3f, 0.65f, 0.25f);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(1.0f, 0.8f, 0.1f);
   glDrawArrays(GL_TRIANGLE_FAN, 0, 33);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, trunkVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.5f, 0.25f, 0.1f);
   glDrawArrays(GL_QUADS, 0, 4);
   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, leavesVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColor3f(0.1f, 0.55f, 0.15f);
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
   glDeleteBuffers(1, &sunVBO);
   glDeleteBuffers(1, &groundVBO);
   glDeleteBuffers(1, &groundIndexVBO);
   glDeleteBuffers(1, &trunkVBO);
   glDeleteBuffers(1, &leavesVBO);
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
   glutCreateWindow("Q16 - Three-Shape VBO Scene: Sun, Indexed Ground and Tree");
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
