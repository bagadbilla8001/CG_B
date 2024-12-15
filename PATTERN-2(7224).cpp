#include<bits/stdc++.h>
#include <GLUT/glut.h>
#include<math.h>
int width = 800, height = 800;
int cx=400,cy=400;
float r=142;


void drawLine(int x1, int y1, int x2, int y2)
{
  glLineWidth(5);
  glBegin(GL_LINES);
  glVertex2i(x1, y1);
  glVertex2i(x2, y2);
  glEnd();
  glFlush();
}

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x+cx, y+cy);
    glEnd();
}

void midPointCircleAlgo()
{
    int x = 0,y = r;
    float decision = 5/4 - r;
    plot(x, y);
    while (y > x)
    {
        if (decision < 0)
        {
            x++;decision += 2*x+1;
        }
        else
        {
            y--; x++; decision += 2*(x-y)+1;
        }
        plot(x, y);plot(x, -y);plot(-x, y);plot(-x, -y);plot(y, x);plot(-y, x);plot(y, -x);plot(-y, -x);
    }

}
void display()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(0.5, 0.75, 0.25);
  glClear(GL_COLOR_BUFFER_BIT);
  
  drawLine(200,600,600,600);
  drawLine(200,200,600,200);
  drawLine(200,200,200,600);
  drawLine(600,200,600,600);
  glLineWidth(2);
  
  glColor3f(0.0, 1.0, 1.0);
  drawLine(200,400,400,200);drawLine(400,200,600,400);drawLine(600,400,400,600);drawLine(400,600,200,400);
  
  glColor3f (1.0, 1.0, 1.0);
  glPointSize(2.0);
  midPointCircleAlgo();

  glFlush();
}


void myinit()
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,(GLdouble)width,0.0,(GLdouble)height);
  glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width,height);
  glutCreateWindow("Pattern");
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();
  return 0;
}