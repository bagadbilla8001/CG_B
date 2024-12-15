
//HILBERT CURVE IMPLEMENTATION...
#include<windows.h>
#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

int n;
int a=-350, b=-250;
int x,y,h=10,r=2,d=3,l=4,u=1;

void moveto(int j,int h,int &x,int &y)
{
    if(j==1)
        y-=h;
    else if(j==2)
        x+=h;
    else if(j==3)
        y+=h;
    else if(j==4)
        x-=h;

    glVertex2f(x,y);
}



void hilbert(int r,int d,int l,int u,int i,int h,int &x,int &y)
{
    if(i>0) //ITERABLE FACTOR
    {
        i--;
        hilbert(d,r,u,l,i,h,x,y);
        moveto(r,h,x,y);

        hilbert(r,d,l,u,i,h,x,y);
        moveto(d,h,x,y);

        hilbert(r,d,l,u,i,h,x,y);
        moveto(l,h,x,y);

        hilbert(u,l,d,r,i,h,x,y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.25, 1.0, 0.5);
    x=a;y=b;
    cout << "ENTER NUMBER OF ITERATIONS:- ";
    cin >> n;

    moveto(a,b,x,y);
    hilbert(r, d, l, u, n, h, x, y);
    glEnd();
    glFlush();
}


void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);
    glFlush();
}

int main(int argc,char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(50,50);

    glutCreateWindow("CURVE");

    glutDisplayFunc(display);

    init();
    glutMainLoop();
}
