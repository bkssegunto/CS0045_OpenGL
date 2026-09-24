#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

int playerColor = BLUE;
int barrierColor = RED;
int score = 0;

float barrierY = 1.10f;
float barrierSpeed = 0.012f;

void drawBitmapString(void* font, const char* text)
{
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void setColor(int color)
{
    if (color == RED)
        glColor3f(1.0f, 0.15f, 0.15f);
    else if (color == GREEN)
        glColor3f(0.10f, 0.90f, 0.25f);
    else
        glColor3f(0.15f, 0.45f, 1.0f);
}

const char* colorName(int color)
{
    if (color == RED) return "RED";
    if (color == GREEN) return "GREEN";
    return "BLUE";
}

void drawPlayer()
{
    setColor(playerColor);
    glBegin(GL_QUADS);
        glVertex2f(-0.14f, -0.14f);
        glVertex2f(0.14f, -0.14f);
        glVertex2f(0.14f, 0.14f);
        glVertex2f(-0.14f, 0.14f);
    glEnd();
}

void drawBarrier()
{
    setColor(barrierColor);
    glBegin(GL_QUADS);
        glVertex2f(-0.78f, barrierY - 0.06f);
        glVertex2f(0.78f, barrierY - 0.06f);
        glVertex2f(0.78f, barrierY + 0.06f);
        glVertex2f(-0.78f, barrierY + 0.06f);
    glEnd();
}

bool colorsMatch()
{
    return playerColor == barrierColor;
}

bool checkGateCollision()
{
    return barrierY < 0.18f && barrierY > -0.18f;
}

void spawnNextBarrier()
{
    barrierY = 1.10f;
    barrierColor = rand() % 3;
}

void drawDashboard()
{
    char buffer[80];

    glColor3f(1.0f, 1.0f, 1.0f);
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glRasterPos2f(-0.92f, 0.90f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    snprintf(buffer, sizeof(buffer), "Player Color: %s", colorName(playerColor));
    glRasterPos2f(-0.92f, 0.79f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    snprintf(buffer, sizeof(buffer), "Barrier Speed: %.3f", barrierSpeed);
    glRasterPos2f(-0.92f, 0.68f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    glColor3f(0.78f, 0.78f, 0.85f);
    glRasterPos2f(-0.92f, -0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[R] Red  [G] Green  [B] Blue  [ESC] Exit");
    glRasterPos2f(-0.92f, -0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Rule: Match the gate to score. A mismatch deducts 1 point.");
}

void updateBarrier(int value)
{
    barrierY -= barrierSpeed;

    if (checkGateCollision())
    {
        if (colorsMatch())
        {
            score++;
            barrierSpeed += 0.0015f;
            if (barrierSpeed > 0.030f)
                barrierSpeed = 0.030f;

            cout << "Correct match! Score: " << score << endl;
        }
        else
        {
            if (score > 0)
                score--;

            cout << "Mismatch! Score: " << score << endl;
        }

        spawnNextBarrier();
    }
    else if (barrierY < -1.10f)
    {
        cout << "Barrier missed the gate." << endl;
        spawnNextBarrier();
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBarrier, 0);
}

void display()
{
    glClearColor(0.06f, 0.06f, 0.09f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawBarrier();
    drawPlayer();
    drawDashboard();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'r': case 'R': playerColor = RED; break;
        case 'g': case 'G': playerColor = GREEN; break;
        case 'b': case 'B': playerColor = BLUE; break;
        case 27: exit(0);
    }

    cout << "Player color: " << colorName(playerColor) << endl;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(850, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 2 - Chroma Shift");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBarrier, 0);

    glutMainLoop();
    return 0;
}
