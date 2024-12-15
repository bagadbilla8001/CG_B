//#include<windows.h>
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<bits/stdc++.h>
using namespace std ;
int m[20][3] , n = 0 ;
void setpcolor(double r1, double b1 , double g1 ){
    glColor3f(r1,b1,g1);
}

void conect(int x , int y , int px , int py){

    glPointSize(2);
    glBegin(GL_LINE_STRIP);
        glVertex2i(x,y);
        glVertex2i(px,py);
    glEnd();
    glFlush();
}

void translation(int tx,int ty){//cout << tx<<ty;
    int tm[3][3] = {{1,0,tx},{0,1,ty},{0,0,1} } ,ne[3]={} ;
     for(int i=0 ;i<n;i++){
        ne [0]  = tm[0][0]*m[i][0] + tm[0][1]*m[i][1] + tm[0][2]*m[i][2] ;
        ne [1]  = tm[1][0]*m[i][0] + tm[1][1]*m[i][1] + tm[1][2]*m[i][2] ;
        ne [2]  = tm[2][0]*m[i][0] + tm[2][1]*m[i][1] + tm[2][2]*m[i][2] ;
        m[i][0] = ne[0] ; m[i][1] = ne[1] ; m[i][2] = ne[2] ;
    }
     for(int i=0 ;i<n;i++){
        int ni = (i+1)%n;
        setpcolor(1,1,0) ;
        conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
    }


}

void rotation(double rot ){//cout << tx<<ty;
    double pi = 3.14159265 ;
    double rad = (pi/180.00) ;   rad *= rot ;
    double rm[3][3] = {{cos(rad),-sin(rad),1},{sin(rad),cos(rad),1},{0,0,1} } ;
    int ne[3]={} ;
    for(int i=0 ;i<n;i++){
        ne [0]  = rm[0][0]*m[i][0] + rm[0][1]*m[i][1] + rm[0][2]*m[i][2] ;
        ne [1]  = rm[1][0]*m[i][0] + rm[1][1]*m[i][1] + rm[1][2]*m[i][2] ;
        ne [2]  = rm[2][0]*m[i][0] + rm[2][1]*m[i][1] + rm[2][2]*m[i][2] ;
        m[i][0] = ne[0] ; m[i][1] = ne[1] ; m[i][2] = ne[2] ;
    }
     for(int i=0 ;i<n;i++){
        int ni = (i+1)%n;
        setpcolor(1,1,0) ;
        conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
    }
}

void shear(double shx , double shy ){//cout << tx<<ty;
    double sm[3][3] = {{1,shx,0},{shy,1,0},{0,0,1} } ;
    double ne[3]={} ;
    for(int i=0 ;i<n;i++){
        ne [0]  = sm[0][0]*m[i][0] + sm[0][1]*m[i][1] + sm[0][2]*m[i][2] ;
        ne [1]  = sm[1][0]*m[i][0] + sm[1][1]*m[i][1] + sm[1][2]*m[i][2] ;
        ne [2]  = sm[2][0]*m[i][0] + sm[2][1]*m[i][1] + sm[2][2]*m[i][2] ;
        m[i][0] = ne[0] ; m[i][1] = ne[1] ; m[i][2] = ne[2] ;
    }
     for(int i=0 ;i<n;i++){
        int ni = (i+1)%n;
        setpcolor(1,1,0) ;
        conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
    }
}
void scale(int sx , int sy ){//cout << tx<<ty;
    int sm[3][3] = {{sx,0,0},{0,sy,0},{0,0,1} } ;
    int ne[3]={} ;
    for(int i=0 ;i<n;i++){
        ne [0]  = sm[0][0]*m[i][0] + sm[0][1]*m[i][1] + sm[0][2]*m[i][2] ;
        ne [1]  = sm[1][0]*m[i][0] + sm[1][1]*m[i][1] + sm[1][2]*m[i][2] ;
        ne [2]  = sm[2][0]*m[i][0] + sm[2][1]*m[i][1] + sm[2][2]*m[i][2] ;
        m[i][0] = ne[0] ; m[i][1] = ne[1] ; m[i][2] = ne[2] ;
    }
     for(int i=0 ;i<n;i++){
        int ni = (i+1)%n;
        setpcolor(1,1,0) ;
        conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
    }
}
void reflect(char c){//cout << tx<<ty;
    int sm[3][3] = {{1,0,0},{0,1,0},{0,0,1} } ;
    if(c=='x'||c=='X') { sm[1][1]=-1 ; }
    else { sm[0][0] = - 1 ; }
    int ne[3]={} ;
    for(int i=0 ;i<n;i++){
        ne [0]  = sm[0][0]*m[i][0] + sm[0][1]*m[i][1] + sm[0][2]*m[i][2] ;
        ne [1]  = sm[1][0]*m[i][0] + sm[1][1]*m[i][1] + sm[1][2]*m[i][2] ;
        ne [2]  = sm[2][0]*m[i][0] + sm[2][1]*m[i][1] + sm[2][2]*m[i][2] ;
        m[i][0] = ne[0] ; m[i][1] = ne[1] ; m[i][2] = ne[2] ;
    }
     for(int i=0 ;i<n;i++){
        int ni = (i+1)%n;
        setpcolor(1,1,0) ;
        conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
    }
}


void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(-250,250,-250,250) ;
	glFlush() ;
}
void display(){
    glFlush() ;
}

int flg = 1 ;
void menu(int c){
    flg++ ;
        for(int i=0 ;i<n;i++){
            int ni = (i+1)%n;
            setpcolor(1,1,1) ;
            conect(m[i][0],m[i][1],m[ni][0],m[ni][1]) ;
        }
        glFlush() ;//glFlush() ;

    if(c==1){
        int tx = 0 , ty = 0 ;
        cout <<"Enter x-translation factor :  " ; cin >> tx ;
        cout <<"Enter y-translation factor :  " ; cin >> ty ;
        translation(tx,ty) ;
    }
    else if(c==2) {
        double rot ;
        int flg = 1 ;
        cout <<"Enter 1 for clockwise else enter 0 for anti-clock wise :  " ; cin >> flg ;
        cout <<"Enter by how much degree the object is to be rotated :  " ; cin >> rot ;
        if(flg){
            rot = -rot ;
        }
        rotation(rot) ;
    }
    else if(c==3) {
            int sx = 1 , sy = 1 ;
        cout <<"Enter the horizontal scaling factor :  " ; cin >> sx ;
        cout <<"Enter the vertical scaling factor :  " ; cin >> sy ;
        scale(sx,sy) ;
    }
    else if(c==4) {
        char c ;
        cout <<"Enter the axis of reflection :  " ; cin >> c ;
        reflect(c) ;
    }
    else if(c==5) {
        double sx = 0 , sy = 0 ;
        cout <<"Enter the horizontal shearing factor :  " ; cin >> sx ;
        cout <<"Enter the vertical shearing factor :  " ; cin >> sy ;
        shear(sx,sy) ;
    }

}

void mouse(int but , int state , int cx , int cy ){
    cx  -= 250 ; cy  -= 250 ; cy = - cy ;
    if( but == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flg==1 ){
        m[n][0] = cx ; m[n][1] = cy ; m[n][2] = 1 ;
        n++ ;
        glColor3f(1,0.0,0);
            glPointSize(3.0);
            glBegin (GL_POINTS);
            glVertex2f(cx,cy);
        glEnd();
         glFlush() ;
    }

}


int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
	glutInitWindowPosition(1000,150);
	glutCreateWindow(" Polygon ");
    cout << "Left Click to select a vertex , Right click to open the menu \n\n";
	init();

	glutDisplayFunc(display);

    glutMouseFunc(mouse);

     glutCreateMenu(menu);
        glutAddMenuEntry("TRANSLATION",1);
        glutAddMenuEntry("ROTATION",2);
        glutAddMenuEntry("REFLECTION",4);
        glutAddMenuEntry("SCALING",3);
        glutAddMenuEntry("SHEARING",5);
     glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();
	return 0;

}
