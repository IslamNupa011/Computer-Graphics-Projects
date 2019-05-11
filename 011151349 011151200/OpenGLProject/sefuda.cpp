#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>

#define rightWindow 120
#define leftWindow -20

double m=0,n=0,speed =0.1,moveHead =8,bottleAngle=0;
bool running=false,carShow=false,isAllset= false,gotBottle = false,isHeadMove=false,isDrinking = false;
const float DEG2RAD = 3.14159/180.0;
double initialPosX=0,initialPosY =45,initialScaleX=0.8,initialScaleY=1,bottleScaleX=1,bottleScaleY=1;
double bottleX = 0,bottleY=0;


void drawBottle(){

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex3f(-33.5,13,0);
    glVertex3f(-31.5,13,0);
     glVertex3f(-31.5,15,0);
    glVertex3f(-33.5,15,0);
    glEnd();

    glColor3f(0.863, 0.078, 0.235);
    glBegin(GL_QUADS);
    glVertex3f(-31,8,0);
    glVertex3f(-34,8,0);
    glVertex3f(-33.5,13,0);
    glVertex3f(-31.5,13,0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-35,-5,0);
    glVertex3f(-30,-5,0);
    glVertex3f(-30,8,0);
    glVertex3f(-35,8,0);
    glEnd();

}
void drawRoad(){
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
    glVertex3f(-400,-55,0);
    glVertex3f(400,-55,0);
    glVertex3f(400,-5,0);
    glVertex3f(-400,-5,0);
    glEnd();
}

void drawRoadDivider(){
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex3f(-6,-27,0);
    glVertex3f(6,-27,0);
    glVertex3f(6,-31,0);
    glVertex3f(-6,-31,0);
    glEnd();
}

void drawCircle(double radius,double R,double G,double B){
    glColor3f(R,G,B);

    double pi= 2*acos(-1);
    double t=0,a=0.002;
    glBegin(GL_TRIANGLES);
    for(double t=0 ;t<=pi ;t+=a){
        glVertex3f(0,0,0);
        glVertex3f(radius*cos(t-a),radius*sin(t-a),0);
        glVertex3f(radius*cos(t),radius*sin(t),0);
    }
    glEnd();
}

void drawEye(){

    drawCircle(0.4,0,0,0);
    glPushMatrix();
    glScaled(1.5,1,1);
    drawCircle(0.79,1,1,1);
    glPopMatrix();

    glColor3f(0,0,0);
    const float DEG2RAD = 3.14159/180.0;

    glBegin(GL_LINE_LOOP);
	for(int i=0; i < 360; i++)
	{
		 //convert degrees into radians
		float degInRad = i*DEG2RAD;
		glVertex2f(cos(degInRad)*1.5,sin(degInRad)*0.8);
	}
	glEnd();

    glBegin(GL_LINES);
    glVertex3f(-2.2,1.2,0);
    glVertex3f(2.2,1.2,0);

    glVertex3f(2.2,1.2,0);
    glVertex3f(2.2,-1.2,0);


    glVertex3f(2.2,-1.2,0);
    glVertex3f(-2.2,-1.2,0);

    glVertex3f(-2.2,-1.2,0);
    glVertex3f(-2.2,1.2,0);

    glEnd();
}

void drawFace(){


    //mouth
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(-3.5,-1,0);
    glVertex3f(3.5,-1,0);


    glVertex3f(-2,-2,0);
    glVertex3f(2,-2,0);
    glEnd();

    //right eye
    glPushMatrix();
    glTranslated(3.8,5.8,0);
    drawEye();
    glPopMatrix();

    //left eye
    glPushMatrix();
    glTranslated(-3.8,5.8,0);
    drawEye();
    glPopMatrix();

    //upper part of nose
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex3f(-1.5,6,0);
    glVertex3f(1.5,6,0);
    glVertex3f(1.5,7,0);
    glVertex3f(-1.5,7,0);
    glEnd();



    //nose
    glColor3f(0.722, 0.525, 0.043);
    glBegin(GL_TRIANGLES);
    glVertex3f(0,6,0);
    glVertex3f(-1.5,1,0);
    glVertex3f(1.5,1,0);
    glEnd();
}

void bottomPart(){

    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex3f(-14,-22,0);
    glVertex3f(14,-22,0);
    glVertex3f(14,-32,0);
    glVertex3f(-14,-32,0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-14,-32,0);
    glVertex3f(-3,-32,0);
    glVertex3f(-3,-38,0);
    glVertex3f(-14,-38,0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(3,-32,0);
    glVertex3f(14,-32,0);
    glVertex3f(14,-38,0);
    glVertex3f(3,-38,0);
    glEnd();

    //left leg
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_QUADS);
    glVertex3f(-11.8,-38,0);
    glVertex3f(-5.4,-38,0);
    glVertex3f(-5.4,-42,0);
    glVertex3f(-11.8,-42,0);
    glEnd();


    //right leg
    glBegin(GL_QUADS);
    glVertex3f(5.4,-38,0);
    glVertex3f(11.8,-38,0);
    glVertex3f(11.8,-42,0);
    glVertex3f(5.4,-42,0);
    glEnd();

    //left leg blue
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex3f(-12,-38,0);
    glVertex3f(-5,-38,0);
    glVertex3f(-5,-42,0);
    glVertex3f(-12,-42,0);
    glEnd();

     //left leg blue
    glBegin(GL_QUADS);
    glVertex3f(5,-38,0);
    glVertex3f(12,-38,0);
    glVertex3f(12,-42,0);
    glVertex3f(5,-42,0);
    glEnd();


    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex3f(-18,-42,0);
    glVertex3f(-5,-42,0);
    glVertex3f(-5,-46,0);
    glVertex3f(-18,-46,0);
    glEnd();


    glBegin(GL_QUADS);
    glVertex3f(5,-42,0);
    glVertex3f(18,-42,0);
    glVertex3f(18,-46,0);
    glVertex3f(5,-46,0);
    glEnd();



}


void drawHand(){

    //right hand
    glPushMatrix();

    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_QUADS);
    glVertex3f(9,-7,0);
    glVertex3f(27,-18,0);
    glVertex3f(25,-21,0);
    glVertex3f(9,-14,0);
    glEnd();

    glTranslated(-25,-19,0);
    drawCircle(3,0.871, 0.722, 0.529);
    glPopMatrix();


    //left hand
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.871, 0.722, 0.529);
    glVertex3f(-9,-7,0);
    glVertex3f(-27,-18,0);
    glVertex3f(-25,-21,0);
    glVertex3f(-9,-14,0);
    glEnd();

    glTranslated(25,-19,0);
    drawCircle(3,0.871, 0.722, 0.529);
    glPopMatrix();

}


void drawCharacter(){

    drawHand();

    bottomPart();

    glPushMatrix(); /// bound head part

    drawFace();
    //right ear
    glPushMatrix();
    glTranslated(8,5.8,0);
    drawCircle(2,0.871, 0.722, 0.529);
    glPopMatrix();

    //left ear
    glPushMatrix();
    glTranslated(-8,5.8,0);
    drawCircle(2,0.871, 0.722, 0.529);
    glPopMatrix();

    //forehead
    glPushMatrix();
    glPushMatrix();
    glScaled(1.1,1.5,1);
    glTranslated(0,3,0);
    drawCircle(7,0.871, 0.722, 0.529);
    glPopMatrix();

    //face
    glScaled(1.4,0.8,1);
    drawCircle(8,0.871, 0.722, 0.529);
    glPopMatrix();

    glPopMatrix(); /// bound head part

    //belly
    glPushMatrix();
    glTranslated(0,-18,0);
	drawCircle(14,0.871, 0.722, 0.529);
	glPopMatrix();

}


void drawSky(){
    glBegin(GL_QUADS);
    glColor3f(0.529,0.808,0.922);
    glVertex3f(-400,200,0);
    glVertex3f(400,200,0);
    glVertex3f(400,30,0);
    glVertex3f(-400,30,0);
    glEnd();
}



void drawTree(){
    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex3f(-60,-50,0);
    glVertex3f(-50,-50,0);
    glVertex3f(-50,-40,0);
    glVertex3f(-60,-40,0);
    glEnd();
}

void drawAxis(){
    glBegin(GL_LINES);

	//+X axis
	glColor3f(1, 0, 0);//red
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);

	//-X axis
	glColor3f(1, 0, 0);//red
	glVertex3f(0, 0, 0);
	glVertex3f(-1000, 0, 0);

    //+Y axis
	glColor3f(1, 1, 0);//yellow
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
	glColor3f(0, 0, 1);//blue
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1000);
	glEnd();
}


void drawCar(){

    glColor3f(0,0,0);

    glBegin(GL_QUADS);
    glVertex3f(-16,10,0);
    glVertex3f(-18,10,0);
    glVertex3f(-22,16,0);
    glVertex3f(-20,16,0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(22,10,0);
    glVertex3f(25,10,0);
    glVertex3f(18,20,0);
    glVertex3f(15,20,0);
    glEnd();

    glPushMatrix();
    glTranslated(15,-10,0);
    drawCircle(3,1,1,1);
    drawCircle(7,0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8,-10,0);
    drawCircle(3,1,1,1);
    drawCircle(7,0,0,0);
    glPopMatrix();

    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3f(-25,-10,0);
    glVertex3f(25,-10,0);
    glVertex3f(25,10,0);
    glVertex3f(-25,10,0);
    glEnd();


    glPushMatrix();
    glTranslated(25,0,0);
    drawCircle(10,1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-25,0,0);
    drawCircle(10,1,0,0);
    glPopMatrix();

}

void display()
{
	//codes for Models, Camera

	//clear the display
	//color black
	glClearColor(0,0.5,0,0);

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


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	***************************************************/

	//drawAxis();


	glPushMatrix();     /// for  car and character
    glTranslated(m,0,0);
    glPushMatrix();
	if(carShow == true){
        glTranslated(-30,-35,0);
	    drawCar();

	}
	glPopMatrix();

	///draw bottle
	glPushMatrix();
	glRotated(bottleAngle,0,0,1);
	glTranslated(bottleX,bottleY,0);
	glScaled(bottleScaleX,bottleScaleY,1);
	drawBottle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(initialPosX,initialPosY,0);
	glScaled(initialScaleX,initialScaleY,1);
	drawCharacter();
	glPopMatrix();

	glPopMatrix();



    glTranslated(n,0,0); ///for road and divider
	drawRoadDivider();

	glPushMatrix();
	glTranslated(45,0,0);
	drawRoadDivider();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-45,0,0);
	drawRoadDivider();
	glPopMatrix();



	drawRoad();
	drawSky();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void keyboardListener(unsigned char key, int x, int y)
{
    if(key == 's' && carShow == true && isAllset == true){
        running=true;
    }
    else if(key == 'c'){
        carShow=true;
    }
    else if(key == 'u' && carShow == true && gotBottle == true ){
        initialPosX=-30;
        initialPosY = -7;
        initialScaleX= 0.55;
        initialScaleY = 0.75;

        bottleX = -21;
        bottleY = -20;
        bottleScaleX = 0.7;
        bottleScaleY = 0.8;
        isAllset = true;
        isHeadMove = false;

    }
    else if(key == 't' && !isAllset){
        bottleX = 12.5;
        bottleY = 26;
        gotBottle = true;
        isHeadMove = true;
    }
    else if(key == 'd' && isAllset )
    {
        bottleScaleX = 0.5;
        bottleScaleY = 0.6;
        bottleX = -10;
        bottleY = -26;
        bottleAngle = -18;
        isDrinking = true;
    }

    else if(key == 'r' && isAllset )
    {
        bottleX = -21;
        bottleY = -20;
        bottleScaleX = 0.7;
        bottleScaleY = 0.8;
        bottleAngle = 0;
        speed -=0.2;
        isDrinking = false;
    }

}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0001;

	moveHead *=-1;

	if(running == true ){
        m+=speed;
        n-=speed;
	}
	//codes for any changes in Models

	if(m > rightWindow){
        m=-50;
	}

	if(n < leftWindow){
        n = 20;
	}

	if(isDrinking)
        speed +=0.01;
    else if(speed > 0.4)
        speed -=0.01;

	//this will call the display AGAIN
	glutPostRedisplay();

}

void init()
{

	//clear the screen
	glClearColor(0,0.5,0,0);


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

	glutInitWindowSize(1000, 850);
	glutInitWindowPosition(100, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("SEUDA");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);
	//what you want to do in the idle time (when no drawing is occuring)
	glutIdleFunc(animate);



	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}
