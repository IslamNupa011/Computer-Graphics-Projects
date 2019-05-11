#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <windows.h>
#include <glut.h>
#define PI 3.1415926535897932384626433832795
static int mercuryRadius = 15;
static int venusRadius = 20;
static int earthRadius = 25;
static int marsRadius = 30;
static int jupitarRadius = 40;
static int SaturaRadius = 52;
static int UrenusRadius = 57;
static int NeptunRadius = 62;
static int PlutoRadius = 67;


//double cameraAngle;
char y[] = "y axis";
char x[] = "x axis";
char z[] = "z axis";
char sun[] = "SUN";
char mercury[] = "mercury";
char venus[] = "venus";
char earth[] = "earth";
char mars[] = "mars";
char jupitar[] = "jupitar";
char Satura[] = "Satura";
char Urenus[] = "Urenus";
char Neptun[] = "Neptun";
char Pluto[] = "Pluto";



double R, Rspeed, vAngle, hAngle, angleSpeed,B=0,button=0,px=0,py=0,pz = 0;
double Cmr_x=0, Cmr_y=0, Cmr_z=0, lk_x=0, lk_y=1, lk_z=0, UP_x=0, UP_y=0, UP_z=1, Rx=1;

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
    glColor3f(1, 1, 1);//cyan
    glRasterPos3f(0, 50,0);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; y[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, y[i]);
    }
    glRasterPos3f(50, 0,0);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; x[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, x[i]);
    }
    glRasterPos3f(0, 0,50);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; z[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, z[i]);
    }
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .02) //<-- Change this Value
 					glVertex3f(cos(i) * mercuryRadius, sin(i) * mercuryRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .02) //<-- Change this Value
 					glVertex3f(cos(i) * venusRadius, sin(i) * venusRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .02) //<-- Change this Value
 					glVertex3f(cos(i) * earthRadius, sin(i) * earthRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .02) //<-- Change this Value
 					glVertex3f(cos(i) * marsRadius, sin(i) * marsRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * jupitarRadius, sin(i) * jupitarRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * SaturaRadius, sin(i) * SaturaRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * UrenusRadius, sin(i) * UrenusRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * NeptunRadius, sin(i) * NeptunRadius, 0 );
    glEnd();
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * PlutoRadius, sin(i) * PlutoRadius, 0 );
    glEnd();

	glColor3f(0.5, 0.5, 0.5);//gray

	//glBegin(GL_LINES);
	//for (i = -10; i <= 10; i++)
	//{
	//	if (i == 0)
	//	{
	//		continue;//SKIP the MAIN axes
	//	}

		//lines parallel to Y-axis
	//	glVertex3f(i * 10, -100, 0);
	//	glVertex3f(i * 10, 100, 0);

		//lines parallel to X-axis
	//	glVertex3f(-100, i * 10, 0);
	//	glVertex3f(100, i * 10, 0);
	//}
	//glEnd();
}

void drawsolarsystem(){

    //sun
    glColor3f(1,0,0);
    glutWireSphere(10,2000,2000);
    glRasterPos3f(0,0,12);
    for ( int i = 0; sun[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, sun[i]);
    }
    glColor3f(1,1,0);
      // move in 10 pixels from the left and bottom edges


    //mercury
    glPushMatrix();
    glRotatef(500+B*10, 0,0,1);
    glTranslatef(15,0,0);

    glRasterPos3f(0,0,2);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; mercury[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, mercury[i]);
    }
    glColor3f(.9,.6,.25);
    glRotatef(B+1000, 0,0,1);
    glutWireSphere(1,20,20);
    glColor3f(.9,.6,.25);
    glutWireSphere(.99,100,20);
    glPopMatrix();



    //venus
    glPushMatrix();
    glRotatef(400+B*8, 0,0,1);
    glColor3f(.8,.5,.2);
    glTranslatef(venusRadius,0,0);
    glRasterPos3f(0,0,2);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; venus[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, venus[i]);
    }
    glRotatef(B+8, 0,0,1);
    glutWireSphere(1.2,200,200);
    glPopMatrix();

    //earth
    glPushMatrix();
    glRotatef(700+B*6, 0,0,1);
    glColor3f(0,.8,1);
    glTranslatef(earthRadius,0,0);
    glRasterPos3f(0,0,2);
    for ( int i = 0; earth[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, earth[i]);
    }
    glRotatef(B+6, 1,0,1);
    glutWireSphere(1.5,200,200);

    //moon
    glPushMatrix();
    glRotatef(4*B,0,0,1);
    glColor3f(1, 1, 1);//cyan
    glBegin(GL_POINTS);
    for(double i = 0; i < 2 * PI; i += .1)
 					glVertex3f(cos(i) * 2.5, sin(i) * 2.5, 0 );
    glEnd();
    glColor3f(0,0,1);
    glTranslatef(-2.5,0,0);
    glutWireSphere(.2,200,200);
    glPopMatrix();
    glPopMatrix();


    //mars
    glPushMatrix();
    glRotatef(200+B*5, 0,0,1);
    glColor3f(.9,.4,.2);
    glTranslatef(marsRadius,0,0);
    glRasterPos3f(0,0,2);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; mars[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, mars[i]);
    }
    glRotatef(B, 0,0,1);
    glutWireSphere(.8,200,200);
    glPopMatrix();

    //jupitar
    glPushMatrix();
    glRotatef(300+B*4, 0,0,1);
    glColor3f(.7,.6,.4);
    glTranslatef(jupitarRadius,0,0);
    glRasterPos3f(0,0,5);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; jupitar[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, jupitar[i]);
    }
    glRotatef(B, 0,0,1);
    glutWireSphere(4,200,200);
    glPopMatrix();
    //Satura
    glPushMatrix();
    glRotatef(100+B*3, 0,0,1);
    glColor3f(.7,.6,.5);
    glTranslatef(SaturaRadius,0,0);
    glRasterPos3f(0,0,4);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; Satura[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, Satura[i]);
    }
    //cyan
    glRotatef(B, 0,1,0);
    for(double j =3.5; j< 4.5; j += .1)
    {
        glColor3f(.8,.7,.6);
        glBegin(GL_POINTS);
        for(double i = 0; i < 2 * PI; i += .02) //<-- Change this Value
 					glVertex3f(cos(i) * j, sin(i) * j ,0);
        glEnd();

    }
    glColor3f(.7,.6,.5);
    glutWireSphere(3,200,200);
    glPopMatrix();
    //Urenus
    glPushMatrix();
    glRotatef(800+B*2, 0,0,1);

    glTranslatef(UrenusRadius,0,0);
    for(double j =1.2; j< 1.5; j += .1)
    {
        glColor3f(.2,.7,.9);
        glBegin(GL_POINTS);
        for(double i = 0; i < 2 * PI; i += .01) //<-- Change this Value
 					glVertex3f(cos(i) * j, sin(i) * j ,0);
        glEnd();

    }
    glColor3f(.2,.8,.9);
    glRasterPos3f(0,0,1.5);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; Urenus[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, Urenus[i]);
    }
    glRotatef(B, 0,0,1);
    glutWireSphere(.9,200,200);
    glPopMatrix();
    //Neptun
    glPushMatrix();
    glRotatef(B*1.5, 0,0,1);
    glColor3f(.2,.5,.8);
    glTranslatef(NeptunRadius,0,0);
    glRasterPos3f(0,0,1.2);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; Neptun[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, Neptun[i]);
    }
    glRotatef(B, 0,0,1);
    glutWireSphere(.7,200,200);
    glPopMatrix();
    //Pluto
    glPushMatrix();
    glRotatef(450+B, 0,0,1);
    glColor3f(.6,.5,.4);
    glTranslatef(PlutoRadius,0,0);
    glRasterPos3f(0,0,.9);  // move in 10 pixels from the left and bottom edges
    for ( int i = 0; Pluto[i] != '\0'; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, Pluto[i]);
    }
    glRotatef(B, 0,0,1);
    glutWireSphere(.3,200,200);
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
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,0,100,	0,0,0,	0,1,0);
	//gluLookAt(200 * sin(cameraAngle), -200 * cos(cameraAngle), 50, 30, 0, 20, 0, 0, 1);

    double x = sqrt(R*R+1);
    double y = atan(1.0/R);

    double a = x*cos(vAngle+y)*cos(hAngle)-R*cos(vAngle)*cos(hAngle);
    double b = x*cos(vAngle+y)*sin(hAngle)-R*cos(vAngle)*sin(hAngle);
    double c = x*sin(vAngle+y)-R*sin(vAngle);

	gluLookAt(R*cos(vAngle)*cos(hAngle),R*cos(vAngle)*sin(hAngle),R*sin(vAngle),  px,py,pz,  a,b,c);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	***************************************************/

	// draw the three major AXES
	//drawAxis();

	//some grid lines along the field
	drawGrid();

    // drawing a house
    drawsolarsystem();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}
void keyboardListener(unsigned char key, int x, int y)
{
    if (key == 'w')
	{
	     button+=0.01;
	}
	if (key == 's')
	{
	    button-=0.01;
	}

    if(key == '4')
    {
        py -= 1;

    }
    if(key == '5')
    {
        py = 0;
        px = 0;
        pz = 0;
    }
    if(key == '6')
    {
        py += 1;
    }
    if(key == '8')
    {
        px -= 1;
    }
    if(key == '2')
    {
        px += 1;
    }
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {

    }

   else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
    {

    }

}

void specialKeyListener(int key, int x, int y)
{


	if (key == GLUT_KEY_UP)
	{
		vAngle+=angleSpeed;
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
	{
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
	B=B+button;
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

	glutInitWindowSize(700, 600);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("3D SOLAR SYSTEM");

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
    glutMouseFunc(mouse);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}
