#include <GL/glut.h>
#include <cmath>
#include <iostream>

struct Point {
    int x, y;
};

// Global variables to store first and second click points
Point firstClick = {-1, -1};  // First click (center of the circle)
Point secondClick = {-1, -1}; // Second click (a point on the circumference)

// Bresenham's Circle Drawing Algorithm
void bresenhamCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Draw the eight symmetric points of the circle
        glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
        glEnd();

        x++;

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
    glPointSize(2.0);                    // Set point size for drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // Set 2D orthographic projection
}

// Display function to clear the screen and draw the circle
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // If both clicks have been made, calculate the radius and draw the circle
    if (firstClick.x != -1 && secondClick.x != -1) {
        // Calculate the radius as the distance between the first and second click
        int radius = static_cast<int>(sqrt(pow(secondClick.x - firstClick.x, 2) + pow(secondClick.y - firstClick.y, 2)));

        // Call Bresenham's circle drawing algorithm to draw the circle
        bresenhamCircle(firstClick.x, firstClick.y, radius);
    }

    glFlush();  // Render the OpenGL output
}

// Mouse callback function to handle mouse click events
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick.x == -1) {
            // Store the first click position (center of the circle)
            firstClick.x = x;
            firstClick.y = 500 - y;  // Convert to OpenGL coordinates (flip y-axis)
        } else if (secondClick.x == -1) {
            // Store the second click position (a point on the circumference)
            secondClick.x = x;
            secondClick.y = 500 - y;  // Convert to OpenGL coordinates (flip y-axis)

            // After the second click, trigger redisplay to draw the circle
            glutPostRedisplay();
        }
    }
}

// Main function to set up the window and OpenGL loop
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffering and RGB color model
    glutInitWindowSize(500, 500);                // Set window size
    glutCreateWindow("Bresenham Circle Algorithm in OpenGL");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register display callback function
    glutMouseFunc(mouse);      // Register mouse callback function to handle mouse clicks

    glutMainLoop();            // Start the OpenGL main loop

    return 0;
}
