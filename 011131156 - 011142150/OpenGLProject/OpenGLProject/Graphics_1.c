#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<GL/glut.h>

double cameraAngle;
double move_X, move_Y, move_Z;
int canDrawGrid, canDrawAxis;
double speed = 30, ang_speed = .1;
double cameraRadius, cameraHeight, cameraAngleDelta;
int num_texture = -1;
GLuint floorImg;
GLuint wallImg;

/***************************** VECTOR structure **********************************/

struct V;

V operator+(V a, V b);
V operator*(V a, V b);
V operator*(V b, double a);
V operator*(double a, V b);

struct V {
	double x, y, z;

	V() {}
	V(double _x, double _y) { x = _x; y = _y; z = 0; }
	V(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }


	double	mag() { return sqrt(x*x + y*y + z*z); }

	void 	norm() { double d = mag(); x /= d; y /= d;	z /= d; }
	V 		unit() { V ret = *this;	ret.norm(); return ret; }

	double	dot(V b) { return x*b.x + y*b.y + z*b.z; }
	V		cross(V b) { return V(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x); }


	double	projL(V on) { on.norm();	return this->dot(on); }
	V		projV(V on) { on.norm();	return on * projL(on); }

	V rot(V axis, double angle) {
		return this->rot(axis, cos(angle), sin(angle));
	}

	V rot(V axis, double ca, double sa) {
		V rotatee = *this;
		axis.norm();
		V normal = (axis * rotatee).unit();
		V mid = (normal * axis).unit();
		double r = rotatee.projL(mid);
		V ret = r*mid*ca + r*normal*sa + rotatee.projV(axis);
		return ret.unit();
	}
};

V operator+(V a, V b) { return V(a.x + b.x, a.y + b.y, a.z + b.z); }
V operator-(V a) { return V(-a.x, -a.y, -a.z); }
V operator-(V a, V b) { return V(a.x - b.x, a.y - b.y, a.z - b.z); }
V operator*(V a, V b) { return a.cross(b); }
V operator*(double a, V b) { return V(a*b.x, a*b.y, a*b.z); }
V operator*(V b, double a) { return V(a*b.x, a*b.y, a*b.z); }
V operator/(V b, double a) { return V(b.x / a, b.y / a, b.z / a); }




V loc, dir, perp;


V  _L(0, -150, 20);
V  _D(0, 1, 0);
V  _P(0, 0, 1);

/***************************** Texture Functions *******************************/

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
	floorImg = LoadBitmapImage("images/floor2.bmp");
	wallImg = LoadBitmapImage("images/wallx.bmp");
}

/****************************** GridLines and Axes ***********************************/

void gridAndAxis() {
	// draw the three major AXES
	if (canDrawAxis == 1) {
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
	}

	if (canDrawGrid == 1) {
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
}

/*********************************** Make Custom Cube ***********************************/
void solidCube1Part(double size) {
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-size, 0, size);
		glTexCoord2f(0, 0);
		glVertex3f(size, 0, size);
		glTexCoord2f(1, 0);
		glVertex3f(size, 0, -size);
		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, -size);
	glEnd();
}
void solidCube2Part(double size) {
	solidCube1Part(size);
	glRotated(90, 1, 0, 0);
	glTranslated(0, -size, -size);
	solidCube1Part(size);
}
void customSolidCube(double size) {
	glPushMatrix(); {
		glTranslated(0, -size/2, 0);
		solidCube2Part(size/2);
		glRotated(90, 1, 0, 0);
		glTranslated(0, -size/2, -size/2);
		solidCube2Part(size/2);
	}glPopMatrix();

	glPushMatrix(); {
		glRotated(90, 0, 0, 1);
		glTranslated(0, size/2, 0);
		solidCube1Part(size/2);
	}glPopMatrix();

	glPushMatrix(); {
		glRotated(90, 0, 0, 1);
		glTranslated(0, -size/2, 0);
		solidCube1Part(size/2);
	}glPopMatrix();
}
/******************************** /End Make Custom Cube *********************************/

/********************************************************************************/

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
									//gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

	V to = loc + dir;
	gluLookAt(loc.x, loc.y, loc.z, to.x, to.y, to.z, perp.x, perp.y, perp.z);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/

	//gridAndAxis();

	/****************************
	/ Add your objects from here
	****************************/
	glPushMatrix(); {
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wallImg);
		customSolidCube(30);
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glFlush();
	glutSwapBuffers();
}

void animate() {
	//codes for any changes in Models, Camera

	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.

	//codes for any changes in Models

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

	cameraAngleDelta = .001;

	cameraRadius = 150;
	cameraHeight = 50;


	loc = _L, dir = _D, perp = _P;
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
	gluPerspective()  set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}

void keyboardListener(unsigned char key, int x, int y) {
	switch (key) {

	case 'w':case 'W':
		loc = loc + speed*dir;
		break;

	case 'a':case 'A':
		loc = loc + speed*((perp*dir).unit());
		break;

	case 's':case 'S':
		loc = loc - speed*dir;
		break;

	case 'd':case 'D':
		loc = loc + speed*((dir*perp).unit());
		break;

	case 'q':case 'Q':
		perp = perp.rot(dir, ang_speed);
		break;

	case 'e':case 'E':
		perp = perp.rot(-dir, ang_speed);
		break;


	default:
		break;
	}
}

void specialKeyListener(int key, int x, int y) {
	V p;

	switch (key) {
	case GLUT_KEY_UP:
		p = (dir*perp).unit();
		dir = dir.rot(p, ang_speed);
		perp = perp.rot(p, ang_speed);
		break;
	case GLUT_KEY_DOWN:
		p = (perp*dir).unit();
		dir = dir.rot(p, ang_speed);
		perp = perp.rot(p, ang_speed);
		break;

	case GLUT_KEY_LEFT:
		dir = dir.rot(-perp, ang_speed);
		break;
	case GLUT_KEY_RIGHT:
		dir = dir.rot(perp, ang_speed);
		break;

	case GLUT_KEY_PAGE_UP:
		loc = loc + speed*perp;
		break;
	case GLUT_KEY_PAGE_DOWN:
		loc = loc - speed*perp;
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		loc = _L, dir = _D, perp = _P;
		break;
	case GLUT_KEY_END:
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y) {	//x, y is the x-y of the screen (2D)
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		// 2 times?? in ONE click? -- solution is checking DOWN or UP

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

	printf("Camera Control\n");
	printf("_____________\n");
	printf("Roll: UP and DOWN arrow\n");
	printf("Pitch: Q and E\n");
	printf("Yaw: LEFT and RIGHT arrow\n");
	printf("Up-Down: PAGEUP and PAGEDOWN\n");
	printf("Left-Right: A and D\n");
	printf("Zoom in-out: W and S\n");
	printf("Reset Camera: HOME\n");

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
