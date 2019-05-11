#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>


//double cameraAngle;
double R, Rspeed, vAngle, hAngle, angleSpeed;
double pinkUp=0;
double yellowUp=0;
double blueUp=0;
double redUp=0;
double greenUp=0;

void drawAxis(){
    glBegin(GL_LINES);

	//+X axis
	glColor3f(1, 0, 0);//red
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);

	//-X axis
	glColor3f(1, 0, 1);//purple
	glVertex3f(0, 0, 0);
	glVertex3f(-1000, 0, 0);

    //+Y axis
	glColor3f(0, 1, 0);//green
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1000, 0);

	//-Y axis
	glColor3f(1, 1, 0);//yellow
	glVertex3f(0, 0, 0);
	glVertex3f(0, -1000, 0);

	//+Z axis
	glColor3f(0, 0, 1);//blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1000);

	//-Z axis
	glColor3f(0, 1, 1);//cyan
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1000);
	glEnd();
}

void drawGrid(){
    int i;

	glColor3f(0.5, 0.5, 0.5);//gray

	glBegin(GL_LINES);
	for (i = -10; i <= 10; i++)
	{
		if (i == 0)
		{
			continue;//SKIP the MAIN axes
		}

		//lines parallel to Y-axis
		glVertex3f(i * 10, -100, 0);
		glVertex3f(i * 10, 100, 0);

		//lines parallel to X-axis
		glVertex3f(-100, i * 10, 0);
		glVertex3f(100, i * 10, 0);
	}
	glEnd();
}

void drawRectPink(double L)
{

    //glPushMatrix();

    //glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-5,0);       //pink
    glColor3f(1, 0, 1);

    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    glPopMatrix();
}

void drawRectCyan(double L)
{
    glPushMatrix();
    glTranslatef(5,5,0);      //cyan
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    glPopMatrix();
}


void drawRectBlue(double L)
{
    glTranslatef(10,0,0);
    glPushMatrix();
    glRotatef(-blueUp, 0,1,0);
    glTranslatef(5,5,0);      //blue

    //glTranslatef(10,0,0);
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    glPopMatrix();
}


void drawRectGreen(double L)
{
    glTranslatef(0,10,0);
    //glPushMatrix();
    glRotatef(greenUp,1,0,0);
    glTranslatef(5,5,0);      //green
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    //glPopMatrix();
}


void drawRectRed(double L)
{
    glTranslatef(-5,5,0);
    glPushMatrix();
    glRotatef(redUp, 1,0,0);
    glTranslatef(5,5,0);      //red
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    glPopMatrix();
}


void drawRectYellow(double L)
{
    glPushMatrix();
    glTranslatef(-5,5,0);      //yellow
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(-L,-L,0);
        glVertex3f(L,-L,0);
        glVertex3f(L,L,0);
        glVertex3f(-L,L,0);
    }
    glEnd();
    glPopMatrix();
}

void display()
{
	//codes for Models, Camera

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
	//3. WhiglPushMatrix();ch direction is the camera's UP direction?

	//gluLookAt(0,0,100,	0,0,0,	0,1,0);
	//gluLookAt(200 * sin(cameraAngle), -200 * cos(cameraAngle), 50, 30, 0, 20, 0, 0, 1);
    {
        double x = sqrt(R*R+1);
        double y = atan(1.0/R);

        double a = x*cos(vAngle+y)*cos(hAngle)-R*cos(vAngle)*cos(hAngle);
        double b = x*cos(vAngle+y)*sin(hAngle)-R*cos(vAngle)*sin(hAngle);
        double c = x*sin(vAngle+y)-R*sin(vAngle);

        gluLookAt(R*cos(vAngle)*cos(hAngle),R*cos(vAngle)*sin(hAngle),R*sin(vAngle),  0,0,0,  a,b,c);
    }


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	**glPushMatrix();*************************************************/

	// draw the three major AXES
	drawAxis();

	//some grid lines along the field
	drawGrid();

	glPushMatrix();
    glRotatef(-pinkUp, 1,0,0);          //  1   2
    drawRectPink(5);
    glPopMatrix();


    glPushMatrix();
    glRotatef(yellowUp, 0,1,0);         //  3   4
    drawRectYellow(5);
    glPopMatrix();


    glPushMatrix();
    drawRectBlue(5);
    glPopMatrix();


    drawRectCyan(5);        //eta fixed


    glPushMatrix();
    drawRectGreen(5);
    drawRectRed(5);
    glPopMatrix();
        //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void keyboardListener(unsigned char key, int x, int y)
{
    if (key == '1')
	{
	    if(pinkUp!=90)
        {
            pinkUp+=5;
        }
	}
	if (key == '2')
	{
	    if(pinkUp!=0)
        {
            pinkUp-=5;
        }
	}




	if (key == '3')
	{
	    if(yellowUp!=90)
        {
            yellowUp+=5;
        }
	}
	if (key == '4')
	{
	    if(yellowUp!=0)
        {
            yellowUp-=5;
        }
	}






	if (key == '5')
	{
	    if(blueUp!=90)
        {
            blueUp+=5;
        }
	}
	if (key == '6')
	{
	    if(blueUp!=0)
        {
            blueUp-=5;
        }
	}



	if (key == '7')
	{
	    if(greenUp!=90)
        {
            greenUp+=5;
        }
	}
	if (key == '8')
	{
	    if(greenUp!=0)
        {
            greenUp-=5;
        }
	}





	if (key == '9')
	{
	    if(redUp!=90)
        {
            redUp+=5;
        }
	}
	if (key == '0')
	{
	    if(redUp!=0)
        {
            redUp-=5;
        }
	}


}

void specialKeyListener(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		vAngle+=angleSpeed;
		//printf("button up pressed\n");
	}
	else if (key == GLUT_KEY_DOWN)
	{
		vAngle-=angleSpeed;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		hAngle-=angleSpeed;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		hAngle+=angleSpeed;
	}
	else if (key == GLUT_KEY_PAGE_UP)
	{glRotatef(-45, 1,0,0);
	    if(R>=Rspeed){
            R-=Rspeed;
	    }
	}
	else if (key == GLUT_KEY_PAGE_DOWN)
    {
        R+=Rspeed;
    }
}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0001;

	//codes for any changes in Models

	//this will call the display AGAIN
	glutPostRedisplay();

}

void init()
{
	//codes for initialization

	//angle in radian
	//cameraAngle = 0;
	R = 100.0;
	Rspeed = 3.0;

	vAngle = 0.0;
    hAngle = 0.0;
    angleSpeed = 0.05;

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

	glutCreateWindow("Assignment_1");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(keyboardListener);

	//what you want to do in the idle time (when no drawing is occuring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}
