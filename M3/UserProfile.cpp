#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

constexpr int DESIGN_W = 900;
constexpr int DESIGN_H = 600;

float renderScale = 1.0f;
float offsetX = 0.0f;
float offsetY = 0.0f;

void drawText(float x, float y, const char* value, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* p = value; *p; ++p) {
        glutBitmapCharacter(font, *p);
    }
}

void labelValue(float labelX, float valueX, float y, const char* label, const char* value) {
    glColor3f(0.04f, 0.10f, 0.19f);
    drawText(labelX, y, label);
    drawText(valueX, y, value);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(renderScale, renderScale, 1.0f);
    glPixelZoom(renderScale, renderScale);

    glColor3f(0.02f, 0.07f, 0.14f);
    drawText(20, 560, "User Profile", GLUT_BITMAP_HELVETICA_18);
    drawText(815, 568, "User Profile", GLUT_BITMAP_HELVETICA_12);

    // Personal information column
    labelValue(31, 212, 485, "Student Number", "202312330");
    labelValue(31, 212, 435, "First Name", "BIENN KYLA");
    labelValue(31, 212, 385, "Middle Name", "SAGALES");
    labelValue(31, 212, 335, "Last Name", "SEGUNTO");
    labelValue(31, 212, 285, "Personal Email", "seguntobiennkyla@gmail.com");
    drawText(31, 257, "Address");
    labelValue(31, 212, 207, "School Email", "bssegunto@fit.edu.ph");
    drawText(31, 179, "Address");
    labelValue(31, 212, 127, "Citizenship", "FILIPINO");
    labelValue(31, 212, 77, "Program", "BSCSSE");
    labelValue(31, 212, 27, "Curriculum Code", "BSCSSE2023");

    // Enrollment information column
    drawText(470, 490, "Enrollment Status: Term 1 SY", GLUT_BITMAP_HELVETICA_18);
    drawText(470, 458, "20262027", GLUT_BITMAP_HELVETICA_18);
    labelValue(480, 644, 420, "Year Level", "3");
    labelValue(480, 644, 370, "Registration Status", "18 UNITS ENROLLED");
    labelValue(480, 644, 320, "Student Type", "REGULAR");
    labelValue(480, 644, 270, "Scholarship", "NO SCHOLARSHIP");
    labelValue(480, 644, 220, "Grades Viewing", "CLOSED");

    glFlush();
}

void reshape(int width, int height) {
    renderScale = static_cast<float>(width) / DESIGN_W;
    float verticalScale = static_cast<float>(height) / DESIGN_H;
    if (verticalScale < renderScale) renderScale = verticalScale;
    offsetX = (width - DESIGN_W * renderScale) * 0.5f;
    offsetY = (height - DESIGN_H * renderScale) * 0.5f;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0.96f, 0.97f, 0.99f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(DESIGN_W, DESIGN_H);
    glutCreateWindow("User Profile");
#ifdef _WIN32
    ShowWindow(GetActiveWindow(), SW_MAXIMIZE);
#endif
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
