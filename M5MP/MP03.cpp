#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

// Machine Problem 03 - Warehouse Robot Route Simulator

GLuint robotVBO = 0;
GLuint warehouseVBO = 0;

// Three vertices: x0, y0, x1, y1, x2, y2.
GLfloat robotVertices[] = {
   136, 238,
   164, 238,
   150, 266
};

GLfloat warehouseVertices[60];
int warehouseVertexCount = 0;

float robotX = 150;
float robotY = 250;

const float leftEdge = 55;
const float rightEdge = 605;
const float bottomEdge = 170;
const float topEdge = 590;

double stepSize = 15;

bool enteringStep = false;
bool autoMoving = false;

int destination = 0;

GLfloat route[4][2] = {
   {150, 500}, // A Receiving
   {490, 500}, // B Storage
   {490, 250}, // C Dispatch
   {150, 250}  // Start
};

string input;
string message = "Ready. Robot is at Start.";

void addRectangle(float x, float y, float width, float height) {
   GLfloat rectangle[] = {
      x, y,
      x + width, y,
      x + width, y + height,

      x, y,
      x + width, y + height,
      x, y + height
   };

   for (int i = 0; i < 12; i++) {
      warehouseVertices[warehouseVertexCount * 2 + i] = rectangle[i];
   }

   warehouseVertexCount += 6;
}

void initScene() {
   addRectangle(52, 167, 556, 426);
   addRectangle(55, 170, 550, 420);
   addRectangle(95, 455, 110, 100);
   addRectangle(435, 455, 110, 100);
   addRectangle(435, 205, 110, 100);

   glGenBuffers(1, &warehouseVBO);
   glBindBuffer(GL_ARRAY_BUFFER, warehouseVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(warehouseVertices),
                warehouseVertices, GL_STATIC_DRAW);

   // Initialize the robot VBO once with dynamic usage.
   glGenBuffers(1, &robotVBO);
   glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(robotVertices),
                robotVertices, GL_DYNAMIC_DRAW);

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

// Reuse the boundary vertices to draw other rectangles.
void drawBox(float x, float y, float width, float height,
             float red, float green, float blue) {
   glBindBuffer(GL_ARRAY_BUFFER, warehouseVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 0, 0);

   glPushMatrix();
   glTranslatef(x, y, 0);
   glScalef(width / 556.0f, height / 426.0f, 1);
   glTranslatef(-52, -167, 0);

   glColor3f(red, green, blue);
   glDrawArrays(GL_TRIANGLES, 0, 6);

   glPopMatrix();

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cleanup() {
   autoMoving = false;

   if (robotVBO != 0) {
      glDeleteBuffers(1, &robotVBO);
      robotVBO = 0;
   }

   if (warehouseVBO != 0) {
      glDeleteBuffers(1, &warehouseVBO);
      warehouseVBO = 0;
   }
}

void printConsoleMenu() {
   cout << "\n============================================\n"
        << "MACHINE PROBLEM 03 - WAREHOUSE ROBOT\n"
        << "============================================\n"
        << "Legend: Yellow = Robot | Blue = Receiving\n"
        << "        Purple = Storage | Green = Dispatch\n\n"
        << "Robot Position: (" << robotX << ", " << robotY << ")\n"
        << "Step Size: " << stepSize << " units\n"
        << "Auto-Move: " << (autoMoving ? "Running" : "Off") << "\n"
        << "Status: " << message << "\n\n"
        << "[1] Move Left\n"
        << "[2] Move Right\n"
        << "[3] Move Up\n"
        << "[4] Move Down\n"
        << "[5] Set Step Size\n"
        << "[6] Return to Start\n"
        << "[7] Auto-Move Demo\n"
        << "[0] Exit\n\n";

   if (enteringStep) {
      cout << "Enter a finite positive step size in the\n"
           << "graphics window, then press Enter.\n";
   } else {
      cout << "Type a menu number in the graphics window,\n"
           << "then press Enter.\n";
   }

   cout << "Backspace edits. Esc exits.\n"
        << "============================================\n"
        << endl;
}

bool moveRobot(double requestedX, double requestedY) {
   // Keep the entire triangle inside the warehouse.
   // Relative to its center: 14 left/right, 12 below, 16 above.
   float newX = static_cast<float>(
      max(double(leftEdge + 14),
          min(double(rightEdge - 14), requestedX))
   );

   float newY = static_cast<float>(
      max(double(bottomEdge + 12),
          min(double(topEdge - 16), requestedY))
   );

   float dx = newX - robotX;
   float dy = newY - robotY;

   GLfloat updated[6];

   // CPU shadow copy for fallback and recovery.
   for (int i = 0; i < 3; i++) {
      updated[i * 2] = robotVertices[i * 2] + dx;
      updated[i * 2 + 1] = robotVertices[i * 2 + 1] + dy;
   }

   glBindBuffer(GL_ARRAY_BUFFER, robotVBO);

   GLfloat* mapped = 0;

   if (glMapBuffer && glUnmapBuffer) {
      mapped = static_cast<GLfloat*>(
         glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE)
      );
   }

   if (mapped != 0) {
      // Move all vertices by the same displacement.
      for (int i = 0; i < 3; i++) {
         mapped[i * 2] += dx;
         mapped[i * 2 + 1] += dy;
      }

      // Unmap before the buffer is used for drawing.
      if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
         // Restore every coordinate if unmapping reports corruption.
         glBufferSubData(GL_ARRAY_BUFFER, 0,
                         sizeof(updated), updated);
      }
   } else {
      // Safe fallback if mapping is unavailable or fails.
      GLenum mappingError = glGetError();

      if (mappingError != GL_NO_ERROR) {
         cerr << "Mapping failed; using glBufferSubData." << endl;
      }

      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      sizeof(updated), updated);
   }

   GLenum error = glGetError();
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   if (error != GL_NO_ERROR) {
      autoMoving = false;
      message = "Buffer update failed. Movement stopped.";
      return false;
   }

   for (int i = 0; i < 6; i++) {
      robotVertices[i] = updated[i];
   }

   robotX = newX;
   robotY = newY;

   glutPostRedisplay();
   return true;
}

void processInput() {
   istringstream reader(input);

   cout << (enteringStep ? "Step: " : "Choice: ")
        << input << endl;

   if (enteringStep) {
      double value;

      if (!(reader >> value) || !isfinite(value) || value <= 0) {
         message = "Invalid step. Enter a finite positive number.";
         return;
      }

      reader >> ws;

      if (!reader.eof()) {
         message = "Invalid step. Enter a finite positive number.";
         return;
      }

      stepSize = value;
      enteringStep = false;
      message = "Step size updated.";
      return;
   }

   int choice;

   if (!(reader >> choice)) {
      message = "Invalid choice. Enter an integer from 0 to 7.";
      return;
   }

   reader >> ws;

   if (!reader.eof() || choice < 0 || choice > 7) {
      message = "Invalid choice. Enter an integer from 0 to 7.";
      return;
   }

   // Valid manual commands cancel the current demo.
   autoMoving = false;

   double x = robotX;
   double y = robotY;

   switch (choice) {
      case 0:
         cleanup();
         glutLeaveMainLoop();
         return;

      case 1:
         x -= stepSize;
         break;

      case 2:
         x += stepSize;
         break;

      case 3:
         y += stepSize;
         break;

      case 4:
         y -= stepSize;
         break;

      case 5:
         enteringStep = true;
         message = "Enter a positive step size, then press Enter.";
         return;

      case 6:
         x = 150;
         y = 250;
         break;

      case 7:
         destination = 0;
         autoMoving = true;
         message = "Auto route: A > B > C > Start.";
         return;
   }

   bool limited =
      x < leftEdge + 14 || x > rightEdge - 14 ||
      y < bottomEdge + 12 || y > topEdge - 16;

   if (moveRobot(x, y)) {
      message = limited
         ? "Boundary reached. Robot remains inside."
         : "Robot position updated.";
   }
}

void animateStep(int) {
   if (autoMoving) {
      double dx = route[destination][0] - robotX;
      double dy = route[destination][1] - robotY;
      double distance = hypot(dx, dy);

      if (distance <= stepSize) {
         // Arrive exactly at the target without overshooting.
         if (moveRobot(route[destination][0],
                       route[destination][1])) {
            destination++;

            if (destination == 4) {
               autoMoving = false;
               message = "Auto demo complete. Robot returned to Start.";
               printConsoleMenu();
            }
         }
      } else {
         moveRobot(
            robotX + dx / distance * stepSize,
            robotY + dy / distance * stepSize
         );
      }

      glutPostRedisplay();
   }

   // One recurring animation timer, started once in main.
   glutTimerFunc(50, animateStep, 0);
}

void display() {
   if (robotVBO == 0) return;

   glClearColor(0.055f, 0.075f, 0.11f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Header and controls panel.
   drawBox(35, 613, 5, 48, 0.20f, 0.78f, 0.65f);
   drawBox(630, 135, 335, 460, 0.10f, 0.13f, 0.18f);

   glColor3f(0.95f, 0.97f, 1.0f);
   drawText(55, 645, "WAREHOUSE ROBOT ROUTE");

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(
      55, 621,
      "RECEIVING  >  STORAGE  >  DISPATCH  /  MACHINE PROBLEM 03"
   );

   // Warehouse boundary and floor.
   drawBox(52, 167, 556, 426, 0.36f, 0.44f, 0.54f);
   drawBox(leftEdge, bottomEdge, 550, 420,
           0.10f, 0.14f, 0.19f);

   // Floor grid.
   for (int x = 75; x < 605; x += 35) {
      drawBox(float(x), 170, 1, 420,
              0.13f, 0.17f, 0.22f);
   }

   for (int y = 180; y < 590; y += 35) {
      drawBox(55, float(y), 550, 1,
              0.13f, 0.17f, 0.22f);
   }

   // Dashed route guide.
   for (int y = 270; y < 480; y += 28) {
      drawBox(148, float(y), 4, 13,
              0.28f, 0.38f, 0.43f);
      drawBox(488, float(y), 4, 13,
              0.28f, 0.38f, 0.43f);
   }

   for (int x = 180; x < 470; x += 28) {
      drawBox(float(x), 498, 13, 4,
              0.28f, 0.38f, 0.43f);
      drawBox(float(x), 248, 13, 4,
              0.28f, 0.38f, 0.43f);
   }

   // Three labeled and color-coded stations.
   GLfloat stationColors[3][3] = {
      {0.25f, 0.65f, 0.95f},
      {0.70f, 0.48f, 0.92f},
      {0.20f, 0.78f, 0.58f}
   };

   float stationX[] = {95, 435, 435};
   float stationY[] = {455, 455, 205};

   string names[] = {"RECEIVING", "STORAGE", "DISPATCH"};
   string letters[] = {"A", "B", "C"};

   for (int i = 0; i < 3; i++) {
      float x = stationX[i];
      float y = stationY[i];

      drawBox(
         x - 2, y - 2, 114, 104,
         stationColors[i][0],
         stationColors[i][1],
         stationColors[i][2]
      );

      drawBox(x, y, 110, 100, 0.14f, 0.20f, 0.26f);

      glColor3f(stationColors[i][0],
                stationColors[i][1],
                stationColors[i][2]);
      drawText(x + 12, y + 65, letters[i]);

      glColor3f(0.90f, 0.94f, 0.98f);
      drawSmallText(x + 12, y + 45, names[i]);

      // Shelf markings.
      drawBox(x + 12, y + 16, 36, 8,
              0.24f, 0.31f, 0.39f);
      drawBox(x + 60, y + 16, 36, 8,
              0.24f, 0.31f, 0.39f);
   }

   glColor3f(0.65f, 0.74f, 0.83f);
   drawSmallText(115, 210, "START / HOME");

   // Robot uses the dynamic VBO updated by moveRobot().
   glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, 0, 0);

   glColor3f(1.0f, 0.80f, 0.25f);
   glDrawArrays(GL_TRIANGLES, 0, 3);

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glColor3f(0.95f, 0.97f, 1.0f);
   drawText(650, 557, "ROBOT CONTROLS");

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(650, 533, "Yellow triangle = robot");

   string menu[] = {
      "1  Move Left",
      "2  Move Right",
      "3  Move Up",
      "4  Move Down",
      "5  Set Step Size",
      "6  Return to Start",
      "7  Auto-Move Demo",
      "0  Exit"
   };

   for (int i = 0; i < 8; i++) {
      float y = 494.0f - i * 34;

      bool selected =
         (i == 4 && enteringStep) ||
         (i == 6 && autoMoving);

      drawBox(
         645, y - 4, 305, 29,
         selected ? 0.17f : 0.12f,
         selected ? 0.25f : 0.16f,
         selected ? 0.31f : 0.21f
      );

      glColor3f(0.90f, 0.94f, 0.98f);
      drawText(657, y + 3, menu[i]);
   }

   ostringstream info;
   info << "Step: " << stepSize << " units";

   glColor3f(0.67f, 0.75f, 0.84f);
   drawSmallText(650, 198, info.str());

   info.str("");
   info.clear();
   info << "Position: (" << robotX << ", " << robotY << ")";
   drawSmallText(650, 178, info.str());

   glColor3f(0.25f, 0.85f, 0.65f);
   drawSmallText(
      650, 153,
      autoMoving ? "AUTO DEMO RUNNING" : "READY FOR COMMAND"
   );

   // Input and status areas.
   drawBox(35, 26, 270, 95, 0.10f, 0.14f, 0.19f);
   drawBox(320, 26, 645, 95, 0.10f, 0.14f, 0.19f);

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(
      50, 98,
      enteringStep ? "SET POSITIVE STEP SIZE" : "NUMERIC INPUT"
   );
   drawSmallText(335, 98, "STATUS");

   glColor3f(0.95f, 0.97f, 1.0f);
   drawSmallText(50, 65, "> " + input + "_");

   glColor3f(1.0f, 0.80f, 0.35f);
   drawText(335, 68, message);

   glColor3f(0.57f, 0.65f, 0.75f);
   drawSmallText(
      335, 43,
      "ENTER submit     BACKSPACE edit     ESC exit"
   );

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

      if (robotVBO == 0) return;

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

   glutCreateWindow(
      "MP03 - Warehouse Robot Route Simulator"
   );

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

   glutTimerFunc(50, animateStep, 0);

   printConsoleMenu();

   glutMainLoop();
   return 0;
}