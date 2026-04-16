/*
 * OpenGL Program: Translation + Rotation of a Quadrilateral
 * 
 * Initial points: A(0,4), B(3,4), C(4,0), D(0,0)
 * Translation: +2 in X, +2 in Y  →  A'(2,6), B'(5,6), C'(6,2), D'(2,2)
 * 
 * INSTRUCTION (ii): The translated figure is drawn with a GREEN border and CREAM inner shading.
 * INSTRUCTION (iii): The translated figure is then rotated by 55° about the origin; the rotated figure is shown.
 * 
 * Axes are drawn with labelled tick marks and 'X'/'Y' labels.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdio>
#include <cstring>

#define PI 3.14159265358979323846

// Vertices of the original quadrilateral
float original[4][2] = {
    {0.0f, 4.0f},   // A
    {3.0f, 4.0f},   // B
    {4.0f, 0.0f},   // C
    {0.0f, 0.0f}    // D
};

// Translated vertices (shift by +2 in X and +2 in Y)
float translated[4][2];

// Rotated vertices (translated vertices rotated by 55° about origin)
float rotated[4][2];

// Translation vector
const float tx = 2.0f;
const float ty = 2.0f;

// Rotation angle in degrees
const float theta_deg = 55.0f;
float theta_rad;

// -------------------------------------------------------------------
// Compute translated coordinates
void computeTranslated() {
    for (int i = 0; i < 4; i++) {
        translated[i][0] = original[i][0] + tx;
        translated[i][1] = original[i][1] + ty;
    }
}

// Compute rotated coordinates (rotate translated vertices about origin)
void computeRotated() {
    float cosTheta = cos(theta_rad);
    float sinTheta = sin(theta_rad);
    for (int i = 0; i < 4; i++) {
        float x = translated[i][0];
        float y = translated[i][1];
        rotated[i][0] = x * cosTheta - y * sinTheta;
        rotated[i][1] = x * sinTheta + y * cosTheta;
    }
}

// -------------------------------------------------------------------
// Draw a filled polygon with a border
void drawPolygon(float vertices[4][2], float fillR, float fillG, float fillB,
                 float borderR, float borderG, float borderB, float lineWidth = 2.0f) {
    // Fill
    glColor3f(fillR, fillG, fillB);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    // Border
    glColor3f(borderR, borderG, borderB);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// Draw a string using bitmap fonts
void drawString(float x, float y, const char* str) {
    glRasterPos2f(x, y);
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// -------------------------------------------------------------------
// Draw labelled axes with tick marks and scaling
void drawAxesWithLabels() {
    glColor3f(0.8f, 0.8f, 0.8f);   // Light gray axes
    glLineWidth(1.5f);

    // X and Y axes
    glBegin(GL_LINES);
    glVertex2f(-8.0f, 0.0f);
    glVertex2f(8.0f, 0.0f);
    glVertex2f(0.0f, -2.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();

    // Arrow heads
    glBegin(GL_TRIANGLES);
    glVertex2f(7.8f, 0.15f);
    glVertex2f(8.0f, 0.0f);
    glVertex2f(7.8f, -0.15f);
    glVertex2f(-0.15f, 9.8f);
    glVertex2f(0.0f, 10.0f);
    glVertex2f(0.15f, 9.8f);
    glEnd();

    // Tick marks and numbers
    char label[10];
    // X-axis ticks -7 to 7
    for (int x = -7; x <= 7; x++) {
        if (x == 0) continue;
        glBegin(GL_LINES);
        glVertex2f(x, -0.1f);
        glVertex2f(x, 0.1f);
        glEnd();
        sprintf(label, "%d", x);
        drawString(x - 0.2f, -0.4f, label);
    }
    // Y-axis ticks -1 to 9
    for (int y = -1; y <= 9; y++) {
        if (y == 0) continue;
        glBegin(GL_LINES);
        glVertex2f(-0.1f, y);
        glVertex2f(0.1f, y);
        glEnd();
        sprintf(label, "%d", y);
        drawString(0.15f, y - 0.15f, label);
    }
    // Origin tick
    glBegin(GL_LINES);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, 0.1f);
    glEnd();
    drawString(-0.3f, -0.4f, "0");

    // Axis labels
    drawString(7.6f, -0.5f, "X");
    drawString(0.15f, 9.6f, "Y");
}

// -------------------------------------------------------------------
// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    drawAxesWithLabels();

    // (Optional) Original shape – faint dashed for reference
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(original[i][0], original[i][1]);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    // -----------------------------------------------------------------
    // INSTRUCTION (ii): Translated figure with GREEN border and CREAM fill
    // Cream colour: RGB(255, 253, 208) -> (1.0, 0.992, 0.816)
    drawPolygon(translated,
                1.0f, 0.992f, 0.816f,   // cream fill
                0.0f, 1.0f, 0.0f,       // green border
                2.5f);                  // border width
    // -----------------------------------------------------------------

    // -----------------------------------------------------------------
    // INSTRUCTION (iii): Rotated figure (translated figure rotated by 55°)
    // No specific styling requested – using red border + light transparent-like fill
    drawPolygon(rotated,
                1.0f, 0.9f, 0.8f,       // light peach fill
                1.0f, 0.0f, 0.0f,       // red border
                2.0f);
    // -----------------------------------------------------------------

    glutSwapBuffers();
}

// Reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // World coordinates: x in [-8, 8], y in [-2, 10] – properly scaled
    gluOrtho2D(-8.0, 8.0, -2.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Print coordinates to console
void printCoordinates() {
    printf("===== Coordinate Information =====\n");
    printf("Original points:\n");
    printf("A(%.2f, %.2f)  B(%.2f, %.2f)  C(%.2f, %.2f)  D(%.2f, %.2f)\n",
           original[0][0], original[0][1], original[1][0], original[1][1],
           original[2][0], original[2][1], original[3][0], original[3][1]);

    printf("\nAfter translation by (%.1f, %.1f):\n", tx, ty);
    printf("A'(%.2f, %.2f)  B'(%.2f, %.2f)  C'(%.2f, %.2f)  D'(%.2f, %.2f)\n",
           translated[0][0], translated[0][1], translated[1][0], translated[1][1],
           translated[2][0], translated[2][1], translated[3][0], translated[3][1]);

    printf("\nAfter rotation by %.1f degrees (about origin):\n", theta_deg);
    printf("A''(%.2f, %.2f)  B''(%.2f, %.2f)  C''(%.2f, %.2f)  D''(%.2f, %.2f)\n",
           rotated[0][0], rotated[0][1], rotated[1][0], rotated[1][1],
           rotated[2][0], rotated[2][1], rotated[3][0], rotated[3][1]);
    printf("==================================\n");
}

// -------------------------------------------------------------------
int main(int argc, char** argv) {
    // Convert rotation angle to radians
    theta_rad = theta_deg * PI / 180.0;

    // Compute transformations
    computeTranslated();
    computeRotated();

    // Print coordinates to console
    printCoordinates();

    // GLUT initialisation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL: Translation (green/cream) + Rotation (55°)");

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}