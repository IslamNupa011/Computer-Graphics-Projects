#include<stdio.h>
#include<glut.h>
#include <gl.h>
#include <stdlib.h>


float SPEED =10.0;
float i=0.0;
float m=0.0;

int day=1;


void draw_pixel(GLint cx, GLint cy)
{

    glBegin(GL_POINTS);
    glVertex2i(cx,cy);
    glEnd();
}

void plotpixels(GLint h,GLint k, GLint x,GLint y)
{
    draw_pixel(x+h,y+k);
    draw_pixel(-x+h,y+k);
    draw_pixel(x+h,-y+k);
    draw_pixel(-x+h,-y+k);
    draw_pixel(y+h,x+k);
    draw_pixel(-y+h,x+k);
    draw_pixel(y+h,-x+k);
    draw_pixel(-y+h,-x+k);
}

void draw_circle(GLint h, GLint k, GLint r)
{
    GLint d=1-r, x=0, y=r;
    while(y>x)
    {
        plotpixels(h,k,x,y);
        if(d<0) d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        ++x;
    }
    plotpixels(h,k,x,y);
}

void draw_object()
{
    int l;
    if(day==1)
    {
//sky
        glColor3f(0.0,0.9,0.9);
        glBegin(GL_POLYGON);
        glVertex2f(0,450);
        glVertex2f(0,700);
        glVertex2f(1100,700);
        glVertex2f(1100,450);
        glEnd();

//sun

        for(l=0; l<=35; l++)
        {
            glColor3f(1.0,0.9,0.0);
            draw_circle(100,625,l);

        }
        for(l=0; l<=10; l++)
        {
            glColor3f(1.0,0.84,0.0);
            draw_circle(100,625,l+30);
        }
        for(l=0; l<=10; l++)
        {
            glColor3f(1.0,0.65,0.0);
            draw_circle(100,625,l+40);
        }


//cloud1

        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(160+m,625,l);

        }


        for(l=0; l<=35; l++)
        {
            glColor3f(.97,.97,.97);
            draw_circle(200+m,625,l);
            draw_circle(225+m,625,l);
        }

        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(265+m,625,l);
        }

//cloud2

        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(370+m,615,l);
        }

        for(l=0; l<=35; l++)
        {

            glColor3f(.97,.97,.97);
            draw_circle(410+m,615,l);
            draw_circle(435+m,615,l);
            draw_circle(470+m,615,l);
        }

        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(500+m,615,l);
        }

//cloud3


        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(580+m,605,l);
        }




        for(l=0; l<=35; l++)
        {

            glColor3f(.97,.97,.97);
            draw_circle(620+m,605,l);
            draw_circle(645+m,605,l);
        }

        for(l=0; l<=20; l++)
        {
            glColor3f(1.0,1.0,1.0);
            draw_circle(675+m,605,l);
        }
//grass
        glColor3f(0.0,0.9,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(0,160);
        glVertex2f(0,450);
        glVertex2f(1100,450);
        glVertex2f(1100,160);
        glEnd();

    }

    else
    {

//sky
        glColor3f(0.0,0.0,0.55);
        glBegin(GL_POLYGON);
        glVertex2f(0,450);
        glVertex2f(0,700);
        glVertex2f(1100,700);
        glVertex2f(1100,450);
        glEnd();

//moon
        int l;

        for(l=0; l<=35; l++)
        {
            glColor3f(0.96,0.96,0.96);
            draw_circle(100,625,l);

        }
        for(l=0; l<=10; l++)
        {
            glColor3f(0.83,0.83,0.83);
            draw_circle(100,625,l+30);
        }

//star1

        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(575,653);
        glVertex2f(570,645);
        glVertex2f(580,645);
        glVertex2f(575,642);
        glVertex2f(570,650);
        glVertex2f(580,650);
        glEnd();

//star2
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(975,643);
        glVertex2f(970,635);
        glVertex2f(980,635);
        glVertex2f(975,632);
        glVertex2f(970,640);
        glVertex2f(980,640);
        glEnd();

//star3
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(875,543);
        glVertex2f(870,535);
        glVertex2f(880,535);
        glVertex2f(875,532);
        glVertex2f(870,540);
        glVertex2f(880,540);
        glEnd();

//star4
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(375,598);
        glVertex2f(370,590);
        glVertex2f(380,590);
        glVertex2f(375,587);
        glVertex2f(370,595);
        glVertex2f(380,595);
        glEnd();

//star5
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(750,628);
        glVertex2f(745,620);
        glVertex2f(755,620);
        glVertex2f(750,618);
        glVertex2f(745,625);
        glVertex2f(755,625);
        glEnd();


//grass
        glColor3f(0.2,0.8,0.2);
        glBegin(GL_POLYGON);
        glVertex2f(0,160);
        glVertex2f(0,450);
        glVertex2f(1100,450);
        glVertex2f(1100,160);
        glEnd();

    }


//road boundary
    glColor3f(0.82,0.41,0.12);
    glBegin(GL_POLYGON);
    glVertex2f(0,150);
    glVertex2f(0,160);
    glVertex2f(1100,160);
    glVertex2f(1100,150);
    glEnd();

//road
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,150);
    glVertex2f(1100,150);
    glVertex2f(1100,0);
    glEnd();

//tree
    glColor3f(0.9,0.2,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(350,325);
    glVertex2f(350,395);
    glVertex2f(365,395);
    glVertex2f(365,325);
    glEnd();


    for(l=0; l<=30; l++)
    {
        glColor3f(0.0,0.4,0.0);
        draw_circle(340,400,l);
        draw_circle(380,400,l);
    }

    for(l=0; l<=25; l++)
    {
        glColor3f(0.0,0.5,0.0);
        draw_circle(350,440,l);
        draw_circle(370,440,l);
    }

    for(l=0; l<=20; l++)
    {
        glColor3f(0.0,0.8,0.0);
        draw_circle(360,465,l);
    }

    //tree2
    glColor3f(0.9,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(430,405);
    glVertex2f(430,475);
    glVertex2f(445,475);
    glVertex2f(445,405);
    glEnd();


    for(l=0; l<=30; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(420,480,l);
        draw_circle(460,480,l);
    }

    for(l=0; l<=25; l++)
    {
        glColor3f(0.0,0.5,0.0);
        draw_circle(430,520,l);
        draw_circle(450,520,l);
    }

    for(l=0; l<=20; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(440,545,l);
    }

    //tree3
    glColor3f(0.9,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(260,235);
    glVertex2f(260,305);
    glVertex2f(275,305);
    glVertex2f(275,235);
    glEnd();


    for(l=0; l<=30; l++)
    {
        glColor3f(0.0,0.4,0.0);
        draw_circle(250,310,l);
        draw_circle(290,310,l);
    }

    for(l=0; l<=25; l++)
    {
        glColor3f(0.0,0.5,0.0);
        draw_circle(260,350,l);
        draw_circle(280,350,l);
    }

    for(l=0; l<=20; l++)
    {
        glColor3f(0.0,0.4,0.0);
        draw_circle(270,375,l);
    }
    //tree4
    glColor3f(0.9,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(520,235);
    glVertex2f(520,305);
    glVertex2f(535,305);
    glVertex2f(535,235);
    glEnd();


    for(l=0; l<=30; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(505,305,l);
        draw_circle(545,305,l);
    }

    for(l=0; l<=25; l++)
    {
        glColor3f(0.0,0.5,0.0);
        draw_circle(515,345,l);
        draw_circle(535,345,l);
    }

    for(l=0; l<=20; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(525,370,l);
    }

    //tree5
    glColor3f(0.9,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(540,435);
    glVertex2f(540,405);
    glVertex2f(555,405);
    glVertex2f(555,435);
    glEnd();

    for(l=0; l<=30; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(530,460,l);
        draw_circle(570,460,l);
    }

    for(l=0; l<=25; l++)
    {
        glColor3f(0.0,0.5,0.0);
        draw_circle(540,500,l);
        draw_circle(560,500,l);
    }

    for(l=0; l<=20; l++)
    {
        glColor3f(0.0,0.7,0.0);
        draw_circle(550,525,l);
    }


    //house
    glColor3f(1.0,0.65,0);
    glBegin(GL_POLYGON);
    glVertex2f(600,375);
    glVertex2f(600,450);
    glVertex2f(650,525);
    glVertex2f(700,450);
    glVertex2f(700,375);
    glEnd();

//door
    glColor3f(0.5,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(640,375);
    glVertex2f(640,410);
    glVertex2f(660,410);
    glVertex2f(660,375);
    glEnd();

//roof
    glColor3f(0.63,0.32,0.18);
    glBegin(GL_POLYGON);
    glVertex2f(700,450);
    glVertex2f(650,525);
    glVertex2f(750,525);
    glVertex2f(780,450);
    glEnd();

//
    glColor3f(0.8,0.8,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(700,375);
    glVertex2f(700,450);
    glVertex2f(780,450);
    glVertex2f(780,375);
    glEnd();

//window
    glColor3f(0.5,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(725,400);
    glVertex2f(725,420);
    glVertex2f(740,420);
    glVertex2f(740,400);
    glEnd();


//car 1
    glColor3f(1.0,0.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(25+i,50);
    glVertex2f(25+i,125);
    glVertex2f(75+i,200);
    glVertex2f(175+i,200);
    glVertex2f(200+i,125);
    glVertex2f(250+i,115);
    glVertex2f(250+i,50);
    glEnd();


//windows
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(35+i,125);
    glVertex2f(80+i,190);
    glVertex2f(115+i,190);
    glVertex2f(115+i,125);
    glEnd();

    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(125+i,125);
    glVertex2f(125+i,190);
    glVertex2f(170+i,190);
    glVertex2f(190+i,125);
    glEnd();


    for(l=0; l<20; l++)
    {
        glColor3f(0.0,0.0,0.0);
        draw_circle(75+i,50,l);
        draw_circle(175+i,50,l);
    }

//car2

    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-470+i,50);
    glVertex2f(-470+i,112);
    glVertex2f(-400+i,125);
    glVertex2f(-372+i,210);
    glVertex2f(-210+i,210);
    glVertex2f(-180+i,125);
    glVertex2f(-135+i,125);
    glVertex2f(-110+i,50);
    glEnd();


//windows
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-410+i,125);
    glVertex2f(-364+i,200);
    glVertex2f(-300+i,200);
    glVertex2f(-300+i,125);
    glEnd();

    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-290+i,125);
    glVertex2f(-290+i,200);
    glVertex2f(-217+i,200);
    glVertex2f(-192+i,125);
    glEnd();

    for(l=0; l<30; l++)
    {
        glColor3f(0.0,0.0,0.0);
        draw_circle(-350+i,50,l);
        draw_circle(-200+i,50,l);
    }

    glFlush();

}


void idle()
{
    i+=SPEED/10;
    m+=0.25;
    if(i>1630)
        i=0.0;
    if(m>1100)
        m=0.0;
    glutPostRedisplay();

}

void keyboardFunc( unsigned char key, int x, int y )
{
    switch( key )
    {

    case 'd':
    case 'D':
        day=1;
        break;

    case 'n':
    case 'N':
        day=0;
        break;
    case 'S':
    case 's':
          SPEED=0.0;
          break;
    case 'A':
    case 'a':
          SPEED=10.0;
        break;

    };

}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1100.0,0.0,700.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_object();
    glFlush();
}

int main(int argc,char** argv)
{
    printf("Press RIGHT MOUSE BUTTON to display menu \n");
    printf("Press LEFT MOUSE BUTTON to quit the program \n");

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1100.0,700.0);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Scenario");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboardFunc);
    myinit();
    glutCreateMenu(1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    glutMainLoop();
    return 0;
}
