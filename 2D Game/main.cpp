#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <math.h>
#include<stdio.h>


static float	tx	=  0.0;
static float	ty	=  0.0;

float speed=0.005;

float vehicleX = 0.0, vehicleY = -16.0;

int SCORE=0;

double moveally=-25.0;
double moveovy1=25.0,moveovy2=55.0;

double ovehicleX[12];
int curr1=0,curr2=1;

void generate_other_vehiclepos()
{
    for(int i = 0; i < 10; i++)
    {
        if(rand()%3==0)
            ovehicleX[i]=-10.0;
        if(rand()%3==1)
            ovehicleX[i]=0.0;
        if(rand()%3==2)
            ovehicleX[i]=10.0;
    }
}

void drawRoad()
{
    glBegin(GL_QUADS);
        glColor3f(0.5,0.5,0.5);
        glVertex2f(-15.0,25.0);
        glVertex2f(-15.0,-25.0);
        glVertex2f(15.0,-25.0);
        glVertex2f(15.0,25.0);
    glEnd();
}

void drawDivider1()//black patch drawn in middle of road
{
    double strtx=-5.5,strty=40.0;
    for(int i = 1; i <= 10; i++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
            glVertex2f(strtx,moveally+strty);
            glVertex2f(strtx+1,moveally+strty);
            glVertex2f(strtx+1,moveally+strty+5);
            glVertex2f(strtx,moveally+strty+5);
        glEnd();
        strty-=10;
    }
}

void drawDivider2()//black patch drawn in middle of road
{
    double strtx=4.5,strty=40.0;
    for(int i = 1; i <= 10; i++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
            glVertex2f(strtx,moveally+strty);
            glVertex2f(strtx+1,moveally+strty);
            glVertex2f(strtx+1,moveally+strty+5);
            glVertex2f(strtx,moveally+strty+5);
        glEnd();
        strty-=10;
    }
}

void drawTreesleft()
{
    double strtx=-20.0,strty=50.0;
    for(int i = 1; i <= 12; i++)
    {
        glColor3f(22.0/255, 186.0/255, 38/255.0);
        glBegin(GL_POLYGON);
            glVertex2f(strtx,moveally+strty);
            glVertex2f(strtx-1,moveally+strty-2);
            glVertex2f(strtx-2,moveally+strty-2);
            glVertex2f(strtx-2,moveally+strty-4);
            glVertex2f(strtx-3,moveally+strty-5);
            glVertex2f(strtx-2,moveally+strty-7);
            glVertex2f(strtx-2,moveally+strty-8);
            glVertex2f(strtx-1,moveally+strty-8);
            glVertex2f(strtx,moveally+strty-10);
            glVertex2f(strtx+1,moveally+strty-8);
            glVertex2f(strtx+2,moveally+strty-8);
            glVertex2f(strtx+2,moveally+strty-6);
            glVertex2f(strtx+3,moveally+strty-5);
            glVertex2f(strtx+2,moveally+strty-4);
            glVertex2f(strtx+2,moveally+strty-2);
            glVertex2f(strtx+1,moveally+strty-2);
        glEnd();
        strty-=10;
    }
}

void drawTreesRight()
{
    double strtx=20.0,strty=50.0;
    for(int i = 1; i <= 10; i++)
    {
        glColor3f(22.0/255, 186.0/255, 38/255.0);
        glBegin(GL_POLYGON);
            glVertex2f(strtx,moveally+strty);
            glVertex2f(strtx-1,moveally+strty-2);
            glVertex2f(strtx-2,moveally+strty-2);
            glVertex2f(strtx-2,moveally+strty-4);
            glVertex2f(strtx-3,moveally+strty-5);
            glVertex2f(strtx-2,moveally+strty-7);
            glVertex2f(strtx-2,moveally+strty-8);
            glVertex2f(strtx-1,moveally+strty-8);
            glVertex2f(strtx,moveally+strty-10);
            glVertex2f(strtx+1,moveally+strty-8);
            glVertex2f(strtx+2,moveally+strty-8);
            glVertex2f(strtx+2,moveally+strty-6);
            glVertex2f(strtx+3,moveally+strty-5);
            glVertex2f(strtx+2,moveally+strty-4);
            glVertex2f(strtx+2,moveally+strty-2);
            glVertex2f(strtx+1,moveally+strty-2);
        glEnd();
        strty-=10;
    }
}

void drawVehicle()//car for racing
{
    glBegin(GL_QUADS);
        glColor3f(1,0,0);//middle body
        glVertex2f(vehicleX - 3, vehicleY + 3);
        glVertex2f(vehicleX - 3, vehicleY - 3);
        glVertex2f(vehicleX + 3, vehicleY - 3);
        glVertex2f(vehicleX + 3, vehicleY + 3);
    glEnd();

    glBegin(GL_QUADS);//up body
        glColor3f(0,1,1);
        glVertex2f(vehicleX - 2, vehicleY + 5);
        glVertex2f(vehicleX - 3, vehicleY + 3);
        glVertex2f(vehicleX + 3, vehicleY + 3);
        glVertex2f(vehicleX + 2, vehicleY + 5);
    glEnd();

    glBegin(GL_QUADS);//down body
        glColor3f(0,1,1);
        glVertex2f(vehicleX - 3, vehicleY - 3);
        glVertex2f(vehicleX - 2, vehicleY - 5);
        glVertex2f(vehicleX + 2, vehicleY - 5);
        glVertex2f(vehicleX + 3, vehicleY - 3);
    glEnd();
 }

void drawOVehicle1()//other cars
{
    glBegin(GL_QUADS);
        glColor3f(0.59,0.33,0.99);//middle body
        glVertex2f(ovehicleX[curr1] - 3, moveovy1 + 3);
        glVertex2f(ovehicleX[curr1] - 3, moveovy1 - 3);
        glVertex2f(ovehicleX[curr1] + 3, moveovy1 - 3);
        glVertex2f(ovehicleX[curr1] + 3, moveovy1 + 3);
    glEnd();
    glBegin(GL_QUADS);//up body
        glColor3f(0.02,0.77,0.45);
        glVertex2f(ovehicleX[curr1] - 2, moveovy1 + 5);
        glVertex2f(ovehicleX[curr1] - 3, moveovy1 + 3);
        glVertex2f(ovehicleX[curr1] + 3, moveovy1 + 3);
        glVertex2f(ovehicleX[curr1] + 2, moveovy1 + 5);
    glEnd();

    glBegin(GL_QUADS);//down body
        glColor3f(0.16,0.02,0.97);
        glVertex2f(ovehicleX[curr1] - 3, moveovy1 - 3);
        glVertex2f(ovehicleX[curr1] - 2, moveovy1 - 5);
        glVertex2f(ovehicleX[curr1] + 2, moveovy1 - 5);
        glVertex2f(ovehicleX[curr1] + 3, moveovy1 - 3);
    glEnd();
}

void drawOVehicle2()//other cars
{
    glBegin(GL_QUADS);
        glColor3f(0.59,0.33,0.99);//middle body
        glVertex2f(ovehicleX[curr2] - 3, moveovy2 + 3);
        glVertex2f(ovehicleX[curr2] - 3, moveovy2 - 3);
        glVertex2f(ovehicleX[curr2] + 3, moveovy2 - 3);
        glVertex2f(ovehicleX[curr2] + 3, moveovy2 + 3);
    glEnd();
    glBegin(GL_QUADS);//up body
        glColor3f(1.,0.77,0.45);
        glVertex2f(ovehicleX[curr2] - 2, moveovy2 + 5);
        glVertex2f(ovehicleX[curr2] - 3, moveovy2 + 3);
        glVertex2f(ovehicleX[curr2] + 3, moveovy2 + 3);
        glVertex2f(ovehicleX[curr2] + 2, moveovy2 + 5);
    glEnd();

    glBegin(GL_QUADS);//down body
        glColor3f(0.96,0.82,0.27);
        glVertex2f(ovehicleX[curr2] - 3, moveovy2 - 3);
        glVertex2f(ovehicleX[curr2] - 2, moveovy2 - 5);
        glVertex2f(ovehicleX[curr2] + 2, moveovy2 - 5);
        glVertex2f(ovehicleX[curr2] + 3, moveovy2 - 3);
    glEnd();
}


void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(speed+0.01<=0.1)
            speed+=0.01;
            break;
        case GLUT_KEY_DOWN:
            if(speed-0.01>0.007)
                speed-=0.01;
            break;
        case GLUT_KEY_LEFT:
            if(vehicleX-10.0>=-15)
                vehicleX -= 10;
            PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
            break;
        case GLUT_KEY_RIGHT:
            if(vehicleX+10.0<=15)
                vehicleX += 10;
            PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
            break;
    }
    glutPostRedisplay();
}

bool collision()
{
    double presX=vehicleX,presY=vehicleY;
    double o1x=ovehicleX[curr1],o1y=moveovy1;
    if(presX==o1x&&(presY>o1y-6&&presY<o1y+6))
        return 1;
    double o2x=ovehicleX[curr2],o2y=moveovy2;
    if(presX==o2x&&(presY>o2y-6&&presY<o2y+6))
        return 1;
    return 0;
}

void init(void)
{
	glClearColor (186.0/255, 120.0/255, 22.0/255, 0.0);
	gluOrtho2D(-25.0, 25.0, -25.0,25.0);
}

double zoom=0.0;

void text()
{
    char text[32];
    text[0]='S';
    text[1]='C';
    text[2]='O';
    text[3]='R';
    text[4]='E';
    text[5]=':';
    text[6]=':';
    int digits=0;
    int strt=7;
    if(SCORE<10)
        strt--;
    int tmp=SCORE;
    while(tmp)
    {
        text[strt--]=(tmp%10)+'0';
        tmp/=10;
    }
    glColor3f(0, 0, 0);
    glRasterPos3f( -25 , 20 , zoom);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void display(void)
{
    if(collision())
    {
        exit(0);
    }
    if(moveally<15)
        moveally+=speed;
    else moveally=-25;
    if(moveovy1>=-25)
        moveovy1-=speed;
    else
    {
        SCORE++;
        curr1++;
        curr1%=12;
        moveovy1=25;
    }
    if(moveovy2>=-55)
        moveovy2-=speed;
    else
    {
        SCORE++;
        curr2++;
        curr2%=12;
        moveovy2=55;
    }
    if(fabs(moveovy1-moveovy2)<20)
    {
        if(moveovy1>moveovy2)
            moveovy1+=20.0;
        else moveovy2+=20.0;
    }
    glutPostRedisplay();

    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    text();
    drawRoad();
    drawDivider1();
    drawDivider2();
    drawTreesleft();
    drawTreesRight();
    drawVehicle();
    drawOVehicle1();
    drawOVehicle2();
    text();
    glPopMatrix();
	glFlush();
}

int main()
{
    PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("MY GAME :: 201414030");
	init();
	generate_other_vehiclepos();
    glutDisplayFunc(display);
    glutSpecialFunc(Specialkey);
	glutMainLoop();
	return 0;
}


