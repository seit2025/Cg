#include <GL/glut.h>

// Fill color and boundary color
float fillColor[3] = {1.0, 0.0, 0.0};  // Red
float boundaryColor[3] = {0.0, 0.0, 0.0};  // Black

void floodFill(int x, int y) {
    float pixelColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixelColor);

    // Check if the pixel isn't the fill color or boundary color
    if ((pixelColor[0] != boundaryColor[0] || pixelColor[1] != boundaryColor[1] || pixelColor[2] != boundaryColor[2]) &&
        (pixelColor[0] != fillColor[0] || pixelColor[1] != fillColor[1] || pixelColor[2] != fillColor[2])) {

        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursively call neighbors
        floodFill(x + 1, y); // Right
        floodFill(x - 1, y); // Left
        floodFill(x, y + 1); // Up
        floodFill(x, y - 1); // Down
    }
}

void drawPolygon() {
    glColor3f(0.0, 0.0, 0.0); // Boundary color (Black)
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 200);
    glVertex2i(300, 200);
    glVertex2i(300, 300);
    glVertex2i(200, 300);
    glEnd();
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert coordinates for OpenGL
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        floodFill(x, windowHeight - y);
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background to white
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Flood Fill Algorithm");
    init();

    glutDisplayFunc(drawPolygon);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}