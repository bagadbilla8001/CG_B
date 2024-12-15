#include <iostream>
#include <cmath>
#include <GL/glut.h>

class KochCurve {
public:
    void drawKochCurve(int it, float x1, float y1, float x5, float y5) {
        if (it == 0) {
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x5, y5);
            glEnd();
        } else {
            float x2, y2, x3, y3, x4, y4;
            float dx = (x5 - x1) / 3;
            float dy = (y5 - y1) / 3;

            x2 = x1 + dx;
            y2 = y1 + dy;

            x3 = 0.5 * (x1 + x5) + sqrt(3) * (y1 - y5) / 6;
            y3 = 0.5 * (y1 + y5) + sqrt(3) * (x5 - x1) / 6;

            x4 = 2 * dx + x1;
            y4 = 2 * dy + y1;

            drawKochCurve(it - 1, x1, y1, x2, y2);
            drawKochCurve(it - 1, x2, y2, x3, y3);
            drawKochCurve(it - 1, x3, y3, x4, y4);
            drawKochCurve(it - 1, x4, y4, x5, y5);
        }
    }
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    KochCurve k;
    int it;

    std::cout << "Enter Number Of Iterations: " << std::endl;
    std::cin >> it;

    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    k.drawKochCurve(it, 0, 100, 600, 100); // Adjust the coordinates for your window size

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set window size as needed
    glutCreateWindow("Koch Curve");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set the coordinate system

    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
