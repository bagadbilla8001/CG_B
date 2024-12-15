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

// Derived class for DDA Circle Drawing
class DDA_Circle : public Pixel {
public:
    void drawCircle(int xc, int yc, int radius);
};

// Derived class for Bresenham Circle Drawing
class Bresenham_Circle : public Pixel {
public:
    void drawCircle(int xc, int yc, int radius);
};

// Plot function for Pixel
void Pixel::plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Implementation of DDA Circle Algorithm
void DDA_Circle::drawCircle(int xc, int yc, int radius) {
    float x = radius, y = 0;
    float theta = 0, increment = 1.0 / radius;

    while (theta <= M_PI / 4) {
        plot(round(xc + x), round(yc + y));
        plot(round(xc - x), round(yc + y));
        plot(round(xc + x), round(yc - y));
        plot(round(xc - x), round(yc - y));
        plot(round(xc + y), round(yc + x));
        plot(round(xc - y), round(yc + x));
        plot(round(xc + y), round(yc - x));
        plot(round(xc - y), round(yc - x));

        theta += increment;
        x = radius * cos(theta);
        y = radius * sin(theta);
    }
}

// Implementation of Bresenham Circle Algorithm
void Bresenham_Circle::drawCircle(int xc, int yc, int radius) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc, yc, radius;
    cout << "Enter center (xc, yc): ";
    cin >> xc >> yc;
    cout << "Enter radius: ";
    cin >> radius;

    char choice;
    cout << "Choose Algorithm: D for DDA, B for Bresenham: ";
    cin >> choice;

    if (choice == 'D' || choice == 'd') {
        DDA_Circle dda;
        dda.drawCircle(xc, yc, radius);
    } else if (choice == 'B' || choice == 'b') {
        Bresenham_Circle bres;
        bres.drawCircle(xc, yc, radius);
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
    glutCreateWindow("Circle Drawing using DDA and Bresenham");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
