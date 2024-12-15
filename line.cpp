#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Base class for pixel operations
class Pixel {
public:
    virtual void plot(int x, int y);
};

// Derived class for DDA Line Drawing
class DDA_Line : public Pixel {
public:
    void drawLine(int x0, int y0, int x1, int y1);
};

// Derived class for Bresenham Line Drawing
class Bresenham_Line : public Pixel {
public:
    void drawLine(int x0, int y0, int x1, int y1);
};

// Plot function for Pixel
void Pixel::plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Implementation of DDA Line Algorithm
void DDA_Line::drawLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = max(abs(dx), abs(dy));
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; i++) {
        plot(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

// Implementation of Bresenham Line Algorithm
void Bresenham_Line::drawLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        plot(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int x0, y0, x1, y1;
    cout << "Enter start point (x0, y0): ";
    cin >> x0 >> y0;
    cout << "Enter end point (x1, y1): ";
    cin >> x1 >> y1;

    char choice;
    cout << "Choose Algorithm: D for DDA, B for Bresenham: ";
    cin >> choice;

    if (choice == 'D' || choice == 'd') {
        DDA_Line dda;
        dda.drawLine(x0, y0, x1, y1);
    } else if (choice == 'B' || choice == 'b') {
        Bresenham_Line bres;
        bres.drawLine(x0, y0, x1, y1);
    } else {
        cout << "Invalid choice!";
    }

    glFlush();
}

void initialize() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Drawing using DDA and Bresenham");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
