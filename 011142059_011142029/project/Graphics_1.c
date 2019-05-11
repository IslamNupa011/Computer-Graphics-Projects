#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <windows.h>
#include <glut.h>
double x=10;
double y=0,c=0.05;
int flag=1;
double theta;
void display()
{
	//clear the display
	//color black
	glClearColor(0, 0, 0, 0);

	//clear buffers to preset values
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/***************************
	/ set-up camera (view) here
	****************************/

	//load the correct matrix -- MODEL-VIEW matrix
	//specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?
	gluLookAt(0,0,100,	0,0,0,	0,1,0);


	glColor3f(1, 0, 0);
	 double PI_2=2*acos(-1);
	 double t=0;
	 double a= 0.002;
	 double r=15;



   glBegin(GL_TRIANGLES);
   {
       /*for(t=0;t<=PI_2; t+=a)
        {
        glVertex3f(0,0,0);
        glVertex3f(r*cos(t-a),r*sin(t-a),0);
        glVertex3f(r*cos(t),r*sin(t),0);
       }*/
    /* for(t=0;t<=PI_2; t+=a)
        {
        glVertex3f(10,-20,0);
        glVertex3f(10+r*cos(t-a),20+r*sin(t-a),0);
        glVertex3f(10+r*cos(t),20+r*sin(t),0);
       }*/
        for(t=0;t<=PI_2; t+=a)
        {
        glVertex3f(x,y,0);
        glVertex3f(x+r*cos(t-a),y+r*sin(t-a),0);
        glVertex3f(x+r*cos(t),y+r*sin(t),0);
       }
   }
   glEnd();
glColor3f(0,128,0);
	glBegin(GL_QUADS);
	{

        glVertex3f(-30, -20, 0);
	    glVertex3f(30, -20, 0);
	  glVertex3f(30, 20, 0);
	   glVertex3f(-30, 20, 0);
	}
   glEnd();

	/*glBegin(GL_QUADS);
	{
	    // glVertex3f(0, 0, 0);
	    //glVertex3f(20, 0, 0);
	  //  glVertex3f(20, 30, 0);
	   // glVertex3f(0, 30, 0);


  glVertex3f(-25, 0, 0);
	    glVertex3f(25, 0, 0);
	  glVertex3f(20, 30, 0);
	   glVertex3f(20, 30, 0);




	}
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	{

        /*glVertex3f(0, 0, 0);
	    glVertex3f(30, 30, 30);
	    glVertex3f(0, 30, 0);
	    glVertex3f(30, 20, 30);*/
	     /*glVertex3f(-30, 0, 0);
	    glVertex3f(30, 0, 0);
	  glVertex3f(30, 20, 0);
	   glVertex3f(-30, 20, 0);
	}*/


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate()
{
	//codes for any changes in Models, Camera

	//this will call the display AGAIN

	/*if(flag==1){
       c+=0.1;

   if(c>80){
        flag=0;
	}
	}

	if(flag==0){
       c-=0.1;

   if(c<0){
        flag=1;
	}
}*/
/*if(x<0 || x>50){
    flag*=-1;
}
x+=(flag*c);*/
theta+=0.005;
x=30*cos(theta);
y=30*sin(theta);


	glutPostRedisplay();
}

void init()
{
	//clear the screen
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/

	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*
	gluPerspective() — set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}

int main(int argc, char **argv)
{
	//initialize the GLUT library
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("First_Lab!");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

