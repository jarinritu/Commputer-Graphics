#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <map>
#include <vector>

double x2,y2,x3,y3 , xmin,xmax,ymax,ymin,xvmax,yvmax,xvmin,yvmin;
int test(double p,double q,double *t1,double *t2) //calculate t1, t2 . if p<0 ,t1={t,0} . line is putside the boundary

{
    double t=q/p;
    if(p<0.0)
    {
        if(t> *t1) *t1=t;
        if(t> *t2) return(false);

    }
    // if p>0 t2={t,1} . line is inside the boundary
    else if(p>0.0)
    {
        if(t< *t2) *t2=t;
        if(t< *t1) return(false);
    }
    //if p==0 , then line is parallel to tth boundary

    else if(p==0.0)
    {
        if(q<0.0) return(false);
    }
    return(true);
}

void Liang_Barsky(double x0,double y0,double x1,double y1) //function to calculate values through liang barsky method

{
         //calculate dx and dy .
    double dx=x1-x0,dy=y1-y0,te=0.0,tl=1.0;
    if(test(-dx,x0-xmin,&te,&tl))
    if(test(dx,xmax-x0,&te,&tl))
    if(test(-dy,y0-ymin,&te,&tl))
    if(test(dy,ymax-y0,&te,&tl))
    {
             /* if t1<1 then calculate x1=x0+t1*dx; y1=y0+t1*dy;  */

        if(tl<1.0){x1=x0+tl*dx;y1=y0+tl*dy;}
        if(te>0.0){x0=x0+te*dx;y0=y0+te*dy;}
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
     }
}

void display() //function to pisplay the program

{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);//Clipped line is displayed in yellow
    glBegin(GL_LINES);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    Liang_Barsky(x2,y2,x3,y3);
    glFlush();
}
void myinit()

{
    /* window color is megenta */
    glClearColor(1.0,1.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc, char *argv[])//Take input of boundary and viewport
{
printf("Enter the X-max of the boundary: ");
    scanf("%lf", &xmax);
    printf("Enter the Y-max of the boundary: ");
    scanf("%lf", &ymax);
    printf("Enter the X-min of the boundary: ");
    scanf("%lf", &xmin);
    printf("Enter the Y-min of the boundary: ");
    scanf("%lf", &ymin);
    printf("Enter the X-max of the viewport: ");
    scanf("%lf", &xvmax);
    printf("Enter the Y-max of the viewport: ");
    scanf("%lf", &yvmax);
    printf("Enter the X-min of the viewport: ");

    scanf("%lf", &xvmin);
    printf("Enter the Y-min of the viewport: ");

    scanf("%lf", &yvmin);
    printf("Enter the end points of the line: ");
    scanf("%lf%lf%lf%lf", &x2,&y2,&x3,&y3);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Line Clipping");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}

