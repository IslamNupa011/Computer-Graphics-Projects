#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include<bits/stdc++.h>

using namespace std;

float tx	=  20;
float ty	=  20;



void display(void)
{
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        //glColor3f(1, 1, 1);
        //glRectf(100.0,100.0,-100.0,-100.0);
        glColor3f(.145, .145, .145);
        glRectf(30.0,21.0,19.0,20.0);
        glRectf(30.0,21.0,29.0,10.0);
        glRectf(30.0,10.0,19.0,11.0);
        glRectf(19.0,10.0,20.0,21.0);

        glColor3f(.2, .2, .2);
        glRectf(20.0,20.0,29.0,11.0);

        glColor3f(1, 0, 0);
        glRectf(21.0,20.0,20.0,19.0);

        glColor3f(1, 0, 0);
        glRectf(29.0,12.0,28.0,11.0);

        glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(20,20);
        glVertex2f(20,11);

        glVertex2f(21,20);
        glVertex2f(29,20);

        glVertex2f(20,11);
        glVertex2f(28,11);

        glVertex2f(29,20);
        glVertex2f(29,11);

        //border done

        glVertex2f(21,19);
        glVertex2f(21,13);

        glVertex2f(22,16);
        glVertex2f(22,12);

        glVertex2f(23,16);
        glVertex2f(23,11);

        glVertex2f(24,17);
        glVertex2f(24,13);

        glVertex2f(21,19);
        glVertex2f(25,19);

        glVertex2f(22,18);
        glVertex2f(25,18);

        glVertex2f(21,17);
        glVertex2f(24,17);

        glVertex2f(21,12);
        glVertex2f(25,12);

        glVertex2f(25,20);
        glVertex2f(25,14);

        glVertex2f(25,13);
        glVertex2f(25,12);

        //half done


        glVertex2f(27,18);
        glVertex2f(27,14);

        glVertex2f(28,18);
        glVertex2f(28,13);

        glVertex2f(21,12);
        glVertex2f(25,12);

        glVertex2f(26,19);
        glVertex2f(29,19);

        glVertex2f(26,18);
        glVertex2f(28,18);

        glVertex2f(25,13);
        glVertex2f(28,13);

        glVertex2f(26,12);
        glVertex2f(29,12);

        glVertex2f(26,17);
        glVertex2f(26,13);

        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex2i(1+tx, ty);
        glVertex2i(tx, ty);
        glVertex2i(tx, ty-1);
        glVertex2i(1+tx, ty-1);
        glEnd();




	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(15.0, 35.0, 5.0, 25.0, -50.0, 50.0);
}



void spe_key(int key, int x, int y)
{
	switch (key) {

        case GLUT_KEY_LEFT:
		    if(ty==20)
		    {
                if(tx>20 && tx<=24)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>25 && tx<=28)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else
                    break;
		    }
		    else if(ty==19)
            {
                if(tx>21 && tx<=24)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>25 && tx<=28)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }
            else if(ty==18)
            {
                if(tx>21 && tx<=24)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>25 && tx<=26)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==17)
            {
                if(tx>21 && tx<=23)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==14)
            {
                if(tx>24 && tx<=25)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>26 && tx<=27)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==13)
            {
                if(tx>20 && tx<=21)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>23 && tx<=24)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>25 && tx<=28)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==12)
            {
                if(tx>20 && tx<=22)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>23 && tx<=28)
                {
                    tx--;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else break;

		case GLUT_KEY_RIGHT:
		    if(ty==20)
		    {
                if(tx>=20 && tx<24)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=25 && tx<28)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
		    }
		    else if(ty==19)
            {
                if(tx>=21 && tx<24)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=25 && tx<28)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else
                    break;
            }
            else if(ty==18)
            {
                if(tx>=21 && tx<24)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=25 && tx<26)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==17)
            {
                if(tx>=21 && tx<23)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==14)
            {
                if(tx>=24 && tx<25)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=26 && tx<27)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==13)
            {
                if(tx>=20 && tx<21)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=23 && tx<24)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=25 && tx<28)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(ty==12)
            {
                if(tx>=20 && tx<22)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx>=23 && tx<28)
                {
                    tx++;
                    cout<<tx<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(tx==28)
                {
                    exit(0);
                }

                else break;
            }

            else
                break;



        case GLUT_KEY_DOWN:

            if(tx==20)
		    {
                if(ty>12 && ty<=20)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
		    }

		    else if(tx==21)
            {
                if(ty>18 && ty<=19)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(ty>13 && ty<=17)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }
            else if(tx==22)
            {
                if(ty>13 && ty<=17)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }
            else if(tx==23)
            {
                if(ty>13 && ty<=17)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==24)
            {
                if(ty>13 && ty<=18)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==25)
            {
                if(ty>14 && ty<=20)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(ty>12 && ty<=13)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==26)
            {
                if(ty>14 && ty<=18)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==27)
            {
                if(ty>14 && ty<=18)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==28)
            {
                if(ty>13 && ty<=19)
                {
                    ty--;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }


            else
                break;


		case GLUT_KEY_UP:

            if(tx==20)
		    {
                if(ty>=12 && ty<20)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
		    }

		    else if(tx==21)
            {
                if(ty>=18 && ty<19)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(ty>=13 && ty<17)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }
            else if(tx==22)
            {
                if(ty>=13 && ty<17)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }
            else if(tx==23)
            {
                if(ty>=13 && ty<17)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==24)
            {
                if(ty>=13 && ty<18)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==25)
            {
                if(ty>=14 && ty<20)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else if(ty>=12 && ty<13)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==26)
            {
                if(ty>=14 && ty<18)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==27)
            {
                if(ty>=14 && ty<18)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }

            else if(tx==28)
            {
                if(ty>=13 && ty<19)
                {
                    ty++;
                    cout<<ty<<" ";
                    glutPostRedisplay();
                    break;
                }
                else break;
            }


            else
                break;


	  default:
			break;
	}
}

int main()
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (40, 40);
	glutCreateWindow ("Maze");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(spe_key);//up,down,left......
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}

