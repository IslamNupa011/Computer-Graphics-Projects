#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <math.h>
#include <windows.h>
#include <vector>
#include <glut.h>
#include<algorithm>
#include <unistd.h>
#define Length 4

using namespace std;
double A[Length][Length]; //Angle of Rotation
double S[Length][Length]; //1 if Selected 0 if not
double C[Length][Length][3];//Color in RGB
double V[Length][Length]; //Value
double F[Length][Length]; //Finished
vector<int> values;
vector<int> R,G,B;
double Size=10;

int SELECTED_X=0,SELECTED_Y=0;

void darwSquare(double SIZE, double R, double G, double B){
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
    {
        glVertex3f(0,0,0);
        glVertex3f(SIZE,0,0);
        glVertex3f(SIZE,SIZE,0);
        glVertex3f(0,SIZE,0);
    }
    glEnd();
}
void drawHollowRectangle(int X,int Y){
    int Border=1;
    glTranslatef(20*X,20*Y,0);
    glBegin(GL_LINES);

	glColor3f(1, 1, 0);//

	glVertex3f(-Border, -Border, 0);
	glVertex3f(Size+Border, -Border, 0);

    glColor3f(1, 1, 0);//
	glVertex3f(Size+Border, -Border, 0);
	glVertex3f(Size+Border, Size+Border, 0);

	glVertex3f(Size+Border, Size+Border, 0);
	glVertex3f(-Border, Size+Border, 0);

	glVertex3f(-Border, Size+Border, 0);
	glVertex3f(-Border, -Border, 0);


    glEnd();
}
void drawGrid(){
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);//red
	glVertex3f(-1000, 0, 0);
	glVertex3f(1000, 0, 0);

	glColor3f(1, 0, 0);//red
	glVertex3f(0, -1000, 0);
	glVertex3f(0, 1000, 0);

	glEnd();

}
void drawTiles(int length){
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++)
        {
            glPushMatrix();
            glTranslatef(20*i,20*j,0);
            glTranslatef(Size/2,0,0);
            glRotatef(A[i][j],0,1,0);
            glTranslatef(-Size/2,0,0);
            darwSquare(Size,C[i][j][0],C[i][j][1],C[i][j][2]);
            glPopMatrix();
        }
    }
}
bool isMatch(int x1,int y1,int x2,int y2){
    if(V[x1][y1]==V[x2][y2])
        return true;
    return false;

}
void display(){
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
	gluLookAt(40,20,150,	40,20,0,	0,1,0);
	//drawGrid();

	drawTiles(Length);
	glPushMatrix();
    drawHollowRectangle(SELECTED_X,SELECTED_Y);
	glPopMatrix();




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void animate(){
	//codes for any changes in Models, Camera

	//this will call the display AGAIN
	vector<int> v;
	for(int i=0;i<Length;i++){
	    for(int j=0;j<Length;j++){
            if(S[i][j]==1){
                    if(A[i][j]==180){
                        v.push_back(i);
                        v.push_back(j);
                    }

                if(A[i][j]<180)
                    A[i][j]+=.5;
                C[i][j][0]=R[V[i][j]];
                C[i][j][1]=G[V[i][j]];
                C[i][j][2]=B[V[i][j]];
            }
            if(A[i][j]==180 && v.size()==4){

                    if(isMatch(v[0],v[1],v[2],v[3])){ //Matched

                            A[v[0]][v[1]]=0;
                            F[v[0]][v[1]]=1;
                            S[v[0]][v[1]]=0;
                            C[v[0]][v[1]][0]=0;
                            C[v[0]][v[1]][1]=0;
                            C[v[0]][v[1]][2]=0;


                            A[v[2]][v[3]]=0;
                            F[v[2]][v[3]]=1;
                            S[v[2]][v[3]]=0;
                            C[v[2]][v[3]][0]=0;
                            C[v[2]][v[3]][1]=0 ;
                            C[v[2]][v[3]][2]=0;
                            break;

                    }
                    else{   //Didn't match
                        A[v[0]][v[1]]=0;
                        S[v[0]][v[1]]=0;
                        C[v[0]][v[1]][0]=0;
                        C[v[0]][v[1]][1]=0;
                        C[v[0]][v[1]][2]=1;


                        A[v[2]][v[3]]=0;
                        S[v[2]][v[3]]=0;
                        C[v[2]][v[3]][0]=0;
                        C[v[2]][v[3]][1]=0;
                        C[v[2]][v[3]][2]=1;
                        break;
                    }

            }

	    }

	}
	glutPostRedisplay();
}

void init(){
	//clear the screen
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/

	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();
    R.push_back(1);
    R.push_back(1);
    R.push_back(1);
    R.push_back(0);
    G.push_back(1);
    G.push_back(0);
    G.push_back(1);
    G.push_back(1);
    B.push_back(1);
    B.push_back(0);
    B.push_back(0);
    B.push_back(0);
    for(int i=0;i<Length;i++){
        values.push_back(i);
        values.push_back(i);
        values.push_back(i);
        values.push_back(i);
    }

    random_shuffle(values.begin(),values.end());
    int val=0;
	for(int i=0;i<Length;i++){
        for(int j=0;j<Length;j++){

            A[i][j]=0;
            S[i][j]=0;
            V[i][j]=values[val];
            val++;
            F[i][j]=0;
            C[i][j][0]=0;
            C[i][j][1]=0;
            C[i][j][2]=1;
        }
	}

	/*
	gluPerspective() — set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}
void keyboardListener(unsigned char key, int x, int y){
    if(key=='w')
    {
        if(SELECTED_Y<Length-1)
        {
            SELECTED_Y+=1;
        }
    }
    else if(key=='s')
    {
        if(SELECTED_Y>0)
        {
            SELECTED_Y-=1;
        }
    }
    else if (key=='a')
    {
        if (SELECTED_X>0)
        {
            SELECTED_X-=1;
        }
    }
    else if (key== 'd')
    {
        if (SELECTED_X<Length-1)
        {
            SELECTED_X+=1;
        }
    }
    else if (key== 'r')
    {
        init();
    }
    else if (key == ' ')
	{
        if(F[SELECTED_X][SELECTED_Y]==0)
            S[SELECTED_X][SELECTED_Y]=1;

	}

}
void specialKeyListener(int key, int x, int y){
if (key == GLUT_KEY_UP)
	{
		if(SELECTED_Y<Length-1)
        {
            SELECTED_Y+=1;
        }
	}
	else if (key == GLUT_KEY_DOWN)
	{
		if(SELECTED_Y>0)
        {
            SELECTED_Y-=1;
        }
	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (SELECTED_X>0)
        {
            SELECTED_X-=1;
        }
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (SELECTED_X<Length-1)
        {
            SELECTED_X+=1;
        }
	}
	else if (key == GLUT_KEY_F1)
	{
		S[SELECTED_X][SELECTED_Y]=1;
	}
}
int main(int argc, char **argv){
	//initialize the GLUT library

	glutInit(&argc, argv);

	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Memory Test");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(keyboardListener);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

