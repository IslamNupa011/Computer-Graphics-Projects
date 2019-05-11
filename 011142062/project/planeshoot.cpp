#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <bits/stdc++.h>
#include <windows.h>
#include <glut.h>
#include <conio.h>

using namespace std;
//stop and show score
bool stop = false;

//bullet
float bullet_x;
float bullet_y;
float bullet_speed = 0.08;
float bullet_rad = .3;
int score=0;
struct playerProperties
{
    float xPosition;
    float yPosition;
    float xSpeed;
    float ySpeed;
}player;
typedef struct Vect {
	float x;
	float y;
}Vector2D;

typedef struct s {
	Vector2D pos;
}Star;

Star stars[10000];
int n_stars = 150;

typedef struct Enemy {
	char color;
	int state;
	Vector2D position;
	float speed;
}Enemy;
Enemy enemys[10000];
int n_enemys = 100;

typedef struct bullet {
	Vector2D position;
	Vector2D speed;
	int blasted;
}BulletShell;

BulletShell bulletShell[100000];
int n_bullets = 0;

void Player(double L)
{

        glBegin(GL_TRIANGLES);
            glVertex2f(L/3, -L/3+0.2);
            glVertex2f(-L/3, -L/3+0.2);
            glVertex2f(0, ((1.414*L/3+0.2)));
            glColor3f(0.2,0.8,0.8);
            glVertex2f(L/3, L/3);
            glVertex2f(-L/3, L/3);
            glVertex2f(0, (-1.414*L/3+2));





        glEnd();

}

void starCreator() {


	int i;
	for (i=0; i<n_stars; i++)
	{
		Star temp;
		temp.pos.x = (-70 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(70+70))));
		temp.pos.y = (-90.9 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.9+90.9))));

		stars[i] = temp;
	}
}
void drawPlayer(){

    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(player.xPosition,player.yPosition, 0 );
    Player(8);
    glPopMatrix();


    //glFlush();
}

//Draw Bullet
void drawBullet(float rad) {

	glBegin(GL_QUADS);
    {
        glVertex3f(-rad,-rad,0);
        glVertex3f(rad,-rad,0);
        glVertex3f(rad,rad,0);
        glVertex3f(-rad,rad,0);
    }
    glEnd();
}

void bulletCreator(float p_x, float p_y) {

	BulletShell bullet;
	bullet.position.x = p_x;
	bullet.position.y = p_y;
	bullet.speed.x = bullet_speed;
	bullet.speed.y = bullet_speed;
	bullet.blasted = 0;

	bulletShell[n_bullets++] = bullet;
}


void drawEnemy() {

	Player(6);
}

void enemyCreator(int value) {

	if (stop == false)
	{
		Enemy enem;
		enem.state = 1;
		enem.color = rand()%2;
		enem.speed = 0.004 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.004)));
		enem.position.y = 80;
		enem.position.x = (-70.85 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.85+90.85))));

		enemys[n_enemys++] = enem;
	}
	glutTimerFunc(2000, enemyCreator, 1);
}
void scorePrint()
{
    cout << "GAME OVER" <<endl;
    cout << "FINAL SCORE: "<<score<<endl;
    stop=true;
    exit(0);
}

void updatingScore()
{
    cout<<"Score:  "<<score<<endl;
    // cout<<"\b \b "<<endl;
}
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

    /*glColor3f(0,1,0);
    glBegin(GL_LINES);
    {
        glVertex3f(-100,0,0);
        glVertex3f(100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0,100,0);
    }
    glEnd(); */
    for (int a=0; a<n_stars; a++)
	{
		glPushMatrix();
		glTranslatef(stars[a].pos.x, stars[a].pos.y,0);
		glColor3f(1.0, 1.0, 1.0);
		drawBullet(0.06);
		glPopMatrix();
	}

    starCreator();
    drawPlayer();

    // Draw BulletShell.
    int a;
	for (a=0; a<n_bullets; a++)
	{
		if (bulletShell[a].blasted == 0)
		{
			glPushMatrix();
			glTranslatef(bulletShell[a].position.x, bulletShell[a].position.y, 0);
			glColor3f(1, 1, 1);
			drawBullet(bullet_rad);
			glPopMatrix();
		}
	}

    //moving the Bullet.



    //enemy draw

    for (int j=0; j<n_enemys; j++)
    {
        if (enemys[j].state == 1)
        {
            glPushMatrix();

            if (enemys[j].color == 0)
                glColor3f(1.0, 0.0, 0.0);
            if (enemys[j].color == 1)
                glColor3f(1.0, 1.0, 1.0);
            glTranslatef(enemys[j].position.x, enemys[j].position.y, 0);
            drawEnemy();
            glPopMatrix();
        }
    }


        //out of the screen
        for (int m=0; m<n_enemys; m++)
        {
            if (enemys[m].state == 1 && enemys[m].position.y < -70)
            {
                if(enemys[m].color==1){
                    score += 1;
                    updatingScore();
                }
                if(enemys[m].color==0){
                    scorePrint();
                }
                enemys[m].state = 0 ;
            }
        }


        for (int e=0; e<n_bullets; e++)
        {
			if (bulletShell[e].blasted == 0)
			{
				for (int f=0; f<n_enemys; f++)
				{
					if (enemys[f].state == 1  && enemys[f].position.y > -80)
					{
						if (((bulletShell[e].position.x + bullet_rad >= enemys[f].position.x - 3 && bulletShell[e].position.x + bullet_rad <= enemys[f].position.x + 3) || (bulletShell[e].position.x - bullet_rad <= enemys[f].position.x + 3 && bulletShell[e].position.x - bullet_rad >= enemys[f].position.x - 3)) && (bulletShell[e].position.y + bullet_rad >=  enemys[f].position.y - 3 && bulletShell[e].position.y + bullet_rad <= enemys[f].position.y + 3))
						{
							enemys[f].state = 0;
							bulletShell[e].blasted = 1;
							enemys[f].position.x= -100;
							enemys[f].position.y= -100;
							if(enemys[f].color == 0)
                            {
                                score +=3;
                            }
                            else
                                score = score -1;


							updatingScore();

						}
					}
				}
			}
        }


    glutSwapBuffers();
	//glutPostRedisplay();
}

void animate()
{
	//codes for any changes in Models, Camera

	//camera will rotate at 0.0001 radians per frame.
	//cameraAngle += 0.0001;

	//codes for any changes in Models
	int i;
    for (i=0; i<n_enemys; i++){
        enemys[i].position.y -= enemys[i].speed;
    }
    int b;
	for (b=0; b<n_bullets; b++)
    {
        if (bulletShell[b].blasted == 0)
        {
            bulletShell[b].position.y += bulletShell[b].speed.y;
        }
    }

	//this will call the display AGAIN
	glutPostRedisplay();

}

void keyboardListener(unsigned char key, int x,int y)
{
    player.xSpeed=0.0;
    player.ySpeed=0.0;
    if(key=='w'){
        player.ySpeed +=1.0;
        player.xPosition +=player.xSpeed;
        player.yPosition +=player.ySpeed;
    }
    if(key=='s'){
        player.ySpeed -=1.0;
        player.xPosition +=player.xSpeed;
        player.yPosition +=player.ySpeed;
    }
    if(key=='a'){
        player.xSpeed -=1.0;
        player.xPosition +=player.xSpeed;
        player.yPosition +=player.ySpeed;

    }
    if(key=='d'){
        player.xSpeed +=1.0;
        player.xPosition +=player.xSpeed;
        player.yPosition +=player.ySpeed;

    }
    if(key == 'p'){
        bulletCreator(player.xPosition, player.yPosition);
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
	gluPerspective() ? set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70, 1, 0.1, 10000.0);

}

int main(int argc, char **argv)
{
    player.xPosition = 0;
    player.yPosition = 0;
    player.xSpeed = 0.0;
    player.ySpeed = 0.0;
	//initialize the GLUT library
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(200, 1);


//    glutSpecialFunc(specialKeyListener);
//    glutMouseFunc(mouseListener);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("spaceshooting");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);

	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);
	glutTimerFunc(200, enemyCreator, 1);

	//The main loop of OpenGL
	glutMainLoop();


	return 0;
}
