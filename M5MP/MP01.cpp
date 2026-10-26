#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

// Machine Problem 01 - Campus Traffic Signal Visualizer

GLuint VBOid = 0;

const int segments = 36;
const int lampVertices = segments * 3;

GLfloat vertices[(6 + lampVertices * 3) * 2];

int vertexCount = 0;
int activeSignal = 1;

string input;
string message = "Ready. Red / Stop is active.";

void addVertex(float x, float y) {
   vertices[vertexCount * 2] = x;
   vertices[vertexCount * 2 + 1] = y;
   vertexCount++;
}

void initScene() {
   // Housing: two triangles.
   addVertex(160, 160);
   addVertex(360, 160);
   addVertex(360, 560);

   addVertex(160, 160);
   addVertex(360, 560);
   addVertex(160, 560);

   // Three circular indicators made from triangles.
   for (int lamp = 0; lamp < 3; lamp++) {
      float centerY = 490.0f - lamp * 130.0f;

      for (int i = 0; i < segments; i++) {
         float angle1 = i * 6.2831853f / segments;
         float angle2 = (i + 1) * 6.2831853f / segments;

         addVertex(260, centerY);
         addVertex(260 + 43 * cos(angle1),
                   centerY + 43 * sin(angle1));
         addVertex(260 + 43 * cos(angle2),
                   centerY + 43 * sin(angle2));
      }
   }

   // Create and upload once.
   glGenBuffers(1, &VBOid);
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawText(float x, float y, const string& text) {
   glRasterPos2f(x, y);

   for (char c : text) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
   }
}

void drawSmallText(float x, float y, const string& text) {
   glRasterPos2f(x, y);

   for (char c : text) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
   }
}

// Reuse the housing vertices for rectangular decorations.
void drawBox(float x, float y, float width, float height,
             float red, float green, float blue) {
   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 0, 0);

   glPushMatrix();
   glTranslatef(x, y, 0);
   glScalef(width / 200.0f, height / 400.0f, 1);
   glTranslatef(-160, -160, 0);

   glColor3f(red, green, blue);
   glDrawArrays(GL_TRIANGLES, 0, 6);

   glPopMatrix();

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cleanup() {
   if (VBOid != 0) {
      glDeleteBuffers(1, &VBOid);
      VBOid = 0;
   }
}

void printConsoleMenu() {
   string states[] = {
      "All Off",
      "Red / Stop",
      "Yellow / Caution",
      "Green / Go"
   };

   cout << "\n============================================\n"
        << "MACHINE PROBLEM 01 - TRAFFIC SIGNAL\n"
        << "============================================\n"
        << "Legend: Red = Stop | Yellow = Caution\n"
        << "        Green = Go | Dark Gray = Inactive\n\n"
        << "Current Signal: " << states[activeSignal] << "\n"
        << "Status: " << message << "\n\n"
        << "[1] Red / Stop\n"
        << "[2] Yellow / Caution\n"
        << "[3] Green / Go\n"
        << "[4] All Off\n"
        << "[5] Reset\n"
        << "[0] Exit\n\n"
        << "Type a number in the graphics window,\n"
        << "then press Enter. Backspace edits. Esc exits.\n"
        << "============================================\n"
        << endl;
}

void processInput() {
   int choice;
   istringstream reader(input);

   cout << "Choice: " << input << endl;

   if (!(reader >> choice)) {
      message = "Invalid input. Enter an integer from 0 to 5.";
      return;
   }

   reader >> ws;

   if (!reader.eof() || choice < 0 || choice > 5) {
      message = "Invalid input. Enter an integer from 0 to 5.";
      return;
   }

   switch (choice) {
      case 0:
         cleanup();
         glutLeaveMainLoop();
         return;

      case 1:
         activeSignal = 1;
         message = "Red / Stop";
         break;

      case 2:
         activeSignal = 2;
         message = "Yellow / Caution";
         break;

      case 3:
         activeSignal = 3;
         message = "Green / Go";
         break;

      case 4:
         activeSignal = 0;
         message = "All indicators are off.";
         break;

      case 5:
         activeSignal = 1;
         message = "Reset: Red / Stop";
         break;
   }
}

void display() {
   if (VBOid == 0) return;

   glClearColor(0.055f, 0.075f, 0.11f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Header and background panels.
   drawBox(35, 613, 5, 48, 0.20f, 0.78f, 0.65f);
   drawBox(35, 135, 550, 460, 0.085f, 0.115f, 0.16f);
   drawBox(610, 135, 355, 460, 0.10f, 0.13f, 0.18f);

   glColor3f(0.95f, 0.97f, 1.0f);
   drawText(55, 645, "CAMPUS TRAFFIC SIGNAL");

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(55, 621,
                 "ROAD SAFETY DEMONSTRATION / MACHINE PROBLEM 01");

   // Stand, shadow, border and housing.
   drawBox(247, 145, 26, 42, 0.35f, 0.40f, 0.47f);
   drawBox(215, 135, 90, 12, 0.27f, 0.32f, 0.39f);
   drawBox(167, 164, 200, 400, 0.035f, 0.045f, 0.065f);
   drawBox(154, 164, 212, 404, 0.30f, 0.35f, 0.42f);
   drawBox(160, 170, 200, 392, 0.14f, 0.17f, 0.22f);

   GLfloat colors[3][3] = {
      {1.0f, 0.25f, 0.28f},
      {1.0f, 0.77f, 0.20f},
      {0.17f, 0.87f, 0.57f}
   };

   string labels[] = {"STOP", "CAUTION", "GO"};

   glBindBuffer(GL_ARRAY_BUFFER, VBOid);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 0, 0);

   for (int i = 0; i < 3; i++) {
      float centerY = 490.0f - i * 130.0f;

      // Dark outer rim.
      glPushMatrix();
      glTranslatef(260, centerY, 0);
      glScalef(1.16f, 1.16f, 1);
      glTranslatef(-260, -centerY, 0);

      glColor3f(0.055f, 0.07f, 0.10f);
      glDrawArrays(GL_TRIANGLES,
                   6 + i * lampVertices, lampVertices);

      glPopMatrix();

      if (activeSignal == i + 1) {
         glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      } else {
         glColor3f(0.24f, 0.28f, 0.33f);
      }

      glDrawArrays(GL_TRIANGLES,
                   6 + i * lampVertices, lampVertices);
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // Indicator labels.
   for (int i = 0; i < 3; i++) {
      if (activeSignal == i + 1) {
         glColor3f(colors[i][0], colors[i][1], colors[i][2]);
      } else {
         glColor3f(0.45f, 0.51f, 0.59f);
      }

      drawText(395, 485 - i * 130, labels[i]);

      drawSmallText(395, 463 - i * 130,
                    activeSignal == i + 1
                    ? "ACTIVE SIGNAL" : "INACTIVE");
   }

   glColor3f(0.95f, 0.97f, 1.0f);
   drawText(635, 557, "OPERATOR MENU");

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(635, 533, "Select a state using its number.");

   string menu[] = {
      "1   Red / Stop",
      "2   Yellow / Caution",
      "3   Green / Go",
      "4   All Off",
      "5   Reset",
      "0   Exit"
   };

   for (int i = 0; i < 6; i++) {
      bool selected =
         (i < 3 && activeSignal == i + 1) ||
         (i == 3 && activeSignal == 0);

      float y = 467.0f - i * 48;

      drawBox(630, y, 315, 38,
              selected ? 0.17f : 0.12f,
              selected ? 0.25f : 0.16f,
              selected ? 0.31f : 0.21f);

      glColor3f(0.90f, 0.94f, 0.98f);
      drawText(645, y + 12, menu[i]);
   }

   // Input and status.
   drawBox(35, 26, 270, 85, 0.10f, 0.14f, 0.19f);
   drawBox(320, 26, 645, 85, 0.10f, 0.14f, 0.19f);

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(50, 88, "NUMERIC INPUT");
   drawSmallText(335, 88, "STATUS");

   glColor3f(0.95f, 0.97f, 1.0f);
   drawSmallText(50, 60, "Choice > " + input + "_");

   glColor3f(1.0f, 0.80f, 0.35f);
   drawText(335, 61, message);

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(335, 39,
                 "ENTER submit     BACKSPACE edit     ESC exit");

   glutSwapBuffers();
}

void reshape(int width, int height) {
   if (width < 1) width = 1;
   if (height < 1) height = 1;

   int viewWidth = width;
   int viewHeight = width * 700 / 1000;

   if (viewHeight > height) {
      viewHeight = height;
      viewWidth = height * 1000 / 700;
   }

   glViewport((width - viewWidth) / 2,
              (height - viewHeight) / 2,
              viewWidth, viewHeight);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 1000, 0, 700, -1, 1);

   glMatrixMode(GL_MODELVIEW);
}

void monitorKeyboard(unsigned char key, int, int) {
   if (key == 27) {
      cleanup();
      glutLeaveMainLoop();
      return;
   }

   if (key == 13) {
      processInput();

      if (VBOid == 0) return;

      input.clear();
      printConsoleMenu();
   } else if (key == 8 || key == 127) {
      if (!input.empty()) input.pop_back();
   } else if (key >= 32 && key <= 126 && input.size() < 30) {
      input += static_cast<char>(key);
   }

   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitContextVersion(2, 1);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1000, 700);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("MP01 - Campus Traffic Signal");

   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                 GLUT_ACTION_GLUTMAINLOOP_RETURNS);

   GLenum err = glewInit();

   if (err != GLEW_OK || !GLEW_VERSION_1_5) {
      cerr << "GLEW initialization or VBO support failed." << endl;
      return 1;
   }

   initScene();

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(monitorKeyboard);
   glutCloseFunc(cleanup);

   printConsoleMenu();

   glutMainLoop();
   return 0;
}