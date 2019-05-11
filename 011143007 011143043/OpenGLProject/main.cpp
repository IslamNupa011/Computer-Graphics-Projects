
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <GL/glu.h>
#include <GLAux.h>
#define cut(x, a, b) min(max(x, a), b)

using namespace std;

typedef vector<double> Vec3;
typedef pair<int, int> pii;

GLuint blockTexture, groundTexture, compassTexture;
struct Block{
    double x, y, z;
    double L, W, H;
    Block(double x, double y, double z, double L, double W, double H){
        this->x = x, this->y = y, this->z = z;
        this->L = L, this->W = W, this->H = H;
    }

    Vec3 center(){
        Vec3 c(3);
        c[0] = x + L/2;
        c[1] = y + W/2;
        c[2] = z + H/2;
        return c;
    }

    void draw(){
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(1, 1, 1);
        //glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, blockTexture);
        glBegin(GL_QUADS);
        //Front

        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1); glVertex3f(L, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(L, W, 0);
        glTexCoord2f(1, 0); glVertex3f(0, W, 0);
        //Left
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(0, 1); glVertex3f(0, 0, H);
        glTexCoord2f(1, 1); glVertex3f(0, W, H);
        glTexCoord2f(1, 0); glVertex3f(0, W, 0);
        //Bottom
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(L, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(L, 0, H);
        glTexCoord2f(0, 1); glVertex3f(0, 0, H);
        //Back
        glTexCoord2f(0, 0); glVertex3f(0, 0, H);
        glTexCoord2f(0, 1); glVertex3f(L, 0, H);
        glTexCoord2f(1, 1); glVertex3f(L, W, H);
        glTexCoord2f(1, 0); glVertex3f(0, W, H);
        //Right
        glTexCoord2f(0, 0); glVertex3f(L, 0, 0);
        glTexCoord2f(0, 1); glVertex3f(L, 0, H);
        glTexCoord2f(1, 1); glVertex3f(L, W, H);
        glTexCoord2f(1, 0); glVertex3f(L, W, 0);
        //Top
        glTexCoord2f(0, 0); glVertex3f(0, W, 0);
        glTexCoord2f(1, 0); glVertex3f(L, W, 0);
        glTexCoord2f(1, 1); glVertex3f(L, W, H);
        glTexCoord2f(0, 1); glVertex3f(0, W, H);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        //glEnable(GL_LIGHTING);
        glPopMatrix();
    }
};



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
Vec3 zero = {0, 0, 0};
Vec3 player = {0, 0, 0};
Vec3 goal = {0, 0, 0};
Vec3 cam = {0, 0, 0};
Vec3 eye = {0, 0, 1};
Vec3 L = {0, 0, 1};
Vec3 R = {1, 0, 0};
Vec3 U = {0, 1, 0};
Vec3 up = {0, 1, 0};
int startTime, endTime;
vector<Vec3> path;
set<pii> covered;
double xAngle = 0, yAngle = 0;
double Len = 5;
double depth = 0;
int mode = 3, pathFinding = 0;

int dx[] = {+1, 0, 0, -1};
int dy[] = {0, +1, -1, 0};
int di[] = {2, 0, 3, 1};
vector<Block> blocks;
string buffer;

void drawCompass()
{
    double r = .1, cx = 0.8, cy = 0.8, PI = acos(-1);
    double angle, radian, x, y, xcos, ysin, tx, ty;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, compassTexture);
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(yAngle, 0, 0, 1);
    glBegin(GL_POLYGON);

    for (angle=0.0; angle<360.0; angle+=.2)
    {
        radian = angle * (PI/180.0f);
        xcos = (double)cos(radian);
        ysin = (double)sin(radian);
        x = xcos * r;
        y = ysin * r;
        tx = xcos * 0.5 + 0.5;
        ty = ysin * 0.5 + 0.5;
        glTexCoord2f(tx, ty);
        glVertex2f(x, y);;
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

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

//	//+Z axis
//	glColor3f(0, 0, 1);//blue
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 0, 1000);
//
//	//-Z axis
//	glColor3f(0, 1, 1);//cyan
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 0, -1000);
	glEnd();
}

void drawGrid(){
    int i;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
	glColor3f(.5, .5, .5);//gray
	glScalef(.2, .2, .2);
	glBegin(GL_QUADS);
	for (i = -200; i <= 200; i++){
		for(int j = -200; j <= 200; j++){
            double h = 10;
            double x = i * h, y = j * h;
            glTexCoord2f(0, 0); glVertex3f(x, y, 0);
            glTexCoord2f(1, 0); glVertex3f(x + h, y, 0);
            glTexCoord2f(1, 1); glVertex3f(x + h, y + h, 0);
            glTexCoord2f(0, 1); glVertex3f(x, y + h, 0);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void camera(){
    xAngle = cut(xAngle, -90.0, 90.0);
    if(yAngle > 360) yAngle = yAngle - 360;
    if(yAngle <   0) yAngle = yAngle + 360;
    glMatrixMode(GL_MODELVIEW);
	glRotatef(xAngle, 1, 0, 0);
	glRotatef(yAngle, 0, 0, 1);
	glTranslatef(cam[0], cam[1], cam[2]);

}

void getLRU(){
    GLfloat matrix[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
    L[0] =  matrix[  2 ]; // x
    L[1] =  matrix[  6 ]; // y
    L[2] =  matrix[ 10 ];
    R[0] =  matrix[ 0 ];
    R[1] =  matrix[ 4 ];
    R[2] =  matrix[ 8 ];
    U[0] =  matrix[ 1 ];
    U[1] =  matrix[ 5 ];
    U[2] =  matrix[ 9 ];
    if(mode == 1){
        swap(L, U);

    }
}

void drawCircle(Vec3 pos, double radius, Vec3 color){
    double r = radius, PI = acos(-1), n = 100;
    glPushMatrix();
    glTranslatef(-pos[0], -pos[1], -pos[2]);
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < n; i++){
        double now = 2.0*i*PI*(1/n);
        double next = 2.0*(i+1)*PI*(1/n);
        glVertex3f(0, 0, 0);
        glVertex3f(r * cos(now), r * sin(now), 0);
        glVertex3f(r * cos(next), r * sin(next), 0);
    }
    glEnd();
    glPopMatrix();
}

void drawSphere(Vec3 pos, double radius, Vec3 color){
    glPushMatrix();
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(-pos[0], -pos[1], -pos[2]);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();
}

void drawPlayer(){
    drawCircle(add(player, {0, 0, -player[2]-2}), 1, {1, 0, 0});
}

void drawGoalCircle(){
    drawCircle(add(goal, {0, 0, -2}), 1, {0, 1, 0});
}

void drawGoalSphere(){
    drawSphere(add(goal, {0, 0, -3}), 1, {0, 1, 0});
}

void drawPath(){
    Vec3 height = {0, 0, -2};
    if(mode == 2){
        height = {0, 0, -.01};
    }
    for(int i = 0; i < path.size(); i++){
        drawCircle(add(sub(zero, path[i]), height), 1, {0, .6, 1});
    }
}

void drawString(string s, double x, double y){
    //glPushMatrix();
    //gluOrtho2D( 0, 600, 0, 600 );
    //printf("%s\n", s.c_str());
    glRasterPos2f(x, y);
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int i = 0; i < s.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    //glPopMatrix();
}

string intToString(int x){
    char text[100];
    sprintf(text, "%d", x);
    return string(text);
}

void display()
{
	//codes for Models, Camera

	//clear the display
	//color black
	Vec3 background = {0,159,255};
	glClearColor(background[0]/255.0, background[1]/255.0, background[2]/255.0, 1.0);

	//clear buffers to preset values
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/***************************
	/ set-up camera (view) here
	****************************/

	//load the correct matrix -- MODEL-VIEW matrix
	//specify which matrix is the current matrix

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    if(mode == 1 ){
        yAngle = 0;
    }
    if(mode == 3){
        drawString("Enter map name: " + buffer, -.9, .9);
    }
    else if(mode == 4){
        int timeTaken = (endTime - startTime) / 10;
        drawString("Time taken: " + intToString(timeTaken/100) + "." + intToString(timeTaken%100) + " seconds", .4, .9);
    }
    else if(mode == 1 || mode == 2){
        drawCompass();
        if(pathFinding == 1){
            drawString("Path Finding: ON", -.9, .9);
        }
        gluPerspective(70, 1, 0.1, 10000.0);

        cam = player;
        gluLookAt(0,0,0,  0,1,0,  0,0,1);
        if(mode == 2){
            cam[2] = -3; //Fix to ground
        }
        else if(mode == 1){
            xAngle = 90;
            yAngle = -90;
            cam[2] = -100 + depth;
        }
        camera();
        getLRU();
        //drawAxis();
        drawGrid();
        if(mode == 1){
            glScalef(1, 1, 1.0/(Len*100));
            drawPlayer();
            drawGoalCircle();
            drawPath();
        }
        else if(mode == 2){
            drawGoalSphere();
            drawPath();
        }
        for(int i = 0; i < blocks.size(); i++){
            blocks[i].draw();
        }
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

double dist2D(Vec3 a, Vec3 b){
    double dx = a[0] - b[0];
    double dy = a[1] - b[1];
    return sqrt(dx*dx+dy*dy);
}

void setMode(int m){
    mode = m;
    buffer = "";
    xAngle = yAngle = 0;
}

bool eq(double a, double b){
    //printf("%.3f %.3f\n", a, b);
    double EPS = 0.001;
    if(fabs(a - b) < EPS) return true;
    return false;
}

bool collision(Vec3 pos){
    //printf("here %.3f %.3f %.3f\n", pos[0], pos[1], pos[2]);
    for(int i = 0; i < blocks.size(); i++){
//        Vec3 center = blocks[i].center();
//        double d = dist2D(pos, center);
//        if(i == 0) printf("%.3f | %.3f %.3f %.3f | %.3f %.3f %.3f\n", d, center[0], center[1], center[2], cam[0], cam[1], cam[2]);
//        if(d < Len / 2) return true;
        if(eq(floor(blocks[i].x / Len), floor(-pos[0] / Len))
          && eq(floor(blocks[i].y / Len), floor(-pos[1] / Len))) return true;
    }
    if(dist2D(pos, goal) < 1){
        endTime = glutGet(GLUT_ELAPSED_TIME);
        setMode(4);
    }
    return false;
}

void loadTextures(){
    AUX_RGBImageRec* TextureImage;
    glGenTextures(1, &blockTexture);
    if (TextureImage = auxDIBImageLoad("wall.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, blockTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	glGenTextures(1, &groundTexture);
	if (TextureImage = auxDIBImageLoad("grass.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, groundTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
	glGenTextures(1, &compassTexture);
	if (TextureImage = auxDIBImageLoad("compass.bmp"))
	{
		glBindTexture(GL_TEXTURE_2D, compassTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	}
}

void loadMap(const char filename[]){
    FILE *f = fopen(filename, "r");
    int row = 0, col = 0, L = 5, W = 5, H = 5;
    L = W = H = Len;
    char ch;
    blocks.clear();
    covered.clear();
    while(fscanf(f, "%c", &ch) != EOF){
        if(ch == '\n'){
            row++, col = 0;
        }
        else if(ch == '*'){
            Block b(row * L, col * W, 0, L, W, H * 2);
            blocks.push_back(b);
            covered.insert(pii(row, col));
            col++;
        }
        else if(ch == 'S'){
            player = sub(zero, {row * L + L/2, col * W + W/2, 0});
            col++;
        }
        else if(ch == 'E'){
            goal = sub(zero, {row * L + L/2, col * W + W/2, 0});
            col++;
        }
        else{
            col++;
        }

    }
    startTime = glutGet(GLUT_ELAPSED_TIME);
}



void findPath(){
    typedef pair<int, int> pii ;
    int dx[] = {0, 0, +1, -1};
    int dy[] = {-1, +1, 0, 0};
    map<pii, pii> parent;
    queue<pii> que;
    pii start = {floor(-player[0]/Len), floor(-player[1]/Len)};
    pii dest  = {floor(-goal[0]/Len), floor(-goal[1]/Len)};
    que.push(start);
    parent[start] = start;
    //printf("<<%d %d\n", start.first, start.second);
    //printf("<<%d %d\n", dest.first, dest.second);
//    for(auto x: covered){
//        printf("%d %d\n", x.first, x.second);
//    }
    while(!que.empty() && !parent.count(dest)){
        pii u = que.front();
        que.pop();
        //printf("-->%d %d\n", u.first, u.second);
        for(int i = 0; i < 4; i++){
            pii v = pii(u.first + dx[i], u.second + dy[i]);
            if(!parent.count(v) && !covered.count(v)){
                parent[v] = u;
                que.push(v);
            }
        }
    }
    path.clear();
    for(pii u = parent[dest]; u != start; u = parent[u]){
        //printf("--<>%d %d\n", u.first, u.second);
        path.push_back({u.first * Len + Len/2, u.second * Len + Len/2, 0});
        //printf("--<>%.3f %.3f\n", u.first * Len + Len/2, u.second * Len + Len/2);
    }
    reverse(path.begin(), path.end());
}

void keyboardListener(unsigned char key, int x, int y)
{
    if(mode == 3){
        if(key == 13){
            string filename = buffer + ".txt";
            loadMap(filename.c_str());
            buffer.clear();
            setMode(1);
        }
        else{
            buffer += key;
        }
    }
    else{
        Vec3 newPos = player;
        if(key == 's') {
        newPos = add(player, L);
        }
        if(key == 'w') {
            newPos = sub(player, L);
        }
        if(key == 'a'){
            newPos = add(player, R);
        }
        if(key == 'd'){
            newPos = sub(player, R);
        }
        if(key == '1'){
            setMode(1);
        }
        if(key == '2'){
            setMode(2);
        }
        if(key == '3'){
            setMode(3);
        }
        if(key == '9'){
            pathFinding ^= 1;
        }
        if(key == '+'){
            depth++;
        }
        if(key == '-'){
            depth--;
        }
        if(collision(newPos) == false){
            player = newPos;
        }
    }

}

void specialKeyListener(int key, int x, int y)
{
    hAngle = 0;
    vAngle = 0;
    double ang = .05;
	if (key == GLUT_KEY_UP)
	{
        xAngle--;
	}
	else if (key == GLUT_KEY_DOWN)
	{
        xAngle++;
	}
	else if (key == GLUT_KEY_LEFT)
	{
	    yAngle--;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
	    yAngle++;
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

int px, py, first = true;
void mouseListener(int x, int y){
    if(first){
        //Ignore
    }
    else{
        double factor = .5;
        int xi = x - px, yi = y - py;
        xAngle += yi * factor;
        yAngle += xi * factor;
    }
    px = x, py = y;
    first = false;
}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0001;

	//codes for any changes in Models

	//this will call the display AGAIN
	path.clear();
	if(pathFinding == 1) findPath();
	glutPostRedisplay();

}


void init()
{
	//codes for initialization
	//setMode(4);
    loadMap("maze.txt");
    loadTextures();
	//angle in radian
	//cameraAngle = 0;
	Rspeed = 3.0;

	vAngle = 0.0;
    hAngle = 0.0;
    angleSpeed = 0.05;

	//clear the screen
	glClearColor(0, 0, 0, 0);
    setMode(1);


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

	glutCreateWindow("Maze Runner");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);

	glutSpecialFunc(specialKeyListener);
	glutKeyboardFunc(keyboardListener);
	glutPassiveMotionFunc(mouseListener);

	//what you want to do in the idle time (when no drawing is occuring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();

	return 0;
}

