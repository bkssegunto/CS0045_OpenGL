#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
#include <cmath>
using namespace std;

float colors[6][3] = {
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {1, 1, 0}, {1, 0, 1}, {0, 1, 1}
};

const char* names[6] = {
    "Red", "Green", "Blue", "Yellow", "Magenta", "Cyan"
};

int selected = 0;

void display() {
    glClearColor(colors[selected][0], colors[selected][1], colors[selected][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '6') {
        selected = key - '1';
        cout << names[selected] << endl;
        glutPostRedisplay();
    }
    if (key == 27) exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Keyboard Color Picker");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}