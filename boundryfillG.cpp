#include <GL/glut.h>
#include <iostream>

using namespace std;

// Initialize the OpenGL window
void myInit()
{
    gluOrtho2D(0, 500, 0, 500);
    glClearColor(1, 1, 1, 1);  // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glColor3f(0, 1, 0);  // Set the default boundary color to green
}

// Function to plot a single pixel
void plotPixel(int x, int y, float* fill_color)
{
    glColor3f(fill_color[0], fill_color[1], fill_color[2]);  // Set the color for the pixel

    glBegin(GL_POINTS);  // Begin drawing points
        glVertex2i(x, y);  // Draw the pixel at coordinates (x, y)
    glEnd();

    glFlush();  // Flush the drawing to the window
}

// Boundary Fill Algorithm
void boundaryFill(int x, int y, float* fill_color, float* boundary_color)
{
    float current[3];  // Array to store the current color at a pixel

    // Read the color of the current pixel at (x, y)
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, current);

    // If the current pixel is not the boundary or fill color, fill it and recurse
    if((current[0] != boundary_color[0] || current[1] != boundary_color[1] || current[2] != boundary_color[2]) &&
       (current[0] != fill_color[0] || current[1] != fill_color[1] || current[2] != fill_color[2]))
    {
        plotPixel(x, y, fill_color);  // Fill the current pixel with the fill color
        // Recurse for the four neighboring pixels (right, up, left, down)
        boundaryFill(x , y + 1, fill_color, boundary_color);  // Right
        boundaryFill(x + 1, y, fill_color, boundary_color);  // Up
        boundaryFill(x , y -1, fill_color, boundary_color);  // Left
        boundaryFill(x-1, y, fill_color, boundary_color);  // Down
    }
}

// Function to draw a square shape and apply boundary fill
void squareShape()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    // Drawing a square with the following coordinates
    glBegin(GL_LINE_LOOP);
        glVertex2i(100, 100);  // Bottom-left corner
        glVertex2i(400, 100);  // Bottom-right corner
        glVertex2i(400, 400);  // Top-right corner
        glVertex2i(100, 400);  // Top-left corner
    glEnd();

    glFlush();  // Flush the drawing

    // Define boundary and fill colors
    float boundary_color[3], fill_color[3];

    // Set boundary color to green (RGB: 0, 1, 0)
    boundary_color[0] = 0;
    boundary_color[1] = 1;
    boundary_color[2] = 0;

    // Set fill color to blue (RGB: 0, 0, 1)
    fill_color[0] = 0;
    fill_color[1] = 0;
    fill_color[2] = 1;

    // Start boundary fill from a point inside the square (e.g., (102, 102))
    boundaryFill(102, 102, fill_color, boundary_color);
}

// Main function to set up the window and start the program
int main(int argc, char **argv)
{
   glutInit(&argc, argv);  // Initialize GLUT
   glutInitWindowSize(500, 500);  // Set the window size
   glutInitWindowPosition(400, 150);  // Set window position
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Set display mode
   glutCreateWindow("Boundary Fill - Square");  // Create window with title

   myInit();  // Initialize OpenGL settings
   glutDisplayFunc(squareShape);  // Register the display function

   glutMainLoop();  // Start the GLUT main loop
   return 0;
}
