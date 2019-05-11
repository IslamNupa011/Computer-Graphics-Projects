#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <windows.h>
#include <glut.h>

double A=0;
double B=0;

void drawRect(double L)
{
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
}

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

    glColor3f(0,1,0);
    glBegin(GL_LINES);
    {
        glVertex3f(-100,0,0);
        glVertex3f(100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0,100,0);
    }
    glEnd();

    glColor3f(1,0,0);

    glRotatef(B, 0,0,1);
    glTranslatef(30,0,0);
    glRotatef(A, 0,0,1);

    drawRect(5);


    glutSwapBuffers();
	//glutPostRedisplay();
}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0001;

	//codes for any changes in Models
	A+=0.5;
	B+=0.3;

	//this will call the display AGAIN
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
	glutIdleFunc(animate);

	//what you want to do in the idle time (when no drawing is occurring)
	//glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

