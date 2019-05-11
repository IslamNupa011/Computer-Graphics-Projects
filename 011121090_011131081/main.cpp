#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <windows.h>
#include <GL/glut.h>

#define PI 3.1416
int xx = -38;
int x = 0;
float rotateVal = 0.0;
float rotateDir = 0.3;
int batFlag = 0;
int batTrnaslate = 0;
int fireVar = 0;
int fireVar2 = 0;
float fireRate = 18;
float rotateeVal = 0.0;
float batlogomove=0;
int batlogomoveflag=0;
float boatmove = 0;
int boatflag = 1;

void normal_key(unsigned char key, int x, int y)
{
	switch (key) {

	    case 'a':
			if(xx>=-300 && xx<=300)
            {
                xx -=4;
                printf("left\n");
            }

            glutPostRedisplay();
				break;

        case 'd': //jump into boat
			if(xx>=-300 && xx<=300)
            {
               xx +=4;
               printf("right\n");
            }
				glutPostRedisplay();
				break;

				case 'w': //jump into boat

                batFlag = 1;
               printf("batlogoON\n");

				glutPostRedisplay();
				break;


				case 's': //jump into boat

                batFlag = 0;
               printf("batlogoOFF\n");

				glutPostRedisplay();
				break;

				case 'e': //jump into boat

                fireVar = 1;
               printf("weaponON\n");

				glutPostRedisplay();
				break;
				case 'q': //jump into boat

                fireVar = 0;
               printf("weaponOFF\n");

				glutPostRedisplay();
				break;
				case 'r': //jump into boat

                fireVar2 = 1;
               printf("fireON\n");

				glutPostRedisplay();
				break;
				case 'f': //jump into boat

                fireVar2 = 0;
               printf("fireOFF\n");

				glutPostRedisplay();
				break;



	    default:
			break;
	}

}



void my_mouse(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				rotateDir = -0.3;
				printf("Mleft\n");
				printf("%d\n",xx);

			}
			break;

		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				rotateDir = 0.3;
				printf("Mright\n");
				printf("%d\n",xx);
			}
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
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
	gluLookAt(0,0,280,	0,0,0,	0,1,0);
    //bari1
	glPushMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-192, 64, 0);
	    glVertex3f(-184, 64, 0);
	    glVertex3f(-184, 76, 0);
	    glVertex3f(-192, 76, 0);
	}
	glEnd();

	glPopMatrix();

    glPushMatrix();
	glBegin(GL_QUADS);
	{
	    glVertex3f(-192, 80, 0);
	    glVertex3f(-184, 80, 0);
	    glVertex3f(-184, 92, 0);
	    glVertex3f(-192, 92, 0);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-192, 96, 0);
	    glVertex3f(-184, 96, 0);
	    glVertex3f(-184, 108, 0);
	    glVertex3f(-192, 108, 0);
	}
	glEnd();
    glPopMatrix();
    glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-172, 96, 0);
	    glVertex3f(-164, 96, 0);
	    glVertex3f(-164, 108, 0);
	    glVertex3f(-172, 108, 0);
	}
	glEnd();
    glPopMatrix();
     glPushMatrix();
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-172, 112, 0);
	    glVertex3f(-164, 112, 0);
	    glVertex3f(-164, 124, 0);
	    glVertex3f(-172, 124, 0);
	}
	glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0 ,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-200, 152, 0);
	    glVertex3f(-160, 152, 0);
	    glVertex3f(-160, 153, 0);
	    glVertex3f(-200, 153, 0);
	}
	glEnd();
    glPopMatrix();

        glColor3f(.7, .7 ,.7);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-200, 40, 0);
	    glVertex3f(-160, 40, 0);
	    glVertex3f(-160, 160, 0);
	    glVertex3f(-200, 160, 0);
	}
	glEnd();
    glPopMatrix();
    //bari2
	glPushMatrix();
	//
	glPushMatrix();
	//glTranslatef(0,14,0);
	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-156, 48, 0);
	    glVertex3f(-148, 48, 0);
	    glVertex3f(-148, 56, 0);
	    glVertex3f(-156, 56, 0);
	}
	glEnd();

	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-144, 48, 0);
	    glVertex3f(-136, 48, 0);
	    glVertex3f(-136, 56, 0);
	    glVertex3f(-144, 56, 0);
	}
	glEnd();

	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-132, 48, 0);
	    glVertex3f(-124, 48, 0);
	    glVertex3f(-124, 56, 0);
	    glVertex3f(-132, 56, 0);
	}
	glEnd();

	glPopMatrix();
    //
    glPopMatrix();

        glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-160, 40, 0);
	    glVertex3f(-120, 40, 0);
	    glVertex3f(-120, 80, 0);
	    glVertex3f(-160, 80, 0);
	}
	glEnd();
    glPopMatrix();
    //bari3
	glPushMatrix();

	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(-116, 44, 0);
	    glVertex3f(-104, 44, 0);
	    glVertex3f(-104, 56, 0);
	    //glVertex3f(-116, 56, 0);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(-96, 44, 0);
	    glVertex3f(-84, 44, 0);
	    glVertex3f(-84, 56, 0);
	    //glVertex3f(-96, 56, 0);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	  glColor3f(0,0,0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(-96, 64, 0);
	    glVertex3f(-84, 64, 0);
	    glVertex3f(-84, 76, 0);
	    //glVertex3f(-96, 76, 0);
	}
	glEnd();

	glPopMatrix();
	glPushMatrix();
	  glColor3f(1,1,1);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(-116, 64, 0);
	    glVertex3f(-104, 64, 0);
	    glVertex3f(-104, 76, 0);
	    //glVertex3f(-116, 76, 0);
	}
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100,115,0);
	glColor3f(0,.6,0);
	circle(9,8);
	glPopMatrix();


        glColor3f(.7, .7 ,.7);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-120, 40, 0);
	    glVertex3f(-80, 40, 0);
	    glVertex3f(-80, 100, 0);
	    glVertex3f(-120, 100, 0);
	}
	glEnd();
	glColor3f(.5,.5,.5);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(-132, 100, 0);
	    glVertex3f(-68, 100, 0);
	    glVertex3f(-100, 140, 0);
	}
	glEnd();
    glPopMatrix();

  //bari4
    glPushMatrix();

    glPushMatrix();
        glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-52,64, 0);
	    glVertex3f(-44, 64, 0);
	    glVertex3f(-44, 76, 0);
	    glVertex3f(-52, 76, 0);
	}
	glEnd();
    glPopMatrix();


    glPushMatrix();
    glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-80, 75, 0);
	    glVertex3f(-40, 95, 0);
	    glVertex3f(-40, 96, 0);
	    glVertex3f(-80, 76, 0);
	}
	glEnd();
    glPopMatrix();

        glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-80, 40, 0);
	    glVertex3f(-40, 40, 0);
	    glVertex3f(-40, 100, 0);
	    glVertex3f(-80, 80, 0);
	}
	glEnd();
    glPopMatrix();

    //bari5
    glPushMatrix();

glPushMatrix();
glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-34, 44, 0);
	    glVertex3f(-22, 44, 0);
	    glVertex3f(-22, 56, 0);
	    glVertex3f(-34, 56, 0);
	}
	glEnd();
    glPopMatrix();

    glPushMatrix();
glColor3f(0,0,0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-16, 44, 0);
	    glVertex3f(-4, 44, 0);
	    glVertex3f(-4, 56, 0);
	    glVertex3f(-16, 56, 0);
	}
	glEnd();
    glPopMatrix();


        glColor3f(.7, .7 ,.7);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-40, 40, 0);
	    glVertex3f(0, 40, 0);
	    glVertex3f(0, 80, 0);
	    glVertex3f(-40, 80, 0);
	}
	glEnd();
    glPopMatrix();

    //chorki

    //cirlce

    //stand

    //bari6
    glPushMatrix();
        glColor3f(.5,.5,.5);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-32, 80, 0);
	    glVertex3f(-8, 80, 0);
	    glVertex3f(-16, 102, 0);
	    glVertex3f(-25, 102, 0);
	}
	glEnd();
    glPopMatrix();

    //bari 7
    glPushMatrix();

    glPushMatrix();
    glColor3f(1, 1 ,1);
	glBegin(GL_QUADS);
	{
	    glVertex3f(4, 50, 0);
	    glVertex3f(36, 50, 0);
	    glVertex3f(36, 52, 0);
	    glVertex3f(4, 52, 0);
	}
	glEnd();

    glPopMatrix();


        glColor3f(.5, .5 ,.5);
	glBegin(GL_QUADS);
	{
	    glVertex3f(0, 40, 0);
	    glVertex3f(40, 40, 0);
	    glVertex3f(40, 60, 0);
	    glVertex3f(0, 68, 0);
	}
	glEnd();
    glPopMatrix();
    //chorki
    rotateVal-=rotateDir;

    glPushMatrix();
    glTranslatef(-20,120,0);
    glRotatef(rotateVal,0.0,0.0,1.0);
    drawSquare(2);
    glColor3f(0, 0, 0);
    circle(2,2);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-20,120,0);
    glRotatef(rotateVal,0.0,0.0,1.0);

    glColor3f(1, 1, 1);
    drawSquare(11);
    //circle(15,15);
    glPopMatrix();

//BatSignalLogo

if(batFlag == 1){
glPushMatrix();
    //glTranslatef(batlogomove,0,0);
    glTranslatef(130+batlogomove,140,0);
    //batlogomove+=0.5;
    glPushMatrix();
    //body
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        {
            glVertex3f(-15, -9, 0);
            glVertex3f(15, -9, 0);
            glVertex3f(15, 9, 0);
            glVertex3f(-15, 9, 0);
        }
        glEnd();
        //leftwing
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(-40, 13, 0);
            glVertex3f(-12, 13, 0);
            glVertex3f(-9, -15, 0);
        }
        glEnd();
        //rightwing
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(40, 13, 0);
            glVertex3f(12, 13, 0);
            glVertex3f(9, -15, 0);
        }
        glEnd();
        //ears
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(-3, 9, 0);
            glVertex3f(-6, 9, 0);
            glVertex3f(-4, 12, 0);
        }
        glEnd();

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(3, 9, 0);
            glVertex3f(6, 9, 0);
            glVertex3f(4, 12, 0);
        }
        glEnd();

        //tail
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(-2, -9, 0);
            glVertex3f(2, -9, 0);
            glVertex3f(0, -13, 0);
        }
        glEnd();

        glPopMatrix();

    glColor3f(1,1,1);
    circle(45,30);

glPopMatrix();
}

//akash
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(-200, 40, 0);
            glVertex3f(200, 40, 0);
            glVertex3f(200, 160, 0);
            glVertex3f(-200, 160, 0);
        }
        glEnd();


// nodi
//check
//boat
glPushMatrix();
    //glTranslatef(batlogomove,0,0);
    glTranslatef(320+boatmove,-5,0);
    //batlogomove+=0.5;
    glPushMatrix();
    glPushMatrix();
    glColor3f(1,0,0);
    {
        glBegin(GL_TRIANGLES);
        {
            glVertex3f(2, 10, 0);
            glVertex3f(3, 38, 0);
            glVertex3f(-13, 16, 0);
        }
        glEnd();

    }
    glPopMatrix();

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        {
            glVertex3f(-20, -9, 0);
            glVertex3f(20, -8, 0);
            glVertex3f(19, 8, 0);
            glVertex3f(-28, 10, 0);
        }
        glEnd();
 glPopMatrix();
 glPopMatrix();

//ecndcheck

	glColor3f(0, .3, .5);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-200, -40, 0);
	    glVertex3f(200, -40, 0);
	    glVertex3f(200, 40, 0);
	    glVertex3f(-200, 40, 0);
	}
	glEnd();


    // batmobile
glPushMatrix();
{

    //glTranslatef(xx,0,0);
    //wings

    //upper spilers
    glPushMatrix();
        glColor3f(0, 0, .7);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(xx-160, -80, 0);
	    glVertex3f(xx-120, -80, 0);
	    glVertex3f(xx-180, -40, 0);

	}
	glEnd();
    glPopMatrix();
    //lowerspoiler
    glPushMatrix();
    glColor3f(0, 0, .7);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(xx-160, -120, 0);
	    glVertex3f(xx-120, -120, 0);
	    glVertex3f(xx-180, -80, 0);
	}
	glEnd();
    glPopMatrix();

    //upperwing
    glPushMatrix();
    glColor3f(.3, .3, .3);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-160, -80, 0);
	    glVertex3f(xx-40, -80, 0);
	    glVertex3f(xx-120, -60, 0);
	    glVertex3f(xx-160, -60, 0);
	}
	glEnd();
    glPopMatrix();
    //lowerwing
    glPushMatrix();
    glColor3f(.3, .3, .3);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-160, -140, 0);
	    glVertex3f(xx-120, -140, 0);
	    glVertex3f(xx-40, -120, 0);
	    glVertex3f(xx-160, -120, 0);
	}
	glEnd();
    glPopMatrix();


    //capsule
    glPushMatrix();
        glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-120, -100, 0);
	    glVertex3f(xx-80, -100, 0);
	    glVertex3f(xx-100, -84, 0);
	    glVertex3f(xx-120, -84, 0);
	}
	glEnd();
    glPopMatrix();

    //exhaust fire
    glPushMatrix();


    glPushMatrix();
	glColor3f(.8, 0, 0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(xx-192, -132, 0);
	    glVertex3f(xx-160, -140, 0);
	    glVertex3f(xx-160, -120, 0);
	}
	glEnd();
	glPopMatrix();


	glColor3f(1, .5, 0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(xx-180, -120, 0);
	    glVertex3f(xx-160, -140, 0);
	    glVertex3f(xx-160, -120, 0);
	}
	glEnd();
	glColor3f(1, .8, 0);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(xx-180, -140, 0);
	    glVertex3f(xx-160, -140, 0);
	    glVertex3f(xx-160, -120, 0);
	}
	glEnd();

    glPopMatrix();
    //lowestbox
    glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-160, -140, 0);
	    glVertex3f(xx-40, -140, 0);
	    glVertex3f(xx-40, -80, 0);
	    glVertex3f(xx-160, -80, 0);
	}
	glEnd();


	//wheels function
	glPushMatrix();
    glTranslatef(xx-142,-140,0);
    glColor3f(0, 0, 0);
    circle(12,12);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(xx-61,-138,0);
    glColor3f(0, 0, 0);
    circle(12,12);
    glPopMatrix();


    //triangle headlights
    //firet
    if(fireVar == 1)
    {
        glPushMatrix();
        glColor3f(10, 10, 10);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-30, -92, 0);
	    glVertex3f(xx+10, -92, 0);
	    glVertex3f(xx+10, -88, 0);
	    glVertex3f(xx-30, -88, 0);
	}
	glEnd();
    glPopMatrix();
    //endfiret

    //firedown
    glPushMatrix();
        glColor3f(10, 10, 10);
	glBegin(GL_QUADS);
	{
	    glVertex3f(xx-30, -114, 0);
	    glVertex3f(xx+10, -114, 0);
	    glVertex3f(xx+10, -110, 0);
	    glVertex3f(xx-30, -110, 0);
	}
	glEnd();
    glPopMatrix();
    //endfiredown
    }


    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(xx-40, -140, 0);
	    glVertex3f(xx-0, -120, 0);
	    glVertex3f(xx-40, -100, 0);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(xx-40, -120, 0);
	    glVertex3f(xx-0, -100, 0);
	    glVertex3f(xx-40, -80, 0);
    }
    glEnd();
}
glPopMatrix();

//fireWeapon
if(fireVar==1 && fireVar2==1){
    rotateeVal+=fireRate;
    glPushMatrix();

    glTranslatef(xx+12,-112,0);
    glRotatef(rotateeVal,0.0,0.0,1.0);

    glColor3f(1, 0, 0);
    drawSquare(3);
    //circle(15,15);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(xx+12,-90,0);
    glRotatef(rotateeVal,0.0,0.0,1.0);

    glColor3f(1, 0, 0);
    drawSquare(3);
    //circle(15,15);
    glPopMatrix();
}
//endFireWeapon

//rasta

	glColor3f(.7, .5, 1);
	glBegin(GL_QUADS);
	{
	    glVertex3f(-200, -160, 0);
	    glVertex3f(200, -160, 0);
	    glVertex3f(200, -40, 0);
	    glVertex3f(-200, -40, 0);
	}
	glEnd();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate()
{
	//codes for any changes in Models, Camera

	//this will call the display AGAIN

    if(batlogomoveflag==0){
    batlogomove+=0.07;
    if(batlogomove>15){
        batlogomoveflag=1;
    }
}
    else if(batlogomoveflag==1){
        batlogomove-=0.07;
        if(batlogomove<-60){
            batlogomoveflag=0;
        }
    }

if(boatflag==0)
{

}
else if(boatflag==1)
{
    boatmove-=.07;
        if(boatmove<-810)
        {
            boatmove=0;
        }
}




	glutPostRedisplay();

	//batlogomove+=2;

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
    PlaySound("DarkKnight.wav", NULL, SND_FILENAME| SND_ASYNC);
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

	glutCreateWindow("gfx_Project_G O T H A M !");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);

    glutKeyboardFunc(normal_key);

	glutMouseFunc(my_mouse);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

