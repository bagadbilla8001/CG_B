#include <windows.h>
#include <GL/glut.h>
#include <vector>
using namespace std;

const int CODE_INSIDE = 0;
const int CODE_LEFT = 1;
const int CODE_RIGHT = 2;
const int CODE_BOTTOM = 4;
const int CODE_TOP = 8;


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CLIP_MIN_X = 100, CLIP_MIN_Y = 100, CLIP_MAX_X = 700, CLIP_MAX_Y = 500;


struct LineSegment {
    int startX, startY, endX, endY;
};

vector<LineSegment> lineSegments;

// Function prototypes
void renderScene();
void handleMouse(int button, int state, int x, int y);
void clipLineSegments();
void clipLine(int &startX, int &startY, int &endX, int &endY);
int getOutcode(int x, int y);

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping rectangle in green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(CLIP_MIN_X, CLIP_MIN_Y);
    glVertex2i(CLIP_MAX_X, CLIP_MIN_Y);
    glVertex2i(CLIP_MAX_X, CLIP_MAX_Y);
    glVertex2i(CLIP_MIN_X, CLIP_MAX_Y);
    glEnd();

    // Draw line segments in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (const auto& segment : lineSegments) {
        glVertex2i(segment.startX, segment.startY);
        glVertex2i(segment.endX, segment.endY);
    }
    glEnd();

    glFlush();
}

void handleMouse(int button, int state, int x, int y) {
    static bool firstClick = true;
    static LineSegment currentSegment;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick) {
            currentSegment.startX = x;
            currentSegment.startY = y;
            firstClick = false;
        } else {
            currentSegment.endX = x;
            currentSegment.endY = y;
            lineSegments.push_back(currentSegment);
            firstClick = true;
        }
        glutPostRedisplay();
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        clipLineSegments();
        glutPostRedisplay();
    }
}

void clipLineSegments() {
    for (auto& segment : lineSegments) {
        clipLine(segment.startX, segment.startY, segment.endX, segment.endY);
    }
}

void clipLine(int &startX, int &startY, int &endX, int &endY) {
    int outcode1 = getOutcode(startX, startY);
    int outcode2 = getOutcode(endX, endY);
    bool isAccepted = false;

    while (true) {
        if (!(outcode1 | outcode2)) {
            // Both points inside
            isAccepted = true;
            break;
        } else if (outcode1 & outcode2) {
            // Both points outside
            break;
        } else {
            // At least one point is outside
            int outcodeOut = outcode1 ? outcode1 : outcode2;
            int x, y;

            if (outcodeOut & CODE_TOP) { // Point is above the clip rectangle
                x = startX + (endX - startX) * (CLIP_MAX_Y - startY) / (endY - startY);
                y = CLIP_MAX_Y;
            } else if (outcodeOut & CODE_BOTTOM) { // Point is below the clip rectangle
                x = startX + (endX - startX) * (CLIP_MIN_Y - startY) / (endY - startY);
                y = CLIP_MIN_Y;
            } else if (outcodeOut & CODE_RIGHT) { // Point is to the right of clip rectangle
                y = startY + (endY - startY) * (CLIP_MAX_X - startX) / (endX - startX);
                x = CLIP_MAX_X;
            } else if (outcodeOut & CODE_LEFT) { // Point is to the left of clip rectangle
                y = startY + (endY - startY) * (CLIP_MIN_X - startX) / (endX - startX);
                x = CLIP_MIN_X;
            }

            if (outcodeOut == outcode1) {
                startX = x;
                startY = y;
                outcode1 = getOutcode(startX, startY);
            } else {
                endX = x;
                endY = y;
                outcode2 = getOutcode(endX, endY);
            }
        }
    }
    if (!isAccepted) {
        startX = endY = startY = endX = 0;
    }
}

int getOutcode(int x, int y) {
    int outcode = CODE_INSIDE;

    if (x < CLIP_MIN_X) outcode |= CODE_LEFT;
    else if (x > CLIP_MAX_X) outcode |= CODE_RIGHT;
    if (y < CLIP_MIN_Y) outcode |= CODE_BOTTOM;
    else if (y > CLIP_MAX_Y) outcode |= CODE_TOP;

    return outcode;
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Line Clipping with GLUT");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);

    glutDisplayFunc(renderScene);
    glutMouseFunc(handleMouse);

    glutMainLoop();
    return 0;
}
