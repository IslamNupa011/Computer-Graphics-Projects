#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include <bits/stdc++.h>
using namespace std;



struct box
{
    int x_move,y_move,z_move;       //moving value to put in stack
    int x_scale,y_scale,z_scale;    //scaling value to put in stack
    int r_color,g_color,b_color;

    box()
    {
        printf("fun");
        x_move=0;
        y_move=0;
        z_move=0;
        x_scale=1;  ///initial value which will be updated by value from new values
        y_scale=1;
        z_scale=1;
        r_color=0;
        g_color=0;
        b_color=0;
    }

};

stack <box> stora;
box saver;          ///it has to be declared global to reach keyboard function also after structure box

//double cameraAngle;
double R, Rspeed, vAngle, hAngle, angleSpeed;
int move_x=0;
int move_y=0;       ///where LEGOMAN is at right now
int move_z=0;

int color_r=0;
int color_g=0;      ///what color box is legoman holding
int color_b=0;

int x_index=0;
int y_index=0;      ///which index of square he is in
int z_index=0;

int scale_x=1;
int scale_y=1;     ///the legnth of the box
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



void StoreBrick()
{
    if(stora.empty())
    {
        return;
    }
    stack <box> draw;
    draw=stora;
    while(!draw.empty())
    {
        glTranslated(draw.top().x_move,draw.top().y_move,draw.top().z_move);    ///always translate how far it is in
        glPushMatrix();
        glColor3f(draw.top().r_color,draw.top().g_color,draw.top().b_color);        //what color it is
        glTranslated(5,-10,0);  //it puts the brick on front of the LEGOMAN
        glTranslated(0,0,-5);   //it goes a little up. so adjust it in z-axis
        glScalef(draw.top().x_scale,draw.top().y_scale,draw.top().z_scale);      ///scaling how big i want to make the box.
        glTranslatef(-5,-5,5);  //the box in 0,0,0 position.
        glutSolidCube(10);      //the box
        glTranslated(draw.top().x_move,draw.top().y_move,draw.top().z_move);    ///always translate how far it is in
        glPopMatrix();
        glTranslated(-draw.top().x_move,-draw.top().y_move,-draw.top().z_move);    ///**reset back to originial position.
        draw.pop();
    }
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

        gluLookAt(move_x+R*cos(vAngle)*cos(hAngle),move_y+R*cos(vAngle)*sin(hAngle),move_z+R*sin(vAngle),  move_x,move_y,move_z,  a,b,c);
    }


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	**glPushMatrix();*************************************************/

	// draw the three major AXES
	//drawAxis();

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




    glPushMatrix();
    StoreBrick();                           ///***** it stores value here (gltranstated-er age korte hobe. jehetu already move_xyz ache)
    glPopMatrix();




    glTranslated(move_x,move_y,move_z);     ///X

    glPushMatrix();
    glColor3f(color_r,color_g,color_b);
    glTranslated(5,-10,0);
    glTranslated(0,0,-5);
	glScalef(scale_x,scale_y,scale_z);      ///scaling how big i want to make the box.
	glTranslatef(-5,-5,5);
	glutSolidCube(10);
	glPopMatrix();













    glPushMatrix();
    glColor3f(color_r, color_g, color_b);
    glTranslated(0,-15,40);                 ///the box he is holding in hand
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
	    if(check+scale_y-1<20)      ///goes front
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
	        y_index--;          ///goes back
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
            move_x=move_x+10;       ///goes left
            //printf("move_x:%f\n",move_x);
            printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
            //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
        }

	}


	if (key == 'd')         //right is in X-axis
	{
	    int check=x_index+1;
	    if(check+scale_x-1<20)        // it can also be calculated by the loop in grid.
        {
            x_index++;          ///goes right
            move_x=move_x-10;
        }

	    //printf("move_x:%f\n",move_x);
        printf("x_index:%d   y_index:%d   z_index:%d\n",x_index,y_index,z_index);
        //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}

	if (key == 'q')         //right is in X-axis
	{

	    int check=z_index+1;
	    if(check+scale_z-1<20)
        {
            z_index++;             ///goes up
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
            z_index--;             ///goes down
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
            color_r=1;          ///change color to red
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
            color_g=1;          ///change color to green
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
            color_b=1;          ///change color to blue
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
	    if(check+x_index-1<20)    //if its in 5th index. it can only extend upto 15 so the total value is 20
        {
            scale_x++;          ///scale x longer
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
            scale_x--;          ///scale x shorter
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}

    if (key == 'c')         //right is in X-axis
	{
	    int check=scale_y+1;
	    if(check+y_index-1<20)    //if its in 5th index. it can only extend upto 15 so the total value is 20
        {
            scale_y++;              ///scale y longer
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}
	if (key == 'v')         //right is in X-axis
	{
	    int check=scale_y-1;
	    if(check>0)     //scale acn be 1.but not 0
        {
            scale_y--;              ///scale y shorter
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}

	if (key == 'b')         //right is in X-axis
	{
	    int check=scale_z+1;
	    if(check+z_index-1<20)    //if its in 5th index. it can only extend upto 15 so the total value is 20
        {
            scale_z++;              ///scale z longer
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}
	if (key == 'n')         //right is in X-axis
	{
	    int check=scale_z-1;
	    if(check>0)     //scale acn be 1.but not 0
        {
            scale_z--;              ///scale z shorter
        }
	    //printf("move_z:%f\n",move_z);
        printf("scale_x:%d   scale_y:%d   scale_z:%d\n",scale_x,scale_y,scale_z);
	    //printf("left:%f, right:%f, up:%f , down:%f\n",left,right,up,down);
	}

    if (key == 'o')         //right is in X-axis
	{
	    saver.x_move=move_x;
	    saver.y_move=move_y;
	    saver.z_move=move_z;
	    saver.x_scale=scale_x;          ///push the values to print later
	    saver.y_scale=scale_y;
	    saver.z_scale=scale_z;
	    saver.r_color=color_r;
        saver.g_color=color_g;
        saver.b_color=color_b;
	    //printf("saver x:%d y:%d z:%d \n scale_x:%d scale_y:%d scale_z:%d \n\n",saver.x_move,saver.y_move,saver.z_move,scale_x,,scale_y,scale_z);
	    printf("x:%d   y:%d   z:%d\n",saver.x_move,saver.y_move,saver.z_move);
	    printf("scale_x:%d   scale_y:%d   scale_z:%d\n\n",saver.x_scale,saver.y_scale,saver.z_scale);
	    stora.push(saver);
	    printf("stored in stora stack\n\n");

	    scale_x=1;
	    scale_y=1;
	    scale_z=1;
	    color_r=0;
	    color_g=0;
	    color_b=0;


	}
    if (key == 'p')         //right is in X-axis
	{

	    if(!stora.empty())  ///if stora not empty
        {
            printf("\n\n\n");
            printf("x:%d   y:%d   z:%d\n",stora.top().x_move,stora.top().y_move,stora.top().z_move);
            printf("scale_x:%d   scale_y:%d   scale_z:%d\n\n",stora.top().x_scale,stora.top().y_scale,stora.top().z_scale);
            stora.pop();    ///pop the last brick entered
            printf("popped from stack");
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
