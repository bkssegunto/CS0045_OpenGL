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
#include <ctime>
#include <cmath>

using namespace std;

const int MAX_BURSTS = 20;
const int SQUARE_BURST = 1;
const int DIAMOND_BURST = 2;
const int STAR_BURST = 3;

struct Burst
{
    bool active;
    int type;
    float x;
    float y;
    float radius;
    float brightness;
    float red;
    float green;
    float blue;
};

Burst bursts[MAX_BURSTS];
int currentMode = SQUARE_BURST;

void drawBitmapString(void* font, const char* text)
{
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

int activeBurstCount()
{
    int count = 0;
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
            count++;
    }
    return count;
}

void spawnBurst(int type, float x, float y)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (!bursts[i].active)
        {
            bursts[i].active = true;
            bursts[i].type = type;
            bursts[i].x = x;
            bursts[i].y = y;
            bursts[i].radius = 0.03f;
            bursts[i].brightness = 1.0f;
            bursts[i].red = 0.35f + (rand() % 66) / 100.0f;
            bursts[i].green = 0.25f + (rand() % 76) / 100.0f;
            bursts[i].blue = 0.35f + (rand() % 66) / 100.0f;
            cout << "Burst created. Active bursts: " << activeBurstCount() << endl;
            return;
        }
    }

    cout << "Maximum number of bursts reached." << endl;
}

void drawSquareBurst(const Burst& burst)
{
    for (int ring = 1; ring <= 3; ring++)
    {
        float size = burst.radius * ring / 3.0f;
        glBegin(GL_LINE_LOOP);
            glVertex2f(burst.x - size, burst.y - size);
            glVertex2f(burst.x + size, burst.y - size);
            glVertex2f(burst.x + size, burst.y + size);
            glVertex2f(burst.x - size, burst.y + size);
        glEnd();
    }
}

void drawDiamondBurst(const Burst& burst)
{
    for (int ring = 1; ring <= 3; ring++)
    {
        float size = burst.radius * ring / 3.0f;
        glBegin(GL_LINE_LOOP);
            glVertex2f(burst.x, burst.y + size);
            glVertex2f(burst.x + size, burst.y);
            glVertex2f(burst.x, burst.y - size);
            glVertex2f(burst.x - size, burst.y);
        glEnd();
    }
}

void drawStarBurst(const Burst& burst)
{
    const float PI = 3.14159265f;
    for (int ray = 0; ray < 12; ray++)
    {
        float angle = ray * 2.0f * PI / 12.0f;
        float leftAngle = angle - 0.10f;
        float rightAngle = angle + 0.10f;

        glBegin(GL_TRIANGLES);
            glVertex2f(burst.x, burst.y);
            glVertex2f(burst.x + cos(leftAngle) * burst.radius,
                       burst.y + sin(leftAngle) * burst.radius);
            glVertex2f(burst.x + cos(rightAngle) * burst.radius,
                       burst.y + sin(rightAngle) * burst.radius);
        glEnd();
    }
}

void drawBurst(const Burst& burst)
{
    glColor3f(burst.red * burst.brightness,
              burst.green * burst.brightness,
              burst.blue * burst.brightness);
    glLineWidth(2.0f);

    if (burst.type == SQUARE_BURST)
        drawSquareBurst(burst);
    else if (burst.type == DIAMOND_BURST)
        drawDiamondBurst(burst);
    else
        drawStarBurst(burst);
}

const char* modeName()
{
    if (currentMode == SQUARE_BURST) return "Concentric Squares";
    if (currentMode == DIAMOND_BURST) return "Diamond Lattice";
    return "Starburst Triangles";
}

void drawSidebar()
{
    char buffer[80];

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.92f, 0.90f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "=== FIREWORKS STUDIO ===");

    snprintf(buffer, sizeof(buffer), "Mode: %s", modeName());
    glRasterPos2f(-0.92f, 0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    snprintf(buffer, sizeof(buffer), "Active Bursts: %d", activeBurstCount());
    glRasterPos2f(-0.92f, 0.68f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    glColor3f(0.78f, 0.78f, 0.85f);
    glRasterPos2f(-0.92f, -0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[1] Squares  [2] Diamonds  [3] Stars");
    glRasterPos2f(-0.92f, -0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[SPACE] Random current mode  [ESC] Exit");
}

void updateBursts(int value)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
        {
            bursts[i].radius += 0.012f;
            bursts[i].brightness -= 0.018f;

            if (bursts[i].brightness <= 0.0f || bursts[i].radius > 0.75f)
            {
                bursts[i].active = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBursts, 0);
}

void display()
{
    glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (bursts[i].active)
            drawBurst(bursts[i]);
    }

    drawSidebar();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        currentMode = SQUARE_BURST;
    else if (key == '2')
        currentMode = DIAMOND_BURST;
    else if (key == '3')
        currentMode = STAR_BURST;
    else if (key == ' ')
    {
        float randomX = -0.70f + (rand() % 141) / 100.0f;
        float randomY = -0.50f + (rand() % 101) / 100.0f;
        spawnBurst(currentMode, randomX, randomY);
    }
    else if (key == 27)
    {
        exit(0);
    }

    // Number keys select a visibly different pattern and launch it immediately.
    if (key == '1' || key == '2' || key == '3')
    {
        float randomX = -0.70f + (rand() % 141) / 100.0f;
        float randomY = -0.50f + (rand() % 101) / 100.0f;
        spawnBurst(currentMode, randomX, randomY);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));

    for (int i = 0; i < MAX_BURSTS; i++)
        bursts[i].active = false;

    glutInit(&argc, argv);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 3 - Dynamic Fireworks Studio");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBursts, 0);

    glutMainLoop();
    return 0;
}
