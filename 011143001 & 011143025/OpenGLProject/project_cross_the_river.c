#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
int c=3,moves=0;
//color for object
int c1=0, c2=1;
//for boat
float x1=-20, x2=-30, x3=-40 , x4=-10, y5=20, y2=20, y3=25, y4=25;
//for objects in the boat
float x11=-18, x12=-20, x13=-18, x14=-20, y11=25, y12=25, y13=30, y14=30;
//for objects in the stand
float x6=-18, x7=-20, x8=-18, x9=-20, y6=40, y7=40, y8=50, y9=50;
//not used
float m = -10, n=40;
//for disappear objects and create again
int gflag = 0, gflag1=0, rflag=0,rflag1=0;
int rrflag1=0,rrflag2=0,rrflag3=0,rgflag1=0,rgflag2=0,rgflag3=0;
int lrflag1=1,lrflag2=1,lrflag3=1,lgflag1=1,lgflag2=1,lgflag3=1;
//use for condition to move the boat
int move_the_boat = 0;
//to move right
float move_right = -10;
int flag3=0;
//to move left
float move_left = 50;
//for objects count
int green_object_count_boat = 0;
int red_object_count_boat = 0;
int green_object_count_leftside = 3;
int red_object_count_leftside = 3;
int green_object_count_rightside = 0;
int red_object_count_rightside = 0;
//boat object count
int boat_object_count=0;

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

    glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(-40, 0, 0);
	    glVertex3f(40, 0, 0);
	    glVertex3f(40, 20, 0);
	    glVertex3f(-40, 20, 0);
	}
	glEnd();
	if(green_object_count_leftside==3)
    {
        glColor3f(0, 1, 0);
    }
    else
    {
        glColor3f(1, 0, 0);
    }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(-100, 0, 0);
	    glVertex3f(-40, 0, 0);
	    glVertex3f(-40, 40, 0);
	    glVertex3f(-100, 40, 0);
	}
	glEnd();
	if(green_object_count_rightside==3)
    {
        glColor3f(0, 1, 0);
    }
    else
    {
        glColor3f(1, 0, 0);
    }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(90, 0, 0);
	    glVertex3f(40, 0, 0);
	    glVertex3f(40, 40, 0);
	    glVertex3f(90, 40, 0);
	}
	glEnd();
	if(green_object_count_rightside==3)
    {
        glColor3f(0, 1, 0);
    }
    else
    {
        glColor3f(1, 0, 0);
    }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x1, y5, 0);
	    glVertex3f(x2, y2, 0);
	    glVertex3f(x3, y3, 0);
	    glVertex3f(x4, y4, 0);
	}
	glEnd();
	//left side 1st object red
	if(lrflag1==1)
    {
         glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-42, y6, 0);
	    glVertex3f(x7-42, y7, 0);
	    glVertex3f(x8-42, y8, 0);
	    glVertex3f(x9-42, y9, 0);
	}
	glEnd();

    }
	//left side 2nd object
	if(lrflag2==1)
    {
        glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-38, y6, 0);
	    glVertex3f(x7-38, y7, 0);
	    glVertex3f(x8-38, y8, 0);
	    glVertex3f(x9-38, y9, 0);
	}
	glEnd();

    }

	//left side 3rd object
	if(lrflag3==1)
    {
        glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-34, y6, 0);
	    glVertex3f(x7-34, y7, 0);
	    glVertex3f(x8-34, y8, 0);
	    glVertex3f(x9-34, y9, 0);
	}
	glEnd();

    }
	//left side 1st object green
	if(lgflag1==1)
    {
         if(red_object_count_leftside>green_object_count_leftside&&move_right==40.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-30, y6, 0);
	    glVertex3f(x7-30, y7, 0);
	    glVertex3f(x8-30, y8, 0);
	    glVertex3f(x9-30, y9, 0);
	}
	glEnd();

    }
    //2nd object left side green
    if(lgflag2==1)
    {
        if(red_object_count_leftside>green_object_count_leftside&&move_right==40.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-26, y6, 0);
	    glVertex3f(x7-26, y7, 0);
	    glVertex3f(x8-26, y8, 0);
	    glVertex3f(x9-26, y9, 0);
	}
	glEnd();
    }
     //3rd object on the stand left side
    if(lgflag3==1)
    {
       if(red_object_count_leftside>green_object_count_leftside&&move_right==40.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6-22, y6, 0);
	    glVertex3f(x7-22, y7, 0);
	    glVertex3f(x8-22, y8, 0);
	    glVertex3f(x9-22, y9, 0);
	}
	glEnd();
    }

    //right side red objects
    //1st
       if(rrflag1==1)
       {
           glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+66, y6, 0);
	    glVertex3f(x7+66, y7, 0);
	    glVertex3f(x8+66, y8, 0);
	    glVertex3f(x9+66, y9, 0);
	}
	glEnd();

       }
       //2nd object right side red
       if(rrflag2==1)
       {


        glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+70, y6, 0);
	    glVertex3f(x7+70, y7, 0);
	    glVertex3f(x8+70, y8, 0);
	    glVertex3f(x9+70, y9, 0);
	}
	glEnd();
       }

	//3rd object right side red
	if(rrflag3==1)
    {
        glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+74, y6, 0);
	    glVertex3f(x7+74, y7, 0);
	    glVertex3f(x8+74, y8, 0);
	    glVertex3f(x9+74, y9, 0);
	}
	glEnd();

    }
    //right side green objects
    if(rgflag1==1)
    {
        if(red_object_count_rightside>green_object_count_rightside&&move_left==-10.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }

	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+78, y6, 0);
	    glVertex3f(x7+78, y7, 0);
	    glVertex3f(x8+78, y8, 0);
	    glVertex3f(x9+78, y9, 0);
	}
	glEnd();
    }




	//2nd object
	if(rgflag2==1)
    {
        if(red_object_count_rightside>green_object_count_rightside&&move_left==-10.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+82, y6, 0);
	    glVertex3f(x7+82, y7, 0);
	    glVertex3f(x8+82, y8, 0);
	    glVertex3f(x9+82, y9, 0);
	}
	glEnd();
    }

	//3rd object
	if(rgflag3==1)
    {
         if(red_object_count_rightside>green_object_count_rightside&&move_left==-10.5)
        {
            glColor3f(c2, c1, c1);
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }
        else
        {
            glColor3f(c1, c2, c1);
        }
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x6+86, y6, 0);
	    glVertex3f(x7+86, y7, 0);
	    glVertex3f(x8+86, y8, 0);
	    glVertex3f(x9+86, y9, 0);
	}
	glEnd();

    }

    //1st object on the boat
    //green
    if(gflag==1)
    {
        glColor3f(c1, c2, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x11, y11, 0);
	    glVertex3f(x12, y12, 0);
	    glVertex3f(x13, y13+5, 0);
	    glVertex3f(x14, y14+5, 0);
	}
	glEnd();
    }

     //2nd object on the boat green
     if(gflag1==1)
     {

	glColor3f(c1, c2, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x11-4, y11, 0);
	    glVertex3f(x12-4, y12, 0);
	    glVertex3f(x13-4, y13+5, 0);
	    glVertex3f(x14-4, y14+5, 0);
	}
	glEnd();
     }
     //1st object on the boat
    //green
    if(rflag==1)
    {
        glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x11, y11, 0);
	    glVertex3f(x12, y12, 0);
	    glVertex3f(x13, y13+5, 0);
	    glVertex3f(x14, y14+5, 0);
	}
	glEnd();
    }

     //2nd object on the boat green
     if(rflag1==1)
     {

	glColor3f(c2, c1, c1);
	glBegin(GL_POLYGON);
	{
	    glVertex3f(x11-4, y11, 0);
	    glVertex3f(x12-4, y12, 0);
	    glVertex3f(x13-4, y13+5, 0);
	    glVertex3f(x14-4, y14+5, 0);
	}
	glEnd();
     }





	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void move_right_func()
{
    move_right = -10;
}
void move_left_func()
{
    move_left = 40;
}
void animate()
{
	//codes for any changes in Models, Camera
	if(move_the_boat==1)
    {


        if(move_right<=40)
        {
            move_right+=.5;
            x1+=.5;
	        x2+=.5;
	        x3+=.5;
	        x4+=.5;
	        x11+=.5;
	        x12+=.5;
	        x13+=.5;
	        x14+=.5;
	        printf("");

        }


    }
    if(move_the_boat==2)
    {

        if(move_left>=-10)
        {
             move_left-=.5;
             x1-=.5;
	         x2-=.5;
	         x3-=.5;
	         x4-=.5;
	         x11-=.5;
	         x12-=.5;
	         x13-=.5;
	         x14-=.5;
	         printf("");
        }

    }






	glutPostRedisplay();
}
void specialKeys(int key, int x, int y)
{

    //request display update
    glutPostRedisplay();
    //for reseting transformation
    glLoadIdentity();
}
void keyboardListener(unsigned char key, int x, int y)
{
    if(key == '1'&&boat_object_count<2)
   {
       boat_object_count++;
       lgflag1 = 0;
       if(rflag1==1 ||gflag1==1)
       {
            gflag = 1;

       }
       else
       {
           gflag1=1;
       }
       green_object_count_boat++;
       green_object_count_leftside--;
       if(green_object_count_leftside==1)
       {
           lgflag2=0;
       }
       if(green_object_count_leftside==0)
       {
           lgflag3=0;
       }
       if(green_object_count_boat==2)
       {
          if(rflag==1&&boat_object_count==2||gflag==1&&boat_object_count==2)
           {
               gflag1==1;
           }
           else if(rflag1==1&&boat_object_count==2||gflag1==1&&boat_object_count==2)
           {
               gflag=1;
           }
       }

       //printf("%d ",boat_object_count);

   }
   if(key == '2'&&boat_object_count>=0)
   {
       boat_object_count--;
       green_object_count_boat--;
       if(gflag==1)
       {
           gflag=0;
       }
       else if(gflag1==1)
       {
           gflag1=0;
       }
       if(green_object_count_boat==0)
       {
           gflag1=0;
       }
       green_object_count_leftside++;
       if(lgflag1==0)
       {
           lgflag1=1;
       }
       else if(lgflag2==0)
       {
           lgflag2=1;
       }
       else if(lgflag3==0)
       {
           lgflag3=1;
       }

   }
    if(key == '3'&&boat_object_count<2)
   {
       boat_object_count++;
       lrflag1 = 0;
       if(gflag1==1||rflag1==1)
       {
            rflag = 1;

       }
       else
       {
           rflag1=1;
       }
       red_object_count_boat++;
       red_object_count_leftside--;
       if(red_object_count_leftside==1)
       {
           lrflag2=0;
       }
       if(red_object_count_leftside==0)
       {
           lrflag3=0;
       }
       if(red_object_count_boat==2)
       {
           if(gflag==1&&boat_object_count==2||rflag==1&&boat_object_count==2)
           {
               rflag1==1;
           }
           else
           {
               rflag=1;
           }
       }
      // printf("%d ",boat_object_count);


   }
   //put in the stand
    if(key == '4'&&boat_object_count>=0)
   {
       boat_object_count--;
       red_object_count_leftside++;
       red_object_count_boat--;
       if(rflag==1)
       {
           rflag=0;
       }
       else if(rflag1==1)
       {
           rflag1=0;
       }
       if(red_object_count_boat==0)
       {
           rflag1=0;
       }

       if(lrflag1==0)
       {
           lrflag1=1;
       }
       else if(lrflag2==0)
       {
           lrflag2=1;
       }
       else if(lrflag3==0)
       {
           lrflag3=1;
       }

   }
    //put the obj to the side
   if(key == '5'&&boat_object_count>=0&&boat_object_count>0)
   {
       boat_object_count--;
       green_object_count_boat--;
       green_object_count_rightside++;
       if(gflag==1)
       {
           gflag=0;
       }
       else if(gflag1==1)
       {
           gflag1=0;
       }
       if(green_object_count_boat==0)
       {
           gflag1=0;
       }
       if(rgflag1==0)
       {
           rgflag1=1;
       }
       else if(rgflag2==0)
       {
           rgflag2=1;
       }
       else if(rgflag3==0)
       {
           rgflag3=1;
       }
   }

   if(key == '6'&&boat_object_count<2)
   {
       boat_object_count++;
       rgflag1 = 0;
       if(rflag1==1 ||gflag1==1)
       {
            gflag = 1;

       }
       else
       {
           gflag1=1;
       }
       green_object_count_boat++;
       if(green_object_count_rightside==1)
       {
           rgflag2=0;
       }
       if(green_object_count_rightside==0)
       {
           rgflag3=0;
       }
       green_object_count_rightside--;
       if(green_object_count_boat==2)
       {
          if(rflag==1&&boat_object_count==2||gflag==1&&boat_object_count==2)
           {
               gflag1==1;
           }
           else if(rflag1==1&&boat_object_count==2||gflag1==1&&boat_object_count==2)
           {
               gflag=1;
           }
       }


   }



   //put the obj to the side
   if(key == '7'&&boat_object_count>=0&&boat_object_count>0)
   {
       boat_object_count--;
       red_object_count_boat--;
       red_object_count_rightside++;
       if(rflag==1)
       {
           rflag=0;
       }
       else if(rflag1==1)
       {
           rflag1=0;
       }
       if(rrflag1==0)
       {
           rrflag1=1;
       }
       else if(rrflag2==0)
       {
           rrflag2=1;
       }
       else if(rrflag3==0)
       {
           rrflag3=1;
       }


   }
   if(key == '8'&&boat_object_count<2)
   {
       boat_object_count++;
       rrflag1 = 0;
       if(gflag1==1 ||rflag1==1)
       {
            rflag = 1;

       }
       else
       {
           rflag1=1;
       }
       red_object_count_boat++;
       if(red_object_count_rightside==1)
       {
           rrflag2=0;
       }
       if(green_object_count_rightside==0)
       {
           rgflag3=0;
       }
       red_object_count_rightside--;
       if(red_object_count_boat==2)
       {
          if(rflag==1&&boat_object_count==2||gflag==1&&boat_object_count==2)
           {
               rflag1==1;
           }
           else if(rflag1==1&&boat_object_count==2||gflag1==1&&boat_object_count==2)
           {
               rflag=1;
           }
       }


   }

   if(key == 'w'&&boat_object_count>0)
   {
       move_the_boat = 1;
       move_right_func();
       move_left_func();
       moves++;
       printf("%d moves\n",moves);
       if(red_object_count_leftside>green_object_count_leftside&&move_right==40)
        {
            printf("!!!GAME OVER!!!\n");
            printf("!!!RESTART THE GAME AGAIN!!!\n");
        }


   }
   if(key == 'e'&&boat_object_count>0)
   {
       move_the_boat = 2;
       move_left_func();
       move_right_func();
       moves++;
       printf("%d moves\n",moves);
   }
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

	glutInitWindowSize(1200, 1500);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Lab!");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);
	glutKeyboardFunc(keyboardListener);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

