#include <GL/glut.h>
#include <cmath>
#include <algorithm>  // Add this line for std::max

#define WIDTH 500
#define HEIGHT 500

// Function to set a pixel at coordinates (x, y)
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to implement the DDA line drawing algorithm
void ddaLine(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(std::abs(dx), std::abs(dy));  // Find the number of steps required
    float xInc = dx / steps;  // Increment for x
    float yInc = dy / steps;  // Increment for y

    float x = x1;
    float y = y1;

    // Loop to plot each pixel along the line
    for (int i = 0; i <= steps; i++) {
        setPixel(round(x), round(y));  // Round to nearest integer and set pixel
        x += xInc;
        y += yInc;
    }
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    glColor3f(0.0, 1.0, 0.0);  // Set color to green

    // Draw a line from (100, 100) to (400, 300)
    ddaLine(100, 100, 400, 300);

    glFlush();  // Ensure all rendering is completed
}

// Initialization function to set up OpenGL environment
void init() {
    glClearColor(0, 0, 0, 1);  // Set background color to black
    gluOrtho2D(0, WIDTH, 0, HEIGHT);  // Set 2D orthogonal projection
}

// Main function where execution starts
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
    glutInitWindowSize(WIDTH, HEIGHT);  // Set window size
    glutCreateWindow("DDA Line Drawing");  // Create window with title

    init();  // Call the init function to set up the environment

    glutDisplayFunc(display);  // Register display callback function
    glutMainLoop();  // Enter the GLUT main loop

    return 0;
}