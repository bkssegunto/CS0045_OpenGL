#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <cstring>

// Compile (MinGW/freeglut):
// g++ enrollment_ui_glut.cpp -o enrollment_ui -lfreeglut -lopengl32 -lglu32

constexpr int DESIGN_W = 900;
constexpr int DESIGN_H = 365;

struct Course {
    const char* code;
    const char* title;
    const char* section;
    const char* units;
    const char* days;
    const char* time;
    const char* room;
};

Course courses[] = {
    {"CS0011", "MOBILE PROGRAMMING",                         "TS31", "3", "S / W", "13:00:00-14:50:00 / 13:00:00-14:50:00", "F1209 / F609"},
    {"CS0016", "NETWORK AND COMMUNICATIONS 2A",              "TN35", "3", "T / W", "17:00:00-18:50:00 / 17:00:00-18:50:00", "ONLINE / F1101"},
    {"CS0019", "MODELING AND SIMULATION",                    "TN35", "3", "F / T", "11:00:00-12:50:00 / 11:00:00-12:50:00", "ONLINE / ONLINE"},
    {"CS0025", "SOFTWARE ENGINEERING 1",                     "TN35", "3", "F / TH", "15:00:00-16:50:00 / 15:00:00-16:50:00", "ONLINE / E609"},
    {"CS0045", "CS ELECTIVE - COMPUTER GRAPHICS AND VISUAL COMPUTING", "TN35", "3", "M / TH", "13:00:00-14:50:00 / 13:00:00-14:50:00", "E601 / E601"},
    {"CS0053", "CS SPECIALIZATION 2 - PROGRAMMING TOOLS AND TECHNIQUES", "TN35", "3", "M / TH", "07:00:00-08:50:00 / 07:00:00-08:50:00", "F702 / F609"}
};

float renderScale = 1.0f;
float offsetX = 0.0f;
float offsetY = 0.0f;

void text(float x, float y, const char* value, void* font = GLUT_BITMAP_HELVETICA_10) {
    glRasterPos2f(x, y);
    for (const char* p = value; *p; ++p) glutBitmapCharacter(font, *p);
}

void rectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y); glVertex2f(x + width, y);
    glVertex2f(x + width, y + height); glVertex2f(x, y + height);
    glEnd();
}

void outline(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); glVertex2f(x + width, y);
    glVertex2f(x + width, y + height); glVertex2f(x, y + height);
    glEnd();
}

void display() {
    glClearColor(0.96f, 0.97f, 0.99f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(offsetX, offsetY, 0.0f);
    glScalef(renderScale, renderScale, 1.0f);
    glPixelZoom(renderScale, renderScale);

    // Header information block
    glColor3f(0.03f, 0.10f, 0.20f);
    text(10, 340, "Enrollment Status : ENROLLED", GLUT_BITMAP_HELVETICA_12);
    text(10, 319, "Student # : 202312330", GLUT_BITMAP_HELVETICA_12);
    text(10, 298, "Name : SEGUNTO, BIENN KYLA SAGALES", GLUT_BITMAP_HELVETICA_12);
    text(10, 277, "Phone : 09391293772    Zip Code : 1410", GLUT_BITMAP_HELVETICA_12);
    text(10, 256, "Classification :", GLUT_BITMAP_HELVETICA_12);
    text(452, 319, "College : COMPUTER STUDIES    Program : BSCSSE", GLUT_BITMAP_HELVETICA_12);
    text(452, 298, "Year Level : 3    1st term, SY 26-27", GLUT_BITMAP_HELVETICA_12);
    text(452, 277, "Address : 288 Marulas A. Caloocan City", GLUT_BITMAP_HELVETICA_12);

    const float left = 10, tableTop = 232, tableWidth = 882, headerH = 28, rowH = 28;
    rectangle(left, tableTop - headerH, tableWidth, headerH, 0.89f, 0.89f, 0.89f);
    outline(left, 10, tableWidth, 222, 0.45f, 0.45f, 0.45f);
    glColor3f(0.01f, 0.05f, 0.12f);
    text(17, 212, "Courses", GLUT_BITMAP_HELVETICA_10);
    text(74, 212, "Title", GLUT_BITMAP_HELVETICA_10);
    text(448, 212, "Section", GLUT_BITMAP_HELVETICA_10);
    text(500, 212, "Units", GLUT_BITMAP_HELVETICA_10);
    text(540, 212, "Days", GLUT_BITMAP_HELVETICA_10);
    text(586, 212, "Time", GLUT_BITMAP_HELVETICA_10);
    text(790, 212, "Room", GLUT_BITMAP_HELVETICA_10);

    for (int i = 0; i < 6; ++i) {
        float y = 204 - i * rowH;
        if (i % 2 == 1) rectangle(left + 1, y - 27, tableWidth - 2, rowH, 0.94f, 0.94f, 0.92f);
        glColor3f(0.01f, 0.05f, 0.12f);
        text(21, y - 17, courses[i].code);
        text(74, y - 17, courses[i].title);
        text(455, y - 17, courses[i].section);
        text(512, y - 17, courses[i].units);
        text(540, y - 17, courses[i].days);
        text(597, y - 17, courses[i].time);
        text(798, y - 17, courses[i].room);
        glColor3f(0.82f, 0.82f, 0.80f);
        glBegin(GL_LINES); glVertex2f(left, y - 28); glVertex2f(left + tableWidth, y - 28); glEnd();
    }
    glColor3f(0.01f, 0.05f, 0.12f);
    text(17, 22, "TOTAL UNITS 18", GLUT_BITMAP_HELVETICA_10);
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
    glutCreateWindow("Schedule and Assessment");
#ifdef _WIN32
    ShowWindow(GetActiveWindow(), SW_MAXIMIZE);
#endif
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
