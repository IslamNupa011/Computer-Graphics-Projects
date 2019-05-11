#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include<iostream.h>

using namespace std;

float angle = 0.0, x=-4;

void home()
{

    glPushMatrix();{ //ground floor main block. .
        glColor3f(0.5,0.5,0.5);
        glTranslatef(0,0.4,0);
        glScalef(2,0.8,1);
        glutSolidCube(1);
    }
    glPopMatrix();


   glPushMatrix(); //ground floor door
   {
       glColor3f(0,0,0);
       glTranslatef(0,0.25,0);
       glScalef(0.3,0.5,1);
       glutSolidCube(1);
   }
  glPopMatrix();


    glPushMatrix();{ //1st room right window
      glColor3f(1,1,1);
      glTranslatef(0.65,0.5,0);
      glScalef(0.4,0.3,1);
      glutSolidCube(1);
  }
   glPopMatrix();

      glPushMatrix();{ //1st room left window
      glColor3f(1,1,1);
      glTranslatef(-0.65,0.5,0);
      glScalef(0.4,0.3,1);
      glutSolidCube(1);
  }
   glPopMatrix();




   glPushMatrix();{ // building roof
        glColor3f(0,0,0);
        glTranslatef(0,0.8,0);
        glScalef(2,0.02,1);
        glutSolidCube(1);
   }

   glPopMatrix();

   glPushMatrix();{ //room on floor
      glColor3f(0.7, 0.7,0.65);
      glTranslatef(0,1.1,0);
      glScalef(1.4,0.6,1);
      glutSolidCube(1);
   }
   glPopMatrix();

       glPushMatrix();{ //top room roof
       glColor3f(0,0,0);
       glTranslatef(0,1.4,0);
       glScalef(2,0.02,1);
       glutSolidCube(1);
   }
   glPopMatrix();

  glPushMatrix();{ //top room right window
      glColor3f(0,0,0);
      glTranslatef(0.45,1.15,0);
      glScalef(0.4,0.3,1);
      glutSolidCube(1);
  }
   glPopMatrix();

     glPushMatrix();{ //top room left window
      glColor3f(0,0,0);
      glTranslatef(-0.45,1.15,0);
      glScalef(0.4,0.3,1);
      glutSolidCube(1);
  }
   glPopMatrix();

   glPushMatrix();{ //top room roof
      glColor3f(1,0,0);
      glTranslatef(0,1.41,0);
      //glScalef(0,1.0,0);
      glBegin(GL_TRIANGLES);{
          glVertex3f(-1,0,0);
          glVertex3f(1,0,0);
          glVertex3f(0,0.5,0);
      }glEnd();
  }
   glPopMatrix();


}

void Bus(float r, float g, float b)
{
   glPushMatrix(); {//behind's Wheel
       glColor3f(1,1,1);
       glTranslatef(0.75,-0.5, -0.5);
       glRotatef(angle,0,0,1);
       glutWireTorus (0.1,0.2,10,10);
   }
   glPopMatrix();

   glPushMatrix();{ //Behind-back Wheel
       glColor3f(1,1,1);
       glTranslatef(-0.75,-0.5, -0.5);
       glRotatef(angle,0,0,1);
       glutWireTorus (0.1,0.2,10,10);
   }
   glPopMatrix();

   glPushMatrix();{ //School Bus..
        glColor3f(r,g,b);
        glScalef(2,1,1);
        glutSolidCube(1);

      glPushMatrix();{ //bus door
      glColor3f(1,1,1);
      glTranslatef(0.1,-0.1,0);
      glScalef(0.2,0.8,1);
      glutSolidCube(1);
  }
   glPopMatrix();


    glPushMatrix();{ //bus right window
      glColor3f(1,1,1);
      glTranslatef(0.35,0.2,0);
      glScalef(0.2,0.4,1);
      glutSolidCube(1);
  }
   glPopMatrix();

   glPushMatrix();{ //busright window
      glColor3f(1,1,1);
      glTranslatef(-0.135,0.2,0);
      glScalef(0.2,0.4,1);
      glutSolidCube(1);
  }
   glPopMatrix();

   glPushMatrix();{ //busright window
      glColor3f(1,1,1);
      glTranslatef(-0.36,0.2,0);
      glScalef(0.2,0.4,1);
      glutSolidCube(1);
  }
   glPopMatrix();



    }
    glPopMatrix();



   glPushMatrix();{ //Front-front Wheel
       glColor3f(0,0,0);
       glTranslatef(0.75,-0.5, 0.5);
       glRotatef(angle,0,0,1);
       glutSolidTorus (0.1,0.2,10,10);
   }
   glPopMatrix();

   glPushMatrix();{//Front-back Wheel Far
   glColor3f(0,0,0);
   glTranslatef(-0.75,-0.5, 0.5);
   glRotatef(angle,0,0,1);
   glutSolidTorus (0.1,0.2,10,10);
   }
   glPopMatrix();

   angle-=0.1;
}

void tree()
{
   glPushMatrix();{ //root of the tree
        glColor3f(0.18,0,0);
        glScalef(0.2,6,0.2);
        glutSolidCube(1);
   }
   glPopMatrix();

   glPushMatrix();{ // treee er matha
     	glColor3f(0,1,0.2);
     	glTranslatef(0,2,0);
    	glutSolidTorus (1.5,0.5,10,10);
    }
    glPopMatrix();
}
void background()
{
    glColor3f(0.24,0.67,0.37);
    glRecti(-3,-2,3,0); //green grass

  	glColor3f(0.13,0.68,0.90);
  	glRecti(-3,0,3,2); //sky


 //small trees
   glPushMatrix();{
       glTranslatef(1.7,0.6,0);
       glScalef(0.3,0.3,0.1);
       tree();
   }
   glPopMatrix();

  	glPushMatrix();{
       glTranslatef(1.5,0.8,0);
       glScalef(0.3,0.3,0.1);
       tree();
   }
   glPopMatrix();
//small tree..
   glPushMatrix();{
       glTranslatef(1.15,0.6,0);
       glScalef(0.3,0.3,0.1);
       tree();
   }
   glPopMatrix();

   glPushMatrix();{
     	glTranslatef(2.3,0.6,0);
     	glScalef(0.23,0.23,0.1);
     	tree();
    }glPopMatrix();

   //big trees
   glPushMatrix();{
     	glTranslatef(-1.6,0.4,0);
     	glScalef(0.23,0.23,0.1);
     	tree();
    }glPopMatrix();

 	glPushMatrix();{
     	glTranslatef(-2.3,0.6,0);
     	glScalef(0.23,0.23,0.1);
     	tree();
    }
    glPopMatrix();

    glPushMatrix();{
     	glTranslatef(-1.4,0.6,0);
     	glScalef(0.23,0.23,0.1);
     	tree();
    }
    glPopMatrix();

 home();
}

int loadBitmapImage (string ff)
{
    printf("line 1\n");
	int i, j = 0;
	FILE *l_file;
	BYTE *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

    char filename[103];
    for(int i=0;i<ff.size();++i){
        filename[i]=ff[i];
    }
    filename[ff.size()]='\0';

	if ((l_file = fopen(filename, "rb")) == NULL)
	{
        cout<<"null\n";
		return (-1);
	}
    cout<<(int)infoheader.biWidth<<"\n";
    cout<<(int)infoheader.biHeight<<"\n";
	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (BYTE *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}

	for(int k = 0;k<(int)sizeof(l_texture);++k){
        cout<<"l_texture["<<k<<"]: "<<(int)l_texture[k]<<"\n";
	}

	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);
}

void loadAllImages()
{
    printf("loading....\n");
	//MarbleImage = loadBitmapImage("images/MARBLES.bmp");
	MarbleImage = loadBitmapImage("images/MARBLES.BMP");

	//skyImage = loadBitmapImage("images/sk2.bmp");
	cout<<"loaded....\n";
}


void tv()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
		{

		   // glTranslatef(20,20,20);
		   //loadAllImages();
		    glColor3f(1,1,1);

			glBindTexture(GL_TEXTURE_2D, MarbleImage);

			glRotatef(90,0,1,0);
            glTranslatef(-50,1,94);
            glScalef(2,3.8,22);
			glBegin(GL_QUADS);
			{
			    glTexCoord3f(0.0, 0.0, 0.0);
			    glVertex3f(0,0,0);

                glTexCoord3f(1.0, 0.0, 0.0);
                glVertex3f(10,0,0);

                glTexCoord3f(1.0, 1.0, 0.0);
                glVertex3f(10,10,0);

			    glTexCoord3f(0.0, 1.0, 0.0);
			    glVertex3f(0,10,0);
			}
			glEnd();
			GLUquadricObj *obj = gluNewQuadric();
            gluQuadricTexture(obj, GL_TRUE);
            glScalef(0,0,0);
            gluSphere(obj, 50, 20, 20);
            //printf("\n ooo \n");
		}
     glPopMatrix();

	  glPushMatrix();

		glColor3f(0,0,0);
	    glTranslatef(97,20,40);
		glScalef(5,40,25);
		glutSolidCube(1);
      glPopMatrix();


}






void display()
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();

     glOrtho (-3,3,-2,2,-4,4);

   background ();

   glPushMatrix ();{
       glColor3f(0,0,0);
       glTranslated (0,-0.8,0);
       glScaled (9,0.8,0.1);
       glutSolidCube(1);   //place of change
   }
   glPopMatrix();

   glTranslatef(x,0,0); // to move bus
   glScalef(0.7,0.7,0.7); //size of the Bus

   glPushMatrix();{
       glTranslatef (-3,0,0); //last one
       Bus(1,0,0);
   }
   glPopMatrix();

   glPushMatrix();{
       glTranslatef (0,-1,0);
       Bus(0,1,0);   //2nd one
   }
   glPopMatrix();

   glPushMatrix();{

       glTranslatef (3,0,0);
       glColor3f(1,0,0);
       Bus(0,0,1); //1st one
   }
   glPopMatrix();
   tv();

   if (x<6)
  	x+=0.005; //control Bus speed
   else
  	x=-6;


   glutSwapBuffers();
   }


   void keyboardListener(unsigned char key, int x, int y)
{


}




int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition (0,0);
    glutInitWindowSize (1500,800);

    glutCreateWindow("Final_Project");
    glutDisplayFunc(display);
    glutIdleFunc (display);
    //glutSpecialFunc(specialKeyListener);
	//glutKeyboardFunc(keyboardListener);
	loadAllImages();
    glClearColor(1,1,1,1);
    glutMainLoop();
     return 0;
}
