#include<bits/stdc++.h>
#include <GL/gl.h>
#include<GL/glut.h>
#//include<windows.h>
using namespace std;

int width = 640, height = 480;
GLint n;
class kcurve{
public:
    GLfloat oldx=-0.25,oldy=0.25;
    void koch(GLfloat dir,GLfloat len,GLint n) ;
}k;

void kcurve::koch(GLfloat dir,GLfloat len,GLint n) {
	GLdouble dirRad = 0.0174533 * dir;
	GLfloat nX = oldx + len * cos(dirRad);
	GLfloat nY = oldy + len * sin(dirRad);
	if (n==0) {
		glVertex2f(oldx, oldy);
		glVertex2f(nX, nY);
		oldx = nX;
		oldy = nY;
	}
	else {
		n--;
		koch(dir, len, n);
		dir += 60.0;
		koch(dir, len, n);
		dir -= 120.0;
		koch(dir, len, n);
		dir += 60.0;
		koch(dir, len, n);
	}
	glutPostRedisplay();
}

void display(){
	 glClear( GL_COLOR_BUFFER_BIT );
	 glBegin(GL_LINES);
	 glColor3f(0.0, 1.0, 0.5);
	 GLfloat len = (1.0)/pow(2, 1.75*n); 
	 k.koch(0.0, len, n);
	 k.koch(-120.0, len, n);
	 k.koch(120.0, len, n);
	 glEnd();
	 glFlush();
}

int main(int argc,char** argv)
{
    cout<<" Enter number iterations : ";
    cin>>n;
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Koch Snowflake Generation");
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}


