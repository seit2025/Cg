#include <GL/glut.h>
#include <iostream>

#define WIDTH 500
#define HEIGHT 500

int x1, startY, x2, y2;  // Renamed y1 to startY

void setPixel(int x, int y) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenhamLine(int x1, int startY, int x2, int y2) {  // Renamed y1 to startY
    int dx = abs(x2 - x1);
    int dy = abs(y2 - startY);  // Renamed y1 to startY
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (startY < y2) ? 1 : -1;  // Renamed y1 to startY
    int err = dx - dy;

    while (true) {
        setPixel(x1, startY);  // Renamed y1 to startY
        if (x1 == x2 && startY == y2) break;  // Renamed y1 to startY
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            startY += sy;  // Renamed y1 to startY
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing a line between the user-input points using Bresenham's algorithm
    bresenhamLine(x1, startY, x2, y2);  // Renamed y1 to startY

    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

int main(int argc, char** argv) {
    // Prompt the user for input
    std::cout << "Enter the coordinates for the start point (x1 y1): ";
    std::cin >> x1 >> startY;  // Renamed y1 to startY
    std::cout << "Enter the coordinates for the end point (x2 y2): ";
    std::cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bresenham Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}