#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<bits/stdc++.h>
#define PI 3.1416
using namespace std;
bool sim=false;
int swapt=1;
float p1=-14.0,q1=-6.0,p2=-8.0,q2=-6.0,p3=-2.0,q3=-6.0,p4=4.0,q4=-6.0,p5=10.0,q5=-6.0,t1=-14,t2=-15,t3=-13;
float wait=0.00;
bool sorted=false;
void circle(float radius_x, float radius_y,int cx,int cy)
{
	int i = 0;
	float angle = 0.0;
glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f ((cos(angle) * radius_x)+cx, (sin(angle) * radius_y)+cy, 0);
		}


	glEnd();

}
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

bool first=true;
bool second=false;
bool third=false;


void display(void)
{
     glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

     if(sim==true)
     {
         //swap 1
         if(swapt==1)
         {

             glColor3f(1.0, 0.0, 0.0);

             renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 1");


             if(first)
             {
                 if(q1<=0)
                    q1+=0.02;
                 else
                 {
                     second=true;
                     first=false;
                 }
             }
             if(second)
             {
                 if(p1<=-8||p2>=-14)
                 {
                     if(p1<=-8)
                        p1+=0.02;
                     if(p2>=-14)
                        p2-=0.02;
                 }
                 else
                 {
                     second=false;
                     p1-=0.02;
                     third=true;
                 }
             }
             if(third)
             {

                 if(q1>=-6)
                    q1-=0.02;
                 else
                 {
                     third=false;
                     first=true;
                     swapt++;
                     Sleep(500);
                     t1+=6;
                     t2+=6;
                     t3+=6;

                 }
             }
         }

         if(swapt==2)
         {

             glColor3f(1.0, 0.0, 0.0);

             renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 1");


             if(first)
             {
                 if(q1<=0)
                    q1+=0.02;
                 else
                 {
                     second=true;
                     first=false;
                 }
             }
             if(second)
             {
                 if(p1<=-2.0||p3>=-8.0)
                 {
                     if(p1<=-2.0)
                        p1+=0.02;
                     if(p3>=-8.0)
                        p3-=0.02;
                 }
                 else
                 {
                     second=false;
                     p1-=0.02;
                     third=true;
                 }
             }
             if(third)
             {

                 if(q1>=-6)
                    q1-=0.02;
                 else
                 {
                     third=false;
                     first=true;
                     swapt++;
                     Sleep(500);
                     t1+=6;
                     t2+=6;
                     t3+=6;

                 }
             }
         }

         if(swapt==3)
         {
             glColor3f(1.0, 0.0, 0.0);

             renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 1");
             if(first)
             {
                 if(q1<=0)
                    q1+=0.02;
                 else
                 {
                     second=true;
                     first=false;
                 }
             }
             if(second)
             {
                 if(p1<=4.0||p4>=-2.0)
                 {
                     if(p1<=4.0)
                        p1+=0.02;
                     if(p4>=-2.0)
                        p4-=0.02;
                 }
                 else
                 {
                     second=false;

                     third=true;
                 }
             }
             if(third)
             {

                 if(q1>=-6)
                    q1-=0.02;
                 else
                 {
                     third=false;
                     first=true;
                     swapt++;
                     Sleep(500);
                     t1+=6;
                     t2+=6;
                     t3+=6;

                 }
             }
         }
         if(swapt==4)
         {
             glColor3f(1.0, 0.0, 0.0);

             renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 1");
             if(first)
             {
                 if(q1<=0)
                    q1+=0.02;
                 else
                 {
                     second=true;
                     first=false;
                 }
             }
             if(second)
             {
                 if(p1<=10.0||p5>=4.0)
                 {
                     if(p1<=10.0)
                        p1+=0.02;
                     if(p5>=4.0)
                        p5-=0.02;
                 }
                 else
                 {
                     second=false;

                     third=true;
                     p5+=0.02;
                 }
             }
             if(third)
             {

                 if(q1>=-6)
                    q1-=0.02;
                 else
                 {
                     third=false;
                     first=true;
                     swapt++;
                     Sleep(500);
                     t1+=6;
                     t2+=6;
                     t3+=6;
                 }
             }
         }
         if(swapt==5)
         {
              glColor3f(1.0, 0.0, 0.0);
              renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 2");
             t1=-14;
             t2=-15;
             t3=-13;
             if(wait<=20)
                wait+=0.02;
             else
             {
                swapt++;
                t1+=6;
                t2+=6;
                t3+=6;
             }

         }





         if(swapt==6)
         {

             glColor3f(1.0, 0.0, 0.0);

             renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Iteration 2");
             if(first)
             {
                 if(q3<=0)
                    q3+=0.02;
                 else
                 {
                     second=true;
                     first=false;
                 }
             }
             if(second)
             {
                 if(p3<=-2.0||p4>=-8.0)
                 {
                     if(p3<=-2.0)
                        p3+=0.02;
                     if(p4>=-8.0)
                        p4-=0.02;

                 }
                 else
                 {
                     second=false;

                     third=true;
                     p3-=0.02;
                 }
             }
             if(third)
             {

                 if(q3>=-6)
                    q3-=0.02;
                 else
                 {
                     third=false;
                     first=true;
                     swapt++;
                     Sleep(500);
                     t1+=6;
                     t2+=6;
                     t3+=6;
                     sorted=true;

                 }
             }
         }
     }
     if(sorted)
     {
        glColor3f(1.0, 0.0, 0.0);

        renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"Sorting Complete");
        renderBitmapString(-10.0,8.0,GLUT_BITMAP_TIMES_ROMAN_24,"Press R to restart Simulation");

     }


     glutPostRedisplay();


     glPushMatrix();


     glColor3f(1.0, 0.0, 0.0);
     glBegin(GL_TRIANGLES);
             glVertex2f(t1, 1);
             glVertex2f(t2, 4);
             glVertex2f(t3, 4);
    glEnd();

     glColor3f(1.0, 0.0, 0.0);
     renderBitmapString(-23.0,23.0,GLUT_BITMAP_TIMES_ROMAN_24,"Simulation of bubble sort Algorithm");

     glColor3f(0.0, 1.0, 0.0);
     circle(1,1,p1,q1);
     glColor3f(1.0, 0.0, 0.0);
     glRasterPos2f(p1-0.2,q1-0.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'6');

     glColor3f(0.0, 1.0, 0.0);
     circle(1,1,p2,q2);
     glColor3f(1.0, 0.0, 0.0);
     glRasterPos2f(p2-0.2,q2-0.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'2');

     glColor3f(0.0, 1.0, 0.0);
     circle(1,1,p3,q3);
     glColor3f(1.0, 0.0, 0.0);
     glRasterPos2f(p3-0.2,q3-0.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'4');

     glColor3f(0.0, 1.0, 0.0);
     circle(1,1,p4,q4);
     glColor3f(1.0, 0.0, 0.0);
     glRasterPos2f(p4-0.2,q4-0.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'3');

     glColor3f(0.0, 1.0, 0.0);
     circle(1,1,p5,q5);
     glColor3f(1.0, 0.0, 0.0);
     glRasterPos2f(p5-0.2,q5-0.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'5');

     glPopMatrix();

     //table up
     glColor3f(0.82,0.41,0.12);
     glRectf(12.0,-7.0,-16.0,-9.0);


     glColor3f(1.0, 1.0, 1.0);
     glRasterPos2f(-14.2,-8.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'0');


     glColor3f(1.0, 1.0, 1.0);
     glRasterPos2f(-8.2,-8.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'1');

     glColor3f(1.0, 1.0, 1.0);
     glRasterPos2f(-2.2,-8.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'2');


     glColor3f(1.0, 1.0, 1.0);
     glRasterPos2f(3.8,-8.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'3');


     glColor3f(1.0, 1.0, 1.0);
     glRasterPos2f(9.8,-8.5);
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'4');

     glColor3f(0.82,0.41,0.12);
     glRectf(9.0,-8.0,8.3,-23.0);

     glColor3f(0.82,0.41,0.12);
     glRectf(-13.0,-8.0,-12.3,-23.0);


     glColor3f(0.0,0.0,0.0);
     glRectf(24.5,24.0,7.0,5.0);


     glColor3f(1.0,1.0,1.0);
     glRectf(24.0,23.0,7.5,6.0);

     glColor3f(0.0, 0.0, 0.0);

    renderBitmapString(11.0,22.0,GLUT_BITMAP_9_BY_15,"***Bubble Sort Algorithm***");

    renderBitmapString(9.0,20.0,GLUT_BITMAP_8_BY_13,"func bubblesort( var a as array )");

    renderBitmapString(9.0,19.0,GLUT_BITMAP_8_BY_13,"for i from 1 to N");

    renderBitmapString(10.0,18.0,GLUT_BITMAP_8_BY_13,"for j from 0 to N - 2");

    renderBitmapString(11.0,17.0,GLUT_BITMAP_8_BY_13,"if a[j] > a[j + 1]");

    renderBitmapString(12.0,16.0,GLUT_BITMAP_8_BY_13,"swap( a[j], a[j + 1] )");

    renderBitmapString(9.0,15.0,GLUT_BITMAP_8_BY_13,"end func");

    renderBitmapString(9.0,12.0,GLUT_BITMAP_8_BY_13,"Input:");

    renderBitmapString(9.0,10.0,GLUT_BITMAP_8_BY_13,"N=5");

    renderBitmapString(9.0,9.0,GLUT_BITMAP_8_BY_13,"Array= 6 2 4 3 5");


    if(sim==false)
    {

    glColor3f(1.0, 0.0, 0.0);

    renderBitmapString(-10.0,10.0,GLUT_BITMAP_TIMES_ROMAN_24,"PRESS S TO START SIMULATION");

    }



    glFlush();
}


void init(void)
{
	glClearColor (1.0, 1.0, 0.88, 0.0);
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
}

void simulate()
{
    sim=true;
    glutPostRedisplay();


}
reinitialize()
{
    p1=-14.0,q1=-6.0,p2=-8.0,q2=-6.0,p3=-2.0,q3=-6.0,p4=4.0,q4=-6.0,p5=10.0,q5=-6.0,t1=-14,t2=-15,t3=-13;
    sim=false;
    sorted=false;
    first=true;
    second=false;
    third=false;
    swapt=1;
    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{

	switch (key) {

      case 's':
				simulate();
				break;
      case 'S':
				simulate();
				break;
	  case 'r':
                reinitialize();
				break;
      case 'R':
               reinitialize();
               break;

	  default:
			break;
	}
}

int main()
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1200, 800);
	glutInitWindowPosition (100, 0);
	glutCreateWindow ("Bubble sort Algorithm Simulation ");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

