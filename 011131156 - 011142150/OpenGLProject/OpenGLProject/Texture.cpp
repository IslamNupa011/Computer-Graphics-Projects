#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<Windows.h>

#include<glut.h>

double cameraAngle;
double move_X, move_Y, move_Z;
int canDrawGrid, canDrawAxis;
double move_ball_z;

double cameraRadius, cameraHeight, cameraAngleDelta;

int num_texture = -1;
GLuint grassimg;
GLuint cyl;
GLuint wall;
GLuint ball;
GLuint football;

int LoadBitmapImage(char *filename)
{
	int i, j = 0;
	FILE *l_file;
	unsigned char *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

	if ((l_file = fopen(filename, "rb")) == NULL) return (-1);

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);

}

void loadImage()
{
	grassimg = LoadBitmapImage("image/grass.bmp");
	cyl = LoadBitmapImage("image/cyl.bmp");
	wall = LoadBitmapImage("image/wall.bmp");
	ball = LoadBitmapImage("image/ball.bmp");
	football = LoadBitmapImage("image/football.bmp");
	if (grassimg != -1)
		printf("Load successful!!\n");
	else printf("Image loading Failed!!\n");
}

void drawGridAndAxes() {

	// draw the three major AXES

	glBegin(GL_LINES);
	//X axis
	glColor3f(0, 1, 0);	//100% Green
	glVertex3f(-150, 0, 0);
	glVertex3f(150, 0, 0);

	//Y axis
	glColor3f(0, 0, 1);	//100% Blue
	glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
	glVertex3f(0, 150, 0);

	//Z axis
	glColor3f(1, 1, 1);	//100% White
	glVertex3f(0, 0, -150);
	glVertex3f(0, 0, 150);
	glEnd();

	//some gridlines along the field
	int i;

	glColor3f(0.5, 0.5, 0.5);	//grey
	glBegin(GL_LINES);
	for (i = -10; i <= 10; i++) {

		if (i == 0)
			continue;	//SKIP the MAIN axes

						//lines parallel to Y-axis
		glVertex3f(i * 10, -100, 0);
		glVertex3f(i * 10, 100, 0);

		//lines parallel to X-axis
		glVertex3f(-100, i * 10, 0);
		glVertex3f(100, i * 10, 0);
	}
	glEnd();

}


void display() {
	//codes for Models, Camera

	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers to preset values

															/***************************
															/ set-up camera (view) here
															****************************/
															//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);		//specify which matrix is the current matrix

									//initialize the matrix
	glLoadIdentity();				//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

									//now give three info
									//1. where is the camera (viewer)?
									//2. where is the camera looking?
									//3. Which direction is the camera's UP direction?

									//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight, 0, 0, 0, 0, 0, 1);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	//drawGridAndAxes();

	/****************************
	/ Add your objects from here
	****************************/

	// all 3d transparent objects
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1,1,1,.2);
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(30,0,0);
	glVertex3f(30,0,50);
	glVertex3f(0,0,50);
	glEnd();

	glDisable(GL_BLEND);*/

	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grassimg);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(-100,100,0);
	glTexCoord2f(0,0);
	glVertex3f(-100,-100,0);
	glTexCoord2f(1,0);
	glVertex3f(100,-100,0);
	glTexCoord2f(1,1);
	glVertex3f(100,100,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex3f(0,0,30);
	glTexCoord2f(0,0);
	glVertex3f(70,0,30);
	glTexCoord2f(1,0);
	glVertex3f(70,0,0);
	glTexCoord2f(1,1);
	glVertex3f(0,0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/


	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, football);
	glColor3f(1,1,1);
	GLUquadricObj *sphare = gluNewQuadric();
	gluQuadricTexture(sphare, GL_TRUE);
	gluSphere(sphare, 10,20,20);
	glDisable(GL_TEXTURE_2D);*/

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cyl);
	glColor3f(1, 1, 1);
	GLUquadricObj *cylender = gluNewQuadric();
	gluQuadricTexture(cylender, GL_TRUE);
	gluCylinder(cylender, 15, 15, 50, 10, 10);
	glDisable(GL_TEXTURE_2D);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate() {
	//codes for any changes in Models, Camera

	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.

	//codes for any changes in Models
	if (move_ball_z  > 100) {
		move_ball_z = 0;
	}
	else {
		move_ball_z = 100;
	}


	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void init() {
	//codes for initialization
	loadImage();

	cameraAngle = 0;	//angle in radian
	move_X = 0;
	move_Y = 0;
	move_Z = 0;
	canDrawGrid = 1;
	canDrawAxis = 1;
	move_ball_z = 0;

	cameraAngleDelta = .001;

	cameraRadius = 150;
	cameraHeight = 50;

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

void keyboardListener(unsigned char key, int x, int y) {
	switch (key) {

	case '1':
		move_X += 1;
		break;

	case '2':
		move_X -= 1;
		break;

	case '3':
		move_Y += 1;
		break;
	case '4':
		move_Y -= 1;
		break;

	case '5':
		move_Z += 1;
		break;
	case '6':
		move_Z -= 1;
		break;
	case '8':

		break;

	case 'g':
		canDrawGrid ^= 1;
		break;

	case 'h':
		canDrawAxis ^= 1;
		break;

	case 'p':
		break;

	case 'r':
		break;

	default:
		break;
	}
}

void specialKeyListener(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:		//down arrow key
		cameraRadius += 10;
		break;
	case GLUT_KEY_UP:		// up arrow key
		if (cameraRadius > 10)
			cameraRadius -= 10;
		break;

	case GLUT_KEY_RIGHT:
		cameraAngle += 0.01;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle -= 0.01;
		break;

	case GLUT_KEY_PAGE_UP:
		cameraHeight += 10;
		break;
	case GLUT_KEY_PAGE_DOWN:
		cameraHeight -= 10;
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		//	cameraAngleDelta = 0.001;
		break;
	case GLUT_KEY_END:
		//	cameraAngleDelta = 0;
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y) {	//x, y is the x-y of the screen (2D)
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			cameraAngleDelta = -cameraAngleDelta;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);							//initialize the GLUT library

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Some Title");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
