#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

const int STRIPE_COUNT = 8;

void drawStar(float centerX, float centerY) {
    const float outerRadius = 0.25f;
    const float innerRadius = 0.1f;

    glColor3f(1.0f, 1.0f, 0.0f);

    // Filled center of the star
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        float angle = 3.14159f / 2.0f + 3.14159f / 5.0f
                    + i * 2.0f * 3.14159f / 5.0f;
        glVertex2f(centerX + innerRadius * cosf(angle),
                   centerY + innerRadius * sinf(angle));
    }
    glEnd();

    // Five filled points of the star
    for (int i = 0; i < 5; i++) {
        float angle = 3.14159f / 2.0f
                    + i * 2.0f * 3.14159f / 5.0f;

        glBegin(GL_POLYGON);
            glVertex2f(centerX + innerRadius * cosf(angle - 3.14159f / 5.0f),
                       centerY + innerRadius * sinf(angle - 3.14159f / 5.0f));
            glVertex2f(centerX + outerRadius * cosf(angle),
                       centerY + outerRadius * sinf(angle));
            glVertex2f(centerX + innerRadius * cosf(angle + 3.14159f / 5.0f),
                       centerY + innerRadius * sinf(angle + 3.14159f / 5.0f));
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float stripeHeight = 1.6f / STRIPE_COUNT;

    for (int i = 0; i < STRIPE_COUNT; i++) {
        if (i % 2 == 0)
            glColor3f(1.0f, 0.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 1.0f);

        float y = -0.8f + i * stripeHeight;

        glBegin(GL_POLYGON);
            glVertex2f(-0.9f, y);
            glVertex2f( 0.9f, y);
            glVertex2f( 0.9f, y + stripeHeight);
            glVertex2f(-0.9f, y + stripeHeight);
        glEnd();
    }

    drawStar(-0.6f, 0.5f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Q20 - Procedural Striped Flag with Star");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}