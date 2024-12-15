#include<windows.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
#include<vector>
#include<math.h>

using namespace std;

int AX,AY,r;

class PATT
{
public:
    void drawCircle(int AX,int AY,int x,int y);
    void BresenhamCircle(int AX,int AY,int r);
    void Pattern(int AX,int AY,int r);
    void dda_line(int,int,int,int);
}p;

void PATT:: drawCircle(int AX,int AY,int x,int y){
    glColor3f(0,0.125,1);
    glBegin(GL_POINTS);
    glVertex2i(AX+x,AY+y);
    glVertex2i(AX+x,AY-y);
    glVertex2i(AX-x,AY+y);
    glVertex2i(AX-x,AY-y);
    glVertex2i(AX+y,AY+x);
    glVertex2i(AX+y,AY-x);
    glVertex2i(AX-y,AY+x);
    glVertex2i(AX-y,AY-x);
    glEnd();
}

void PATT:: BresenhamCircle(int AX,int AY,int r){
    int x=0,y=r,d;
    d=3-2*r;

    while(x<=y){
        if(d>0){
            x++;
            y--;
            d+=4*x-4*y+10;
        }
        else{
            x++;
            d+=4*x+6;
        }
        drawCircle(AX,AY,x,y);
    }
}

void PATT::dda_line(int Xi,int Yi,int Xf,int Yf)
{
    glPointSize(1.0);
    double dx=(Xf-Xi),dy=(Yf-Yi);
    double steps;
    float xInc,yInc,x=Xi,y=Yi;
    steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));

    xInc=dx/(float)steps;
    yInc=dy/(float)steps;
    glLineWidth(10.0);
    glVertex2f(x,y);
    for(int k=0;k<steps;k++)
    {
      x+=xInc;
      y+=yInc;
     glVertex2f(x,y);
  }
}
void PATT:: Pattern(int AX,int AY,int r){
    BresenhamCircle(AX,AY,r);
    glBegin(GL_POINTS);
    p.dda_line(AX,AY-r,AX+r*0.866,AY+r*0.5);
    p.dda_line(AX+r*0.866,AY+r*0.5,AX-r*0.866,AY+r*0.5);
    p.dda_line(AX-r*0.866,AY+r*0.5,AX,AY-r);
    glEnd();
    BresenhamCircle(AX,AY,r/2);
}


void init(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,0);
    gluOrtho2D(-440,640,480,-480);
    glMatrixMode(GL_PROJECTION);
}

void display(){
    glPointSize(1);
    glBegin(GL_POINTS);
    p.Pattern(AX,AY,r);
    glEnd();
    glFlush();
}

void MOUSE(int button,int state,int x,int y){
    glColor3f(0,0,1);
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        AX=x;
        AY=y;
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();
        r=sqrt((AX-x)*(AX-x) + (AY-y)*(AY-y));
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}


int main(int argc,char* argv[]){
    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("Circle Pattern");
    init();
    glutMouseFunc(MOUSE);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
