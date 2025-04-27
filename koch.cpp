#include <GL/glut.h>
#include <cmath>

struct Point {
    float x, y;
};

void drawLine(Point a, Point b) {
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}

void kochCurve(Point a, Point b, int depth) {
    if (depth == 0) {
        drawLine(a, b);
        return;
    }

    Point p1, p2, peak;

    // Divide the line into 3 segments
    p1.x = (2 * a.x + b.x) / 3;
    p1.y = (2 * a.y + b.y) / 3;

    p2.x = (a.x + 2 * b.x) / 3;
    p2.y = (a.y + 2 * b.y) / 3;

    // Calculate the peak of the equilateral triangle
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    peak.x = (p1.x + p2.x) / 2 - sqrt(3) * dy / 2;
    peak.y = (p1.y + p2.y) / 2 + sqrt(3) * dx / 2;

    // Recursive calls for 4 segments
    kochCurve(a, p1, depth - 1);
    kochCurve(p1, peak, depth - 1);
    kochCurve(peak, p2, depth - 1);
    kochCurve(p2, b, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Point start = { -0.9f, 0.0f };
    Point end   = {  0.9f, 0.0f };

    int depth = 2; // You can change depth for more/less detail

    glColor3f(0.0f, 0.5f, 1.0f);
    kochCurve(start, end, depth);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Draw in black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -0.5, 1.0); // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Koch Curve - OpenGL");
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}