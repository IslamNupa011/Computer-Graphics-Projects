
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include <vector>
#include <string>
#define cut(x, a, b) min(max(x, a), b)

using namespace std;

struct Block{
    double x, y, z;
    double L, W, H;
    Block(double x, double y, double z, double L, double W, double H){
        this->x = x, this->y = y, this->z = z;
        this->L = L, this->W = W, this->H = H;
    }

    void draw(){
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(1, 0, 0);
        glBegin(GL_QUADS);
        //Front
        glVertex3f(0, 0, 0);
        glVertex3f(L, 0, 0);
        glVertex3f(L, W, 0);
        glVertex3f(0, W, 0);
        //Left
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, H);
        glVertex3f(0, W, H);
        glVertex3f(0, W, 0);
        //Bottom
        glVertex3f(0, 0, 0);
        glVertex3f(L, 0, 0);
        glVertex3f(L, 0, H);
        glVertex3f(0, 0, H);
        //Back
        glVertex3f(0, 0, H);
        glVertex3f(L, 0, H);
        glVertex3f(L, W, H);
        glVertex3f(0, W, H);
        //Right
        glVertex3f(L, 0, 0);
        glVertex3f(L, 0, H);
        glVertex3f(L, W, H);
        glVertex3f(L, W, 0);
        //Top
        glVertex3f(0, W, 0);
        glVertex3f(L, W, 0);
        glVertex3f(L, W, H);
        glVertex3f(0, W, H);
        glEnd();
        glPopMatrix();
    }
};

typedef vector<double> Vec3;


Vec3 add(Vec3 a, Vec3 b){
    Vec3 c(3);
    for(int i = 0 ; i < 3; i++){
        c[i] = a[i] + b[i];
    }
    return c;
}


Vec3 sub(Vec3 a, Vec3 b){
    Vec3 c(3);
    for(int i = 0 ; i < 3; i++){
        c[i] = a[i] - b[i];
    }
    return c;
}

Vec3 rot(Vec3 point, Vec3 axis, Vec3 axisPoint, double angle){
    double x = point[0], y = point[1], z = point[2];
    double a = axisPoint[0], b = axisPoint[1], c = axisPoint[2];
    double u = axis[0], v = axis[1], w = axis[2];
    Vec3 rotatedPoint(3);
    rotatedPoint[0] = (a*(v*v+w*w)-u*(b*v+c*w-u*x-v*y-w*z))*(1-cos(angle))+x*cos(angle)+(-c*v+b*w-w*y+v*z)*sin(angle);
    rotatedPoint[1] = (b*(u*u+w*w)-v*(a*u+c*w-u*x-v*y-w*z))*(1-cos(angle))+y*cos(angle)+(+c*u-a*w-w*x-u*z)*sin(angle);
    rotatedPoint[2] = (c*(u*u+v*v)-w*(a*u+b*v-u*x-v*y-w*z))*(1-cos(angle))+z*cos(angle)+(-b*u+a*v-v*x+u*y)*sin(angle);
    return rotatedPoint;
}

Vec3 normalize(Vec3 a){
    Vec3 b = a;
    double xyz = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
    b[0] /= xyz, b[1] /= xyz, b[2] /= xyz;
    return b;
}

Vec3 cross(Vec3 v1, Vec3 v2){
    double x = v1[0], y = v1[1], z = v1[2];
    double a = v2[0], b = v2[1], c = v2[2];
    Vec3 res(3);
    res[0] = b*z-c*y;
    res[1] = c*x-a*z;
    res[2] = a*y-b*x;
    return res;
}

//double cameraAngle;
double  Rspeed, vAngle, hAngle, angleSpeed;
double scale = 1;
Vec3 cam = {0, 0, 0};
Vec3 eye = {0, 0, 1};
Vec3 L = {0, 0, 1};
Vec3 R = {1, 0, 0};
Vec3 U = {0, 1, 0};
Vec3 up = {0, 1, 0};
double xAngle = 0, yAngle = 0;

int dx[] = {+1, 0, 0, -1};
int dy[] = {0, +1, -1, 0};
int di[] = {2, 0, 3, 1};
vector<Block> blocks;

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

void camera(){
    yAngle = cut(yAngle, -90.0, 90.0);
    if(xAngle > 360) xAngle = xAngle - 360;
    if(xAngle <   0) xAngle = xAngle + 360;
    glRotatef(-xAngle, U[0], U[1], U[2]);
    glRotatef(-yAngle, R[0], R[1], R[2]);
    glTranslatef(-cam[0], -cam[1], -cam[2]);
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
    {
//        double x = sqrt(R*R+1);
//        double y = atan(1.0/R);
//
//        double a = x*cos(vAngle+y)*cos(hAngle)-R*cos(vAngle)*cos(hAngle);
//        double b = x*cos(vAngle+y)*sin(hAngle)-R*cos(vAngle)*sin(hAngle);
//        double c = x*sin(vAngle+y)-R*sin(vAngle);
//
//        cx = R*cos(vAngle)*cos(hAngle), cy = R*cos(vAngle)*sin(hAngle), cz = R*sin(vAngle);
        //lx = 0, ly = 0, lz = 0;
        //lx = R*cos(hAngle), ly=R*cos(vAngle);

//        double lxyz = sqrt(lx * lx + ly * ly + lz * lz);
//        lx = lx / lxyz, ly = ly / lxyz, lz = lz / lxyz;
//        ux = -lx * ly, uy = -(lz * lz) - (lx * lx), uz = -lz * ly;
//        printf("%.3f %.3f %.3f\n", lx, ly, lz);
        L = normalize(sub(eye, cam));
        R = cross(L, up);
        U = cross(R, L);
        gluLookAt( cam[0], cam[1], cam[2], eye[0], eye[1], eye[2], U[0],U[1],U[2]);
    }


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);

	/**************************************************
	/ Grid and axes Lines(You can remove them if you want)
	***************************************************/

	// draw the three major AXES
    //camera();
	drawAxis();


    //camera();
	//some grid lines along the field
	drawGrid();

    glScalef(scale, scale, scale);

    for(int i = 0; i < blocks.size(); i++){
        blocks[i].draw();
    }
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}



void keyboardListener(unsigned char key, int x, int y)
{
    if(key == 'w') {
        cam = add(cam, L);
        eye = add(eye, L);
    }
    if(key == 's') {
        cam = sub(cam, L);
        eye = sub(eye, L);
    }
    scale = cut(scale, 1.0, 4.0);
}

void specialKeyListener(int key, int x, int y)
{
    hAngle = 0;
    vAngle = 0;
    double ang = .05;
	if (key == GLUT_KEY_UP)
	{
	    eye = rot(eye, R, cam, -ang);
		vAngle= -angleSpeed;
	}
	else if (key == GLUT_KEY_DOWN)
	{
	    eye = rot(eye, R, cam, +ang);
	    yAngle--;
		vAngle= +angleSpeed;
	}
	else if (key == GLUT_KEY_LEFT)
	{
	    eye = rot(eye, U, cam, -ang);
		xAngle++;
		hAngle = +angleSpeed;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
	    eye = rot(eye, U, cam, +ang);
		xAngle--;
		hAngle= -angleSpeed;
	}
    //Y-axis rotation Left-Right
//    lx =  lx * cos(hAngle) + lz * sin(hAngle);
//    ly =  ly;
//    lz = -lx * sin(hAngle) + lz * cos(hAngle);
//
//    //X-axis rotation Up-Down
//    lx = lx;
//    ly = ly * cos(vAngle) - lz * sin(vAngle);
//    lz = ly * sin(vAngle) + lz * cos(vAngle);
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

void loadMap(char filename[]){
    FILE *f = fopen(filename, "r");
    int row = 0, col = 0, L = 5, W = 5, H = 5;
    L = W = H = 5;
    char ch;
    blocks.clear();
    while(fscanf(f, "%c", &ch) != EOF){
        if(ch == '\n'){
            row++, col = 0;
        }
        else if(ch == '*'){
            printf("%d %d\n", row, col);
            Block b(row * L, 0, col * W, L, W, H);
            blocks.push_back(b);
            col++;
        }
        else{
            col++;
        }

    }
}

void init()
{
	//codes for initialization
    loadMap("map1.txt");
	//angle in radian
	//cameraAngle = 0;
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

