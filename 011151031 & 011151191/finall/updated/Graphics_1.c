#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>

//double cameraAngle;
double R, Rspeed, vAngle, hAngle, angleSpeed;
int move_x=0;
int move_y=0;
int move_z=0;

int color_r=0;
int color_g=0;
int color_b=0;


int zxy_array[21][21][21]={0};

int x_index=0;
int y_index=0;
int z_index=0;

int scale_x=1;
int scale_y=1;
int scale_z=1;

void drawAxis(){
    glBegin(GL_LINES);

	//+X axis
	glColor3f(1, 0, 0);//red
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x+1000, move_y+0, move_z+0);

	//-X axis
	glColor3f(1, 0, 1);//purple
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x-1000, move_y+0, move_z+0);

    //+Y axis
	glColor3f(0, 1, 0);//green
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x+0, move_y+1000, move_z+0);

	//-Y axis
	glColor3f(1, 1, 0);//yellow
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x+0, move_y+-1000, move_z+0);

	//+Z axis
	glColor3f(0, 0, 1);//blue
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x+0, move_y+0, move_z+1000);

	//-Z axis
	glColor3f(0, 1, 1);//cyan
	glVertex3f(move_x+0, move_y+0, move_z+0);
	glVertex3f(move_x+0, move_y+0, move_z-1000);
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

void drawRectAnywhere(int L)
{

    int left,right,up,down;
    right=move_x+L;
    left=move_x-L;
    up=move_y+L;
    down=move_y-L;

    //printf("left:%d, right:%d, up:%d , down:%d\n",left,right,up,down);

    glColor3f(color_r, color_g, color_b);//red
    glBegin(GL_QUADS);
    {
        glVertex3f(left,down,move_z);
        glVertex3f(left+10,down,move_z);
        glVertex3f(left+10,down+10,move_z);
        glVertex3f(left,down+10,move_z);
    }
    glEnd();
    glPopMatrix();
}

/*
void LoopRect()
{
    for(z=0;z<20;z++)
    {
        for(x=0;x<20;x++)
        {
            for(y=0;y<20;y++)
            {
                printf("z:%d,  x:%d,y:%d",z,x,y)
            }
        }
    }
}
*/


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

        gluLookAt(move_x+R*cos(vAngle)*cos(hAngle),move_y+R*cos(vAngle)*sin(hAngle),move_z+R*sin(vAngle),  move_x,move_y,move_z,  a,b,c);
    }


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	**glPushMatrix();*************************************************/

	// draw the three major AXES
	drawAxis();

	//some grid lines along the field
	glPushMatrix();
	glTranslated(-95,-110,0);
	drawGrid();
    glPopMatrix();
         //  1   2





    glTranslated(0,0,5);    //liftin the leg up to axis


    glPushMatrix();
    glTranslated(0,-15,-5);    //the pink tile is the center of body
    drawRectAnywhere(5);
    glPopMatrix();




    glTranslated(move_x,move_y,move_z);
    glPushMatrix();
    glColor3f(1, 1, 1);
    //glTranslated(-5,-15,0);
    glTranslated(-5,-5,0);
    glScaled(3,1,1);
    glutSolidCube(10);
    glPopMatrix();








    glPushMatrix();
    glColor3f(1,1,0);
    glTranslated(0,5,60);       //head
    glutSolidCube(10);
    glPopMatrix();


    glPushMatrix();
    glColor3f(0,0,1);
    glTranslated(0,5,40);       //body
    glScalef(1,1,3);
    glScalef(3,1,1);
    glutSolidCube(10);
    glPopMatrix();


    glPushMatrix();
    glTranslated(10,0,0);

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslated(0,5,15);
    glScalef(1,1,2);                //left leg  with left knee
    //glTranslatef(10,0,0);
    glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,0,0);
    glScalef(1,2,1);
    glutSolidCube(10);



    glPushMatrix();
    glColor3f(1,1,0);
    glTranslated(10,0,40);
    glutSolidCube(10);
    glPopMatrix();      //left hand


    glPopMatrix();






    glPushMatrix();
    glColor3f(1,0,0);
    glTranslated(-10,0,0);

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslated(0,5,15);
    glScalef(1,1,2);                //right leg with right knee
    //glTranslatef(10,0,0);
    glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,0,0);
    glScalef(1,2,1);
    glutSolidCube(10);






    glPushMatrix();
    glColor3f(1,1,0);
    glTranslated(-10,0,40);
    glutSolidCube(10);
    glPopMatrix();      //right hand

    glPopMatrix();





        //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void keyboardListener(unsigned char key, int x, int y)
{
    if (key == 'w')         //up is in Y-axis
	{
	    int check=y_index+1;
	    if(check<20)
	    {
	        y_index++;
	        move_y=move_y-10;
            //printf("move_y:%f and x_index:%d   y_index:%d\n",move_y,x_index,y_index);
            printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
            //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);

	    }


	}

    if (key == 's')         //down is in Y'-axis
	{

	    int check=y_index-1;
	    if(check>-1)
	    {
	        y_index--;
	        move_y=move_y+10;
            //printf("move_y:%f and x_index:%d   y_index:%d\n",move_y,x_index,y_index);
            printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
            //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	    }

	}


	if (key == 'a')        //left is in X'-axis
	{
	    int check=x_index-1;
	    if(check>-1)
        {
            x_index--;
            move_x=move_x+10;
            //printf("move_x:%f\n",move_x);
            printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
            //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
        }

	}


	if (key == 'd')         //right is in X-axis
	{
	    int check=x_index+1;
	    if(check<20)        // it can also be calculated by the loop in grid.
        {
            x_index++;
            move_x=move_x-10;
        }

	    //printf("move_x:%f\n",move_x);
        printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
        //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}

	if (key == 'q')         //right is in X-axis
	{

	    int check=z_index+1;
	    if(check<20)
        {
            z_index++;
            move_z=move_z+10;
        }
	    //printf("move_z:%f\n",move_z);
        printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
        //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);

	}

	if (key == 'e')         //right is in X-axis
	{
	    int check=z_index-1;
	    if(check>-1)
        {
            z_index--;
            move_z=move_z-10;
        }
	    //printf("move_z:%f\n",move_z);
	    printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}


	if (key == '1')
	{
	    if(color_r==0)
        {
            color_r=1;
        }
        else
        {
            color_r=0;
        }
	    //color_r=(color_r+5)%255;
	    printf("color_r:%d\n",color_r);
	}


	if (key == '2')
	{
	    if(color_g==0)
        {
            color_g=1;
        }
        else
        {
            color_g=0;
        }
	    //color_g=(color_g+5)%255;
	    printf("color_g:%d\n",color_g);
	}


	if (key == '3')
	{
	    if(color_b==0)
        {
            color_b=1;
        }
        else
        {
            color_b=0;
        }
	    //color_b=(color_b+5)%255;
	    printf("color_b:%d\n",color_b);
	}

	if (key == 'z')         //right is in X-axis
	{
	    int check=scale_x+1;
	    if(check+x_index<20)    //if its in 5th index. it can only extend upto 15 so the total value is 20
        {
            scale_x++;
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}
	if (key == 'x')         //right is in X-axis
	{
	    int check=scale_x-1;
	    if(check>0)     //scale acn be 1.but not 0
        {
            scale_x--;
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
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
