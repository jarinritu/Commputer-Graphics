#include <iostream>
#include<windows.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

 int screenheight = 600;
 int screenwidth = 800;
 bool flag = true;

 int X1,Y1,X2,Y2 ;
 int xmin, ymin, xmax, ymax, sz;

 void DrawRect(int x0, int y0, int x1, int y1)
 {
      glClear(GL_COLOR_BUFFER_BIT);
      glRecti(x0,y0,x1,y1);
      glFlush();
 }

 void DrawLineSegment(int x0, int y0, int x1, int y1){
      glColor3d(0,0,0);
      glBegin(GL_LINES);
           glVertex2i(x0,y0);
           glVertex2i(x1,y1);
      glEnd();
      glFlush();
 }

 typedef int OutCode;

 const int INSIDE = 0; // 0000
 const int BOTTOM = 1;  // 0001
 const int RIGHT = 2; // 0010
 const int TOP = 4; // 0100
 const int LEFT = 8;  // 1000

 OutCode ComputeOutCode(int x, int y)
 {
      OutCode code;

      code = INSIDE;     // initialised as being inside of clip window

      if (x < xmin)      // to the left of clip window
           code |= LEFT;
      else if (x > xmax)      // to the left of clip window
           code |= RIGHT;
      else if (y < ymin)      // to the left of clip window
           code |= BOTTOM;// Complete the code segment here
      else if (y > ymax)      // to the left of clip window
           code |= TOP;
 return(code);
 }

 void lineclip(int x0,int y0,int x1,int y1) {
  OutCode code0,code1;
  int midx,midy;

  if(abs(x0-x1)==1 && abs(y0-y1)==1) /*Adjacent points */
   return;

  code0=ComputeOutCode(x0,y0);
  code1=ComputeOutCode(x1,y1);
  if( !(code0 | code1) ) { /*The two points are completely inside the window*/
   DrawLineSegment(x0,y0,x1,y1);
   return;
  }
  else if(code0 & code1) /*The two points are completely outside the window.*/
           return ;

  midx=(x0+x1)/2;
  midy=(y0+y1)/2;
  //lineclip(midx,midy,x1,y1);
  lineclip(x0,y0,midx,midy);
 }


 void myDisplay()
 {
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //black
      glClear(GL_COLOR_BUFFER_BIT);

      glColor3f(1,0,0);
      DrawRect(xmin,ymin,xmax,ymax);

      //glcolor

     // glColor3f(0,0,0);
      DrawLineSegment(X1,Y1,X2,Y2);

      glFlush();
 }

 void myKey(unsigned char key,int x,int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(key=='c')
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1,0,0);
        DrawRect(xmin,ymin,xmax,ymax);

        glColor3f(0.0,0.0,0.0);
        glFlush();
        lineclip(X1,Y1,X2,Y2);
    }
}

 int main( int argc, char ** argv ) {

      glutInit( &argc, argv );


      printf("Enter the lower corner and upper corner of window:\n");
      scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);

      printf("Enter the two points of line:\n");
      scanf("%d %d %d %d",&X1,&Y1,&X2,&Y2);

      glutInitWindowPosition( 0, 0 );
      glutInitWindowSize( 800, 600 );



      // create window
      glutCreateWindow( "midpoint subdivision method Clipping" );

      // set the view frustum
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      gluOrtho2D( 0, 800, 0, 600 );


      // clear rendering surface
      glViewport(0, 0, 800, 600);

      glutDisplayFunc( myDisplay );
      glutKeyboardFunc(myKey);
      glutMainLoop();

      return( 0 );
 }
