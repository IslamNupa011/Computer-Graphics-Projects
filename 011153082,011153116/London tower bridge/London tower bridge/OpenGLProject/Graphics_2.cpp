#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<GL/glut.h>

double cameraAngle, cameraAngleDelta;
int canDrawGrid;

double cameraHeight;
double cameraRadius;
int num_texture  = -1;
GLuint grassimg,wallimg,ballimg,ball1img,ball2img,cylimg,cylimg2,cylimg3,cylimg4,sky;

void frontwall()
{
    glPushMatrix();{
	glColor3f(.7,.6,.5);
	glScalef(80,.5,300);

	glTranslatef(0,-67,.6);
	glutSolidCube(1);

	}glPopMatrix();//cylnderbase

	glPushMatrix();{
	glColor3f(.8,.7,.6);
	glScalef(6,.5,3.5);
	glTranslatef(7,-68,8);

	}glPopMatrix();//end off front wallcubeeee

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pillfrnt
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft pilfrnt
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft backpil
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pil bck

	//uptorus&cylbder
	//torusbarupppppppppppppppppppppppp

		glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,322);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,-39,322);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,1,1,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	//enduptoru&..

	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,-38,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,38,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,38,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);


	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(44,34,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);

	}glPopMatrix(); //frntupcylbrder

	//2nd borderrrrrrrrreeeeerrrrrrrrrrreree

glPushMatrix(); {
	glTranslatef(0,0,-58);
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pillfrnt
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft pilfrnt
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft backpil
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pil bck

	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,-34,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,34,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);


	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,34,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);


	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(40,34,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);

		}glPopMatrix(); //frntupcylbrder
	}glPopMatrix();

	///////3rd borderrrrrrrrrrrrrrrrrrrrrrrrr
	glPushMatrix(); {
	glTranslatef(0,0,-120);
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pillfrnt
	//topptoruscone
	glPushMatrix(); {
		glColor3f(.8,0.7,.6);
		glTranslatef(40,-35,492);
		glScalef(1,1,2);
		glutSolidTorus(2,4.6,50,50);

	}glPopMatrix(); //r8pillfrnt
	//end
	//topptoruscone
	glPushMatrix(); {
		glColor3f(.8,0.7,.6);
		glTranslatef(-40,-35,492);
		glScalef(1,1,2);
		glutSolidTorus(2,4.6,50,50);

	}glPopMatrix(); //r8pillfrnt
	glPushMatrix(); {

			glColor3f(.9,.8,.7);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,35,528);
			//glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,1,1,22,6,200);


	}glPopMatrix(); //toptorcylnderrs
	glPushMatrix(); {

			glColor3f(.9,.8,.7);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(40,35,528);
			//glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,1,1,22,6,200);


	}glPopMatrix(); //toptorcylnderrs
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(40,35,550);
			glutSolidSphere(2,20,20);


	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(-40,35,550);
			glutSolidSphere(2,20,20);


	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(-38,35,542);
			glScalef(1.7,.8,1);
			glutSolidSphere(2,20,20);


	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(-42,35,542);
			glScalef(1.7,.8,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(38,35,542);
			glScalef(1.7,.8,1);
			glutSolidSphere(2,20,20);


	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(42,35,542);
			glScalef(1.7,.8,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	//yyy
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(-40,33,542);
			glScalef(.8,1.7,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(-40,37,542);
			glScalef(.8,1.7,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(40,33,542);
			glScalef(.8,1.7,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	glPushMatrix(); {
			glColor3f(.9,.8,.7);
			glTranslatef(40,37,542);
			glScalef(.8,1.7,1);
			glutSolidSphere(2,20,20);

	}glPopMatrix();
	//end
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,-35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft pilfrnt
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //lft backpil
	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,280);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(-40,35,270);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix(); //r8pil bck

	//cubeeeee btween border
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-34.1,275);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix();
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-34.1,337);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix();
	glPushMatrix(); {
		glColor3f(.8,.7,.63);
		glTranslatef(0,-37.5,395);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix(); //border cube
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-35,425);
		glScalef(80,5,60);
		glutSolidCube(1);

	}glPopMatrix(); //upper outside wall

	//cylndurbrder1

	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,-34,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,34,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,34,270);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);
			glTranslatef(-10,0,0);
			gluCylinder(cylinder_obj,.5,.5,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(40,34,270);
			glRotatef(90,1,0,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);
			glTranslatef(0,10,0);
			gluCylinder(cylinder_obj,.5,.5,72,6,200);

		}glPopMatrix(); //frntupcylbrder

	}glPopMatrix();

	////bottomwindooooooooowwwwww&dooooorrr
	glPushMatrix(); {

		glTranslatef(0,0,-62);
		glPushMatrix(); {
				glScalef(1.4,1,1);

			glPushMatrix(); {
				glTranslatef(14,0,0);
				glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-20,-34,177);
				glRotatef(90,0,1,0);
				glScalef(32,5,1.2);

				glutSolidCube(1);

			}glPopMatrix(); //lft1
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-10,-34,177);
				glRotatef(90,0,1,0);
				glScalef(32,5,1.2);

				glutSolidCube(1);

			}glPopMatrix(); //2
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-34,161);
				//glRotatef(90,0,1,0);
				glScalef(10,3,2);

				glutSolidCube(1);

			}glPopMatrix(); //lower
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-33,159);
				//glRotatef(90,0,1,0);
				glScalef(40,6,2);

				glutSolidCube(1);

			}glPopMatrix(); //lower
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-33,141);
				//glRotatef(90,0,1,0);
				glScalef(36,6,2);

				glutSolidCube(1);

			}glPopMatrix(); //lower
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-14,-33,124);
				//glRotatef(90,0,1,0);
				glScalef(12,6,3);

				glutSolidCube(1);

			}glPopMatrix(); //lower
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-34,167);
				glRotatef(90,0,1,0);
				glScalef(50,3,.6);

				glutSolidCube(1);

			}glPopMatrix(); //midlethin
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-8.3,-34,110);
				glRotatef(90,0,1,0);
				glScalef(30,3,1.7);

				glutSolidCube(1);

			}glPopMatrix(); //midlethindoorside1
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-19.5,-34,110);
				glRotatef(90,0,1,0);
				glScalef(30,3,1.7);

				glutSolidCube(1);

			}glPopMatrix(); //midlethindoorside2

			glPushMatrix(); {

				glColor3f(.7,.7,.7);
				glTranslatef(-14.5,-33,110);
				glRotatef(90,0,1,0);
				glScalef(30,3,11);

				glutSolidCube(1);

			}glPopMatrix(); //midlethindoormidlegray
			glPushMatrix(); {
				glColor3f(.9,.8,.7);

				glTranslatef(-17.4,-34.5,189.4);
				glRotatef(90,1,0,0);
				glScalef(.9,2,.4);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.65,2,50,50);
				}
				glDisable(GL_CLIP_PLANE0);

			}glPopMatrix();//uptorus11
			glPushMatrix(); {
				glColor3f(.9,.8,.7);

				glTranslatef(-12.7,-34.5,189.4);
				glRotatef(90,1,0,0);
				glScalef(.9,2,.4);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.65,2,50,50);
				}
				glDisable(GL_CLIP_PLANE0);

			}glPopMatrix();//uptorus22
			glPushMatrix(); {

				glColor3f(.7,.7,.7);
				glTranslatef(-15,-33,177);
				glRotatef(90,0,1,0);
				glScalef(32,3,10);

				glutSolidCube(1);

			}glPopMatrix(); //midleglasssgray
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-34.5,180);
				//glRotatef(90,0,1,0);
				glScalef(10,3,.9);

				glutSolidCube(1);

			}glPopMatrix(); //midlehorizntal
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-15,-34.5,194);
				//glRotatef(90,0,1,0);
				glScalef(11,5,3);

				glutSolidCube(1);

			}glPopMatrix(); //midlehorizntal

				}glPopMatrix();
				}glPopMatrix();

			//singlewindow333333333333midletttttttttttttttttttttttttttttttte

			//functioooonsmalwindoooww

			glPushMatrix(); {
					glTranslatef(0,0,-25);
			}glPopMatrix();
			glPushMatrix(); {
					glTranslatef(0,0,-43);
			}glPopMatrix();
			glPushMatrix(); {
					glTranslatef(-35,0,-43);
					glScalef(1.9,1,1);

			}glPopMatrix();

		glPushMatrix(); {
				glTranslatef(-37,0,0);

			glPushMatrix(); {
					glTranslatef(0,0,-25);

			}glPopMatrix();
			glPushMatrix(); {
					glTranslatef(0,0,-43);

			}glPopMatrix();
		}glPopMatrix();

			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				GLUquadricObj *cylinder_obj=gluNewQuadric();
				glTranslatef(0,-36,208);
				glRotatef(180,0,1,0);
				gluCylinder(cylinder_obj,.4,.55,13,16,200);

			}glPopMatrix(); //up++++++
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				GLUquadricObj *cylinder_obj=gluNewQuadric();
				glTranslatef(-1,-36,208);
				glRotatef(180,0,1,0);
				gluCylinder(cylinder_obj,.4,.55,13,16,200);

			}glPopMatrix(); //up++++++
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-1.2,-36,204);
				glScalef(1,1,1);
				glutSolidSphere(.8,10,30);

			}glPopMatrix(); //up++sphere
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-2.2,-36,204);
				glScalef(1,1,1);
				glutSolidSphere(.8,10,30);

			}glPopMatrix(); //up++sphere
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(1.2,-36,204);
				glScalef(1,1,1);
				glutSolidSphere(.8,10,30);

			}glPopMatrix(); //up++sphere

			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(0,-36,208);

				glutSolidSphere(.7,10,30);

			}glPopMatrix(); //up++sphere
			glPushMatrix(); {

				glColor3f(.9,.8,.7);
				glTranslatef(-1,-36,208);

				glutSolidSphere(.7,10,30);

			}glPopMatrix(); //up++sphere

		//doorfrnttttttttttors
			glPushMatrix(); {
				glColor3f(.9,.8,.7);

				glTranslatef(0,-34.5,125);
				glRotatef(90,1,0,0);
				glScalef(4,6,.4);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.25,2,50,50);
				}
				glDisable(GL_CLIP_PLANE0);

			}glPopMatrix();//uptorus22

		}glPopMatrix();

}

void doortorus()
{
	glPushMatrix(); {
				glColor3f(.9,.8,.7);

				glTranslatef(0,-34.5,105);
				glRotatef(90,1,0,0);
				glScalef(15,14,4);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.3,2,50,50);
					glColor3f(.8,.7,.6);
					glTranslatef(0,0,0.5);
					glScalef(.9,.9,1);
					glutSolidTorus(.3,2,50,50);
					glColor3f(.9,.8,.7);
					glTranslatef(0,0,0.5);
					glScalef(.9,.9,1);
					glutSolidTorus(.3,2,50,50);
					int j;
					for(j=0;j<4;j++)
					{
						glTranslatef(0,0,2);
						glPushMatrix(); {

								glColor3f(0,0,.6);
							glTranslatef(0,0,0);
							glScalef(.9,.9,1);
							glutSolidTorus(.19,2,50,50);
						}glPopMatrix();
					}
				}
				glDisable(GL_CLIP_PLANE0);


			}glPopMatrix();//uptorus22

}


void rigtwall()
{
	glPushMatrix();{
		//torusbarupppppppppppppppppppppppp

		glPushMatrix(); {
		glColor3f(.5,0.5,.55);
		glTranslatef(40,-35,322);
		glScalef(1,1,.4);
		glutSolidTorus(2,5,50,50);

	}glPopMatrix();

	glPushMatrix(); {

			glColor3f(.5,.5,.5);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-40,-39,322);
			glRotatef(90,0,1,0);
			gluCylinder(cylinder_obj,1,1,86,6,200);

	}glPopMatrix(); //frntupcylbrder
	//enduptoru&..
			glPushMatrix();{


	glColor3f(.7,.6,.5);
	glScalef(80,.5,160);
	glTranslatef(0,-67,1.30);
	glutSolidCube(1);

	}glPopMatrix();//cylnderbase

	glPushMatrix();{


	glColor3f(.7,.6,.5);
	glScalef(20,.5,144);
	glTranslatef(1.6,-67,1.30);
	glutSolidCube(1);

	}glPopMatrix();//cylnderbase
	glPushMatrix();{

	glColor3f(.7,.6,.5);
	glScalef(20,.5,144);
	glTranslatef(-1.6,-67,1.30);
	glutSolidCube(1);

	}glPopMatrix();//cylnderbase


	glTranslatef(0,0,-120);
	//cubeeeee btween border
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-34.1,275);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix();
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-34.1,337);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix();
	glPushMatrix(); {
		glColor3f(.8,.7,.63);
		glTranslatef(0,-37.5,395);
		glScalef(80,1,8.5);
		glutSolidCube(1);

	}glPopMatrix(); //border cube
	glPushMatrix(); {
		glColor3f(.8,.7,.6);
		glTranslatef(0,-35,425);
		glScalef(80,5,60);
		glutSolidCube(1);

	}glPopMatrix(); //upper outside wall
	}glPopMatrix(); //upper outside wall
	//bigggggTorusroaddddddddddd

	glRotatef(180,0,0,1);
	glTranslatef(0,70,0);
	doortorus();

}

void cone()
{
	glPushMatrix(); {
		glColor3f(.6,.6,.6);
		GLUquadricObj *obj= gluNewQuadric();
	glPushMatrix(); {

		glTranslatef(0,25,371);
		glRotatef(90, 1, 0, 0);
		//glRotatef(90, 0, 0, 1);
		glScalef(1.6, 4, 2);
		gluCylinder(obj, 19, 19, 26, 3, 10);
	}glPopMatrix();//roof



	glPushMatrix(); {

		glTranslatef(0,-27,333);
		glRotatef(90, 0, 0, 1);
		glScalef(1.6, 1.6, 4.1);
		glutSolidCone(16.8,27.8,2,1);
	}glPopMatrix();//lupwall
	glPushMatrix(); {

		glTranslatef(0,24,333);
		glRotatef(90, 0, 0, 1);
		glScalef(1.6, 1.6, 4.1);
		glutSolidCone(16.8,27.8,2,1);
	}glPopMatrix();//lupwall
	glPushMatrix();{

				glColor3f(0.1,0.1,0.1);
				glTranslatef(0,-1,445);
				glRotatef(90,1,0,0);
				glScalef(3,7,54.5);
				glutSolidCube(1);

	}glPopMatrix();//longbar1

	glPushMatrix();{

				glColor3f(1,.8,.4);
				glTranslatef(0,-1,439);
				glRotatef(90,1,0,0);
				glScalef(4,7,55);
				glutSolidCube(1);

	}glPopMatrix();//longbar1
	glPushMatrix(); {

		glTranslatef(0,0,423);
		//glRotatef(90, 0, 0, 1);
		glScalef(1.2, 1.2, 2);
		glutSolidCone(16.8,27.8,2,1);
	}glPopMatrix();//lupwall
	glPushMatrix(); {

		glTranslatef(0,0,423);
		glRotatef(5, 0, 0, 1);
		glScalef(1200, 1.2, 2);
		glutSolidCone(16.8,27.8,2,1);
	}glPopMatrix();//lupwall
	glPushMatrix(); {

		glTranslatef(0,0,423);
		glRotatef(-5, 0, 0, 1);
		glScalef(1200, 1.2, 2);
		glutSolidCone(16.8,27.8,2,1);
	}glPopMatrix();//lupwall

	glPushMatrix(); {
		glColor3f(.9,.8,.7);
		glTranslatef(0,0,421);

		gluCylinder(obj, 1, .3, 70, 30, 10);
	}glPopMatrix();//roof
	glPushMatrix(); {
		glColor3f(.9,.8,.7);
		glTranslatef(0,-8,421);

		gluCylinder(obj, 1, .8, 44, 30, 10);
	}glPopMatrix();//roof
	glPushMatrix(); {
		glColor3f(.9,.8,.7);
		glTranslatef(0,8,421);

		gluCylinder(obj, 1, .8, 44, 30, 10);
	}glPopMatrix();//roof

		}glPopMatrix();
}

void palace()
{
	glTranslatef(0,0,-30);
	glPushMatrix();{
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,grassimg);
		glBegin(GL_QUADS);{
			glColor3f(1,1,1);
			glTexCoord2f(0,1);
			glVertex3f(-1000,1000,0);
			glTexCoord2f(0,0);
			glVertex3f(-1000,-1000,0);
			glTexCoord2f(1,0);
			glVertex3f(1000,-1000,0);
			glTexCoord2f(1,1);
			glVertex3f(1000,1000,0);
		}glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	glPushMatrix();{
		glRotatef(45,0,0,1);
		glScalef(1.5,1.5,1.5);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			gluCylinder(cylinder_obj,50,50,38,4,20);
			glScalef(70,70,70);
			glRotatef(-45,0,0,1);
			//glTranslatef(0,0,-.1);
			glutSolidCube(1);
		}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//cylnderbase
	}glPopMatrix();//fulltrnslte Z
	glPushMatrix();{
			 glColor3f(1,1,1);
		  glTranslatef(0,0,170);
			glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,sky);
			GLUquadricObj *obj = gluNewQuadric();
		gluQuadricTexture(obj,GL_TRUE);
		  gluSphere(obj,6000,300,300);
			}
		  glDisable(GL_TEXTURE_2D);
	glPopMatrix();}


	//baseextraroundcylnder%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	glPushMatrix();{
		//glRotatef(45,0,0,1);
		glTranslatef(0,-20,0);
		glScalef(1.5,1.5,1.5);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);

			double equ[4];
			equ[0] =0;
			equ[1] =1;
			equ[2] =0;
			equ[3] =-48.5;
			glClipPlane(GL_CLIP_PLANE0,equ);
			glEnable(GL_CLIP_PLANE0);{
			gluCylinder(cylinder_obj,60,60,38,80,20);
			glScalef(1,1,.2);
			glTranslatef(0,0,155);
			glutSolidSphere(60,50,50);
			}
			glDisable(GL_CLIP_PLANE0);

		}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//back
	glPushMatrix();{
		glRotatef(180,0,0,1);
		glTranslatef(0,-20,0);
		glScalef(1.5,1.5,1.5);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);

			double equ[4];
			equ[0] =0;
			equ[1] =1;
			equ[2] =0;
			equ[3] =-48.5;
			glClipPlane(GL_CLIP_PLANE0,equ);
			glEnable(GL_CLIP_PLANE0);{
			gluCylinder(cylinder_obj,60,60,38,80,20);
			glScalef(1,1,.2);
			glTranslatef(0,0,155);
			glutSolidSphere(60,50,50);
			}
			glDisable(GL_CLIP_PLANE0);

		}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//front

	//Bigpillars%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$


	glPushMatrix();{
		//glRotatef(180,0,0,1);
		glTranslatef(-40,-35,0);
		glScalef(2,2,18);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			gluCylinder(cylinder_obj,3,3,15,10,20);
			glTranslatef(0,0,15);
			gluCylinder(cylinder_obj,3.15,3.15,3,6,20);
		}
		glDisable(GL_TEXTURE_2D);////upperwhite
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg3);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,3);
			gluCylinder(cylinder_obj,3.15,3.15,2.6,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{///top coooooone1
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,2.6);
			gluCylinder(cylinder_obj,3.15,.15,2.6,6,200);
			}
		glDisable(GL_TEXTURE_2D);

	}glPopMatrix();//frontleft
	glPushMatrix();{
		//glRotatef(180,0,0,1);
		glTranslatef(40,-35,0);
		glScalef(2,2,18);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			gluCylinder(cylinder_obj,3,3,15,10,20);
			glTranslatef(0,0,15);
			gluCylinder(cylinder_obj,3.15,3.15,3,6,20);


		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg3);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,3);
			gluCylinder(cylinder_obj,3.15,3.15,2.6,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{///top coooooone1
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,2.6);
			gluCylinder(cylinder_obj,3.15,.15,2.6,6,200);
			}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//frontright

	glPushMatrix();{
		//glRotatef(180,0,0,1);
		glTranslatef(-40,35,0);
		glScalef(2,2,18);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			gluCylinder(cylinder_obj,3,3,15,10,20);
			glTranslatef(0,0,15);
			gluCylinder(cylinder_obj,3.15,3.15,3,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg3);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,3);
			gluCylinder(cylinder_obj,3.15,3.15,2.6,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{///top coooooone1
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,2.6);
			gluCylinder(cylinder_obj,3.15,.15,2.6,6,200);
			}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//backleft

	glPushMatrix();{
		//glRotatef(180,0,0,1);
		glTranslatef(40,35,0);
		glScalef(2,2,18);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			gluCylinder(cylinder_obj,3,3,15,10,20);
			glTranslatef(0,0,15);
			gluCylinder(cylinder_obj,3.15,3.15,3,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{
			glBindTexture(GL_TEXTURE_2D,cylimg3);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,3);
			gluCylinder(cylinder_obj,3.15,3.15,2.6,6,20);

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);{///top coooooone1
			glBindTexture(GL_TEXTURE_2D,cylimg2);
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			gluQuadricTexture(cylinder_obj,GLU_TRUE);
			glTranslatef(0,0,2.6);
			gluCylinder(cylinder_obj,3.15,.15,2.6,6,200);
			}
		glDisable(GL_TEXTURE_2D);
	}glPopMatrix();//backr8

	//uproofcube
	glPushMatrix(); {

				glColor3f(.4,.4,.4);
				glTranslatef(0,0,332);
				//glRotatef(90,0,1,0);
				glScalef(80,70,3);

				glutSolidCube(1);

			}glPopMatrix(); //uproof

	//frontwaall text#######################################
	glPushMatrix();{
	frontwall();
	}glPopMatrix();
	///upbigconeee
	glPushMatrix();{
		glScalef(1.5,1,.95);
		cone();
	}glPopMatrix();


	glPushMatrix();{
		glScalef(1,.9,1);
		glTranslatef(6,0,0);
		glRotatef(90,0,0,1);
		glPushMatrix();{
			rigtwall();
		}glPopMatrix();//backr8
	}glPopMatrix();//backr8

	glPushMatrix();{
		glScalef(1,.9,1);
		glTranslatef(-6,0,0);
		glRotatef(-90,0,0,1);
		glPushMatrix();{
			rigtwall();
		}glPopMatrix();//backr8
	}glPopMatrix();//backr8


	glPushMatrix();{
		//glScalef(1,.9,1);
		glTranslatef(0,0,0);
		glRotatef(180,0,0,1);
		glPushMatrix();{
			frontwall();
		}glPopMatrix();//backr8
	}glPopMatrix();//backr8

	//side

	glPushMatrix();{
	glColor3f(0,.4,.7);
	glTranslatef(0,29,85);
	glScalef(80,.5,60);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase

	glPushMatrix();{
	glColor3f(0,.4,.7);
	glTranslatef(0,-29,85);
	glScalef(80,.5,60);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase

	//frntsmall
		int k;
	glPushMatrix();{
	for(k=0;k<=10;k++)
	{

		glTranslatef(-7,0,0);
	glPushMatrix();{
		glColor3f(0,0,.6);
		glTranslatef(40,29,70);
		glScalef(2,3,35);
		glutSolidCube(1);
	}glPopMatrix();//cylnderbase
	glPushMatrix();{
		glColor3f(0,0,.6);
		glTranslatef(40,-29,70);
		glScalef(2,3,35);
		glutSolidCube(1);
	}glPopMatrix();//cylnderbase

	}
	}glPopMatrix();

	glPushMatrix();{
	glColor3f(0,.0,.5);
	glTranslatef(0,28,73);
	glScalef(80,.5,3);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase

	glPushMatrix();{
	glColor3f(0,.0,.5);
	glTranslatef(0,28,85);
	glScalef(80,.5,3);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase
	//
	glPushMatrix();{
	glColor3f(0,.0,.5);
	glTranslatef(0,-28,73);
	glScalef(80,.5,3);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase

	glPushMatrix();{
	glColor3f(0,.0,.5);
	glTranslatef(0,-28,85);
	glScalef(80,.5,3);
	glutSolidCube(1);
	}glPopMatrix();//cylnderbase

}

void outsideroadside()
{
	glPushMatrix(); {
		glColor3f(.0,.0,.6);
		glTranslatef(0,-32,25);
		glScalef(360,5,7);
		glutSolidCube(1);
	}glPopMatrix(); //sideblue

	//frntsidestrt
	glPushMatrix(); {
		glColor3f(.6,.2,0);
		glTranslatef(0,-32,45);
		glScalef(360,5.5,3);
		glutSolidCube(1);
	}glPopMatrix(); //sideeuprailng
	glPushMatrix(); {
		glColor3f(.9,.9,.9);
		glTranslatef(0,-32,35);
		glScalef(360,3,20);
		glutSolidCube(1);
	}glPopMatrix(); //sidemidlewhite
	int i;
	for(i=170;i>-180;i=i-15)
	{
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(i,-32,35);
		glScalef(3,5,20);
		glutSolidCube(1);
	}glPopMatrix(); //midlezebra
	}
}

void road()
{
	glPushMatrix(); {
		glColor3f(.4,.4,.4);
		glTranslatef(0,0,25);
		glScalef(1300,60,5);
		glutSolidCube(1);
	}glPopMatrix(); //bl;ack

	int i;
	for(i=620;i>-620;i=i-25)
	{
	glPushMatrix(); {
		glColor3f(.9,.9,.9);
		glTranslatef(i,0,25.5);
		glScalef(10,4,5);
		glutSolidCube(1);
	}glPopMatrix(); //midlezebra
	}


	outsideroadside();
	glPushMatrix(); {
		glTranslatef(440,0,0);
		outsideroadside();
		}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(0,64,0);
		outsideroadside();
		}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(-440,0,0);
		outsideroadside();

		}glPopMatrix();
	//
	glPushMatrix(); {
		glTranslatef(440,64,0);
		outsideroadside();

		}glPopMatrix();
	glPushMatrix(); {
		glTranslatef(-440,64,0);
		outsideroadside();

		}glPopMatrix();

	//underrroaaadtoruuuusss
	glPushMatrix(); {
				glColor3f(0,0,.6);

				glTranslatef(0,-35,-40);
				glRotatef(90,1,0,0);
				glScalef(200,60,1);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.04,1,50,50);
				}
				glDisable(GL_CLIP_PLANE0);

			}glPopMatrix();//uptorus22
	 int j=34,k=0;

	for(i=160;i>45;i=i-15)
	{
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(i,-32,12+k);
		k=k+1;
		glScalef(3,3,j);
		j=j-5;
		glutSolidCube(1);
	}glPopMatrix(); //midlezebralower
	}
	j=34;k=0;
	for(i=-165;i<-45;i=i+15)
	{
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(i,-32,11+k);
		k=k+1;
		glScalef(3,3,j);
		j=j-5;
		glutSolidCube(1);
	}glPopMatrix(); //midlezebralower
	}

	//backsideksssssssssssssssj

	//underrroaaadtoruuuusss
	glPushMatrix(); {
				glColor3f(0,0,.6);

				glTranslatef(0,35,-40);
				glRotatef(90,1,0,0);
				glScalef(200,60,1);
				double equ[4];
				equ[0] =0;
				equ[1] =1;
				equ[2] =0;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE0,equ);
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.04,1,50,50);
				}
				glDisable(GL_CLIP_PLANE0);


			}glPopMatrix();//uptorus22
	 j=34;k=0;

	for(i=160;i>45;i=i-15)
	{
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(i,32,12+k);
		k=k+1;
		glScalef(3,3,j);
		j=j-5;
		glutSolidCube(1);
	}glPopMatrix(); //midlezebralower
	}
	j=34;k=0;
	for(i=-165;i<-45;i=i+15)
	{
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(i,32,11+k);
		k=k+1;
		glScalef(3,3,j);
		j=j-5;
		glutSolidCube(1);
	}glPopMatrix(); //midlezebralower
	}
}

void sideboard()
{
	glPushMatrix(); {
		glColor3f(0,.2,.8);
		glTranslatef(0,-34,265);
		glScalef(360,5,2);
		glutSolidCube(1);
	}glPopMatrix(); //sideblue
	glPushMatrix(); {
		glColor3f(0,.2,.8);
		glTranslatef(0,-34,257);
		glScalef(360,5,2);
		glutSolidCube(1);
	}glPopMatrix(); //sideblue
	glPushMatrix(); {
		glColor3f(.6,.8,.8);
		glTranslatef(0,-34,276);
		glScalef(360,2,23);
		glutSolidCube(1);
	}glPopMatrix(); //sidebluemidle
	glPushMatrix(); {
		glColor3f(.9,.9,.9);
		glTranslatef(0,-34,261);
		glScalef(360,2,7);
		glutSolidCube(1);
	}glPopMatrix(); //sidebluemidle
	int i;

	for(i=170;i>-180;i=i-8)
	{
	glPushMatrix(); {
		glColor3f(0,.2,.8);
		glTranslatef(i,-34,261);
		glScalef(2,5,7);
		glutSolidCube(1);
	}glPopMatrix(); //midlezebra
	}
	glPushMatrix(); {
		glColor3f(.6,.2,0);
		glTranslatef(0,-34,287);
		glScalef(360,5,1.7);
		glutSolidCube(1);
	}glPopMatrix(); //sideupwood
	glPushMatrix(); {
		glColor3f(0,0,.6);
		glTranslatef(0,-34,285);
		glScalef(360,5,3);
		glutSolidCube(1);
	}glPopMatrix(); //sideupwood

	for(i=190;i>-180;i=i-8.5)
	{
		glPushMatrix(); {
	glTranslatef(i,0,0);
	glScalef(.6,1,1);
	glPushMatrix(); {
			glColor3f(1,.9,.8);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(0,-35,266);
			glRotatef(45,0,1,0);
			gluCylinder(cylinder_obj,1.5,1.5,23,6,200);

	}glPopMatrix(); //frntupcylbrder
	glPushMatrix(); {
			glColor3f(1,.9,.8);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(20,-35,266);
			glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1.5,1.5,23,6,200);

	}glPopMatrix(); //frntupcylbrder
	}glPopMatrix(); //frntupcylbrder
	}
}

void toproof()
{

	sideboard();
	glPushMatrix(); {
		glTranslatef(0,54,0);
		sideboard();
	}glPopMatrix();
	glPushMatrix(); {

		glRotatef(180,0,0,1);

	}glPopMatrix();
	glPushMatrix(); {
		glRotatef(180,0,0,1);
		glTranslatef(0,54,0);
		sideboard();
	}glPopMatrix();
	glPushMatrix(); {
		glRotatef(180,0,0,1);
		sideboard();
	}glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0,190,270);
		glRotatef(90,1,0,0);
		glScalef(.6,.1,.8);

	}glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0,54,0);
		glPushMatrix(); {
		glTranslatef(0,190,270);
		glRotatef(90,1,0,0);
		glScalef(.6,.1,.8);

		}glPopMatrix();
	}glPopMatrix();
	//2

	glPushMatrix(); {
		glTranslatef(2,54,19);
		glPushMatrix(); {
		glTranslatef(0,190,270);
		glRotatef(90,1,0,0);
		glScalef(.6,.1,.8);

		}glPopMatrix();
	}glPopMatrix();
	glPushMatrix(); {
		glTranslatef(2,0,19);
		glPushMatrix(); {
		glTranslatef(0,190,270);
		glRotatef(90,1,0,0);
		glScalef(.6,.1,.8);

		}glPopMatrix();
	}glPopMatrix();

}

void hangintorus()
{
	glPushMatrix(); {
				glColor3f(0,0,.6);

				glTranslatef(410,-35,120);
				glRotatef(90,1,0,0);
				glScalef(200,60,1);
				double equ1[4];
				equ1[0] =1;
				equ1[1] =1;
				equ1[2] =0;
				equ1[3] =0;

				glPushMatrix(); {

				double equ[4];
				equ[0] =-.8;
				equ[1] =1;
				equ[2] =2;
				equ[3] =0;
				glClipPlane(GL_CLIP_PLANE1,equ1);
				glClipPlane(GL_CLIP_PLANE0,equ);

				glEnable(GL_CLIP_PLANE1);{
				glEnable(GL_CLIP_PLANE0);{
					glutSolidTorus(.04,1,50,50);
				}
				glDisable(GL_CLIP_PLANE0);
				}
				glDisable(GL_CLIP_PLANE1);
				}glPopMatrix();//uptorus22

			}glPopMatrix();//uptorus22

}
void display(){
	//codes for Models, Camera

	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
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
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,0,		0,0,1);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	// draw the three major AXES

	/****************************
	/ Add your objects from here
	****************************/
	//basebox%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	glPushMatrix();{
		glTranslatef(-220,0,0);
		palace();
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(220,0,0);
		glRotatef(180,0,0,1);
		palace();
	}glPopMatrix();

	//
	glPushMatrix();{
		road();
	}glPopMatrix();
	glPushMatrix();{
		toproof();
	}glPopMatrix();

	//hngntorus
	glPushMatrix();{
		glTranslatef(-776,-2,-35);
		glRotatef(45,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	//
	glPushMatrix();{
		glTranslatef(-738,-2,-62);
		glRotatef(40,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();

	//2
	glPushMatrix();{
		glRotatef(180,0,0,1);
	glPushMatrix();{
		glTranslatef(-776,-2,-35);
		glRotatef(45,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();
	//
	glPushMatrix();{
		glRotatef(180,0,0,1);
	glPushMatrix();{
		glTranslatef(-738,-2,-62);
		glRotatef(40,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();

	//3333
	glPushMatrix();{
		glTranslatef(0,-65,0);
	glPushMatrix();{
		glTranslatef(-776,-2,-35);
		glRotatef(45,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	//
	glPushMatrix();{
		glTranslatef(-738,-2,-62);
		glRotatef(40,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();

	//
	glPushMatrix();{
		glTranslatef(0,65,0);
	glPushMatrix();{
		glRotatef(180,0,0,1);
	glPushMatrix();{
		glTranslatef(-776,-2,-35);
		glRotatef(45,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();
	//
	glPushMatrix();{
		glRotatef(180,0,0,1);
	glPushMatrix();{
		glTranslatef(-738,-2,-62);
		glRotatef(40,0,1,0);
	glPushMatrix();{
		glRotatef(180,1,0,1);
		hangintorus();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();
	}glPopMatrix();

	//sidehangn pillars
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(300,-32,45);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,136,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(300,32,45);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,136,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-300,32,45);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,136,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-300,-32,45);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,136,100,20);

	}glPopMatrix(); //

	//22
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(350,-32,47);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,73,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(350,32,47);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,73,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-350,-32,47);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,73,100,20);

	}glPopMatrix(); //
	glPushMatrix(); {
			glColor3f(1,1,1);
			GLUquadricObj *cylinder_obj=gluNewQuadric();
			glTranslatef(-350,32,47);
			//glRotatef(-45,0,1,0);
			gluCylinder(cylinder_obj,1,1,73,100,20);

	}glPopMatrix(); //

	glutSwapBuffers();
}

void animate(){

	glutPostRedisplay();	//this will call the display AGAIN

}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraRadius += 20;
			break;
		case GLUT_KEY_UP:		// up arrow key
			if(cameraRadius > 10)
				cameraRadius -= 20;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.16;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.16;
			break;

		case GLUT_KEY_PAGE_UP:
			cameraHeight += 18;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraHeight -= 18;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void init(){

	cameraAngle = 0;	//angle in radian
	cameraAngleDelta = 0.001;
	canDrawGrid = 1;

	cameraHeight = 115;
	cameraRadius = 700;
	//clear the screen
	glClearColor(0,0,0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	gluPerspective(70,	1,	0.1,	10000.0);

}

int main(int argc, char **argv){

	glutInit(&argc,argv);							//initialize the GLUT library

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Some Title");

	init();						//codes for initialization

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutSpecialFunc(specialKeyListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
