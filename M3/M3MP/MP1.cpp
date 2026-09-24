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

float shipX = 0.0f;
float shipY = -0.55f;

float asteroid1X = -0.45f;
float asteroid1Y = 0.95f;
float asteroid2X = 0.40f;
float asteroid2Y = 0.55f;

float asteroid1Speed = 0.012f;
float asteroid2Speed = 0.020f;

int score = 0;
int lives = 3;
bool gameRunning = true;

void drawBitmapString(void* font, const char* text)
{
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawShip()
{
    // Ship body
    glColor3f(0.15f, 0.65f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(shipX, shipY + 0.12f);
        glVertex2f(shipX - 0.10f, shipY - 0.09f);
        glVertex2f(shipX + 0.10f, shipY - 0.09f);
    glEnd();

    // Ship wings
    glColor3f(0.75f, 0.85f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(shipX - 0.16f, shipY - 0.08f);
        glVertex2f(shipX - 0.03f, shipY - 0.03f);
        glVertex2f(shipX - 0.05f, shipY - 0.13f);
        glVertex2f(shipX - 0.18f, shipY - 0.15f);

        glVertex2f(shipX + 0.03f, shipY - 0.03f);
        glVertex2f(shipX + 0.16f, shipY - 0.08f);
        glVertex2f(shipX + 0.18f, shipY - 0.15f);
        glVertex2f(shipX + 0.05f, shipY - 0.13f);
    glEnd();
}

void drawAsteroid(float x, float y, float size)
{
    glColor3f(0.55f, 0.45f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(x - size, y);
        glVertex2f(x - size * 0.45f, y + size);
        glVertex2f(x + size * 0.55f, y + size * 0.75f);
        glVertex2f(x + size, y - size * 0.20f);
        glVertex2f(x + size * 0.30f, y - size);
        glVertex2f(x - size * 0.70f, y - size * 0.60f);
    glEnd();
}

void drawHUD()
{
    char buffer[80];

    glColor3f(1.0f, 1.0f, 1.0f);
    snprintf(buffer, sizeof(buffer), "Score: %d   Lives: %d", score, lives);
    glRasterPos2f(-0.92f, 0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glColor3f(0.75f, 0.75f, 0.85f);
    glRasterPos2f(-0.92f, 0.76f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[W][A][S][D] Move Ship   [R] Restart   [ESC] Exit");
}

bool checkCollision(float asteroidX, float asteroidY)
{
    float distanceX = shipX - asteroidX;
    float distanceY = shipY - asteroidY;

    if (distanceX < 0)
        distanceX = -distanceX;

    if (distanceY < 0)
        distanceY = -distanceY;

    return distanceX < 0.16f && distanceY < 0.16f;
}

void resetAsteroid(int asteroid)
{
    if (asteroid == 1)
    {
        asteroid1X = -0.75f + (rand() % 150) / 100.0f;
        asteroid1Y = 1.05f;
    }
    else
    {
        asteroid2X = -0.75f + (rand() % 150) / 100.0f;
        asteroid2Y = 1.20f;
    }
}

void resetGame()
{
    shipX = 0.0f;
    shipY = -0.55f;
    asteroid1X = -0.45f;
    asteroid1Y = 0.95f;
    asteroid2X = 0.40f;
    asteroid2Y = 0.55f;
    score = 0;
    lives = 3;
    gameRunning = true;
    cout << "Game restarted." << endl;
}

void updateGame(int value)
{
    if (gameRunning)
    {
        asteroid1Y -= asteroid1Speed;
        asteroid2Y -= asteroid2Speed;

        if (asteroid1Y < -1.10f)
        {
            score++;
            resetAsteroid(1);
        }

        if (asteroid2Y < -1.10f)
        {
            score++;
            resetAsteroid(2);
        }

        // Resetting a hit asteroid prevents repeated life loss from one overlap.
        if (checkCollision(asteroid1X, asteroid1Y))
        {
            lives--;
            cout << "Asteroid 1 hit! Lives remaining: " << lives << endl;
            resetAsteroid(1);
        }

        if (checkCollision(asteroid2X, asteroid2Y))
        {
            lives--;
            cout << "Asteroid 2 hit! Lives remaining: " << lives << endl;
            resetAsteroid(2);
        }

        if (lives <= 0)
        {
            lives = 0;
            gameRunning = false;
            cout << "GAME OVER" << endl;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

void display()
{
    glClearColor(0.02f, 0.03f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameRunning)
    {
        drawShip();
        drawAsteroid(asteroid1X, asteroid1Y, 0.09f);
        drawAsteroid(asteroid2X, asteroid2Y, 0.12f);
        drawHUD();
    }
    else
    {
        glColor3f(1.0f, 0.25f, 0.25f);
        glRasterPos2f(-0.48f, 0.10f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "GAME OVER - Press R to Restart");

        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(-0.26f, -0.08f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Final Score: ");
        char buffer[30];
        snprintf(buffer, sizeof(buffer), "%d", score);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        resetGame();
    }
    else if (key == 27)
    {
        exit(0);
    }
    else if (gameRunning)
    {
        switch (key)
        {
            case 'w': case 'W': shipY += 0.06f; break;
            case 's': case 'S': shipY -= 0.06f; break;
            case 'a': case 'A': shipX -= 0.06f; break;
            case 'd': case 'D': shipX += 0.06f; break;
        }

        if (shipX > 0.80f) shipX = 0.80f;
        if (shipX < -0.80f) shipX = -0.80f;
        if (shipY > 0.58f) shipY = 0.58f;
        if (shipY < -0.80f) shipY = -0.80f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(850, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 1 - The Cosmic Dodger");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateGame, 0);

    glutMainLoop();
    return 0;
}
