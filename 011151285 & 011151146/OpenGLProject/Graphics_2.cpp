#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <glut.h>
#include <iostream>
#include<fstream>
#include<map>
#include<vector>
#include <dirent.h>

using namespace std;


struct colCode{
    int rgb[3];
};

int x=0;
int st=0;
double i=0;
double j=0;

int ix=0;
int iy=0;
double ro=0;
int imgChane=0;


double camx=-50;
double camy=0;
double camz=2700;


char pic[1000][600];

int picNo=0;
int total_img; // if(picno==total_img){picno=0}


 map< char ,int > trc;
 map <char , colCode> col;
 vector<char> uniq;



 char img[78][300]; //store all txt file name

void FileToPixel(int p){

char read[1000];

int take;

take= p;


 FILE *fp;
 fp = fopen(img[take],"r");
 while (fgets(read, sizeof(read), fp)) {
        //printf("%s\n", read);
         for(int i=0;read[i]!='\0';i++){
            if(trc[read[i]]==0){
            trc[read[i]]=1;
            uniq.push_back(read[i]);
            }
        }


}
 fclose(fp);

if(st==0){
 for(int i=0;i<uniq.size();i++){
        //printf("%c\n",uniq[i]);
        col[uniq[i]].rgb[0]=(250+rand()%10);
        col[uniq[i]].rgb[1]=(225+rand()%30);
        col[uniq[i]].rgb[2]=(216+rand()%20);

        if( uniq[i]=='@' ||uniq[i]=='#'){
            col[uniq[i]].rgb[0]=20;
            col[uniq[i]].rgb[1]=20;
            col[uniq[i]].rgb[2]=20;

        }


         else if(uniq[i]==' '){

            col[uniq[i]].rgb[0]=250;
            col[uniq[i]].rgb[1]=210;
            col[uniq[i]].rgb[2]=210;

        }

        else{

            col[uniq[i]].rgb[0]=123+rand()%123;
            col[uniq[i]].rgb[1]=55+rand()%200;
            col[uniq[i]].rgb[2]=55+rand()%200;

        }

    }
    st++;
}


if(st==1){
fp = fopen(img[take],"r");
 while (fgets(read, sizeof(read), fp)) {
        //printf("%s\n", read);

         for(int k=0;read[k]!='\0';k++){

                    glPushMatrix();
                    double a= (double)col[read[k]].rgb[0];
                    double b= (double)col[read[k]].rgb[1];
                    double c= (double)col[read[k]].rgb[2];
                    glColor3f(a/255,b/255,c/255);
                    glTranslatef(i,j,1);
                    glRotatef(ro,0,0,1);
                    glRectd(0,0,2.5,1.5);
                    glPopMatrix();
                    i+=1.6;

                   pic[ix][k]=read[k];
                   if(read[k+1]=='\0'){
                    pic[ix][k+1]='\0';
                    ix++;
                   }
        }


        i=0;
        j+=1.6;

}
 fclose(fp);

}




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
	gluLookAt(camx,camy,camz,camx,camy,0,	0,1,0);

	//FileToPixel();

	//glColor3f(1, 0, 0);
	/*
	glBegin(GL_QUADS);
	{
	    glVertex3f(-5,0, 0);
	    glVertex3f(5,0, 0);
	    glVertex3f(5,15, 0);
	    glVertex3f(-5, 15, 0);
	}
	glEnd();

	*/


	/*

	for(double i=0;i<101;i+=1.1){

    for (double j=0;j<101;j+=1.1){
    glPushMatrix();
    glColor3f(i/255, j/255, 0);
    glTranslatef(i,j,0);
	glRectd(0,0,1,1);
	glPopMatrix();
    }

	}
*/




glRotated(-180,1,0,0);
glTranslated(-1050,-1950,1);
double x,y;
x=0;
y=0;
for(int i=0;i<ix;i++){

    for(int j=0;pic[i][j]!='\0';j++){

        glPushMatrix();
                    double a= (double)col[pic[i][j]].rgb[0];
                    double b= (double)col[pic[i][j]].rgb[1];
                    double c= (double)col[pic[i][j]].rgb[2];
        glColor3f(a/255,b/255,c/255);
       //glRotatef(ro,0,1,0);
        glTranslatef(x,y,1);
	   // glRectd(0,0,18.5,29.5);
	    glutWireSphere(9,6,6);
	    glPopMatrix();
	    x+=18.5;

    }
    y+=18.5;
    x=0;
    //no
}





	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate()
{
    ro+=9.5;
    imgChane+=2;
    if(imgChane>6){

        /*
        imgChane=0;
        x=0;
        st=0;
        i=0;
        j=0;
        ix=0;
        iy=0;
        FileToPixel(0);
        */

    }

	//codes for any changes in Models, Camera

	//this will call the display AGAIN
	glutPostRedisplay();
}



void specialKeyListener(int key, int x, int y)
{

        //color change

	if (key == GLUT_KEY_INSERT)
	{
		//vAngle+=angleSpeed;


		imgChane=0;
        x=0;
        st=0;
        i=0;
        j=0;
        ix=0;
        iy=0;
        FileToPixel(picNo);

	}


	//left

	if(key==GLUT_KEY_LEFT){

        camx+=50;
	}

//right
	if(key==GLUT_KEY_RIGHT){

        camx-=50;
	}


	//up

    if(key==GLUT_KEY_UP){

        camy+=50;
	}


	//down

	if(key==GLUT_KEY_DOWN){

        camy-=50;
	}


	//zoomout


	if (key == GLUT_KEY_PAGE_UP)
	{
		//vAngle+=angleSpeed;
		camz+=150;

	}


	//zoom in

	if (key == GLUT_KEY_PAGE_DOWN)
	{
		//vAngle+=angleSpeed;
		camz-=150;

	}


	//backward

	if(key==GLUT_KEY_F1){
        picNo++;
        imgChane=0;
        x=0;
        st=0;
        i=0;
        j=0;
        ix=0;
        iy=0;

        if(picNo>total_img){
            picNo=0;
        }
        FileToPixel(picNo);
	}


	//forward

	if(key==GLUT_KEY_F2){
        picNo--;
        imgChane=0;
        x=0;
        st=0;
        i=0;
        j=0;
        ix=0;
        iy=0;

        if(picNo<0){
            picNo=total_img;
        }
        FileToPixel(picNo);
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
//	glutInit(&argc, argv);


//printf("lol\n");

DIR *d;
    struct dirent *dir;
    char dname[200]="C:/Users/Dell/Downloads/OpenGLProject/pixf"; //directory name
    d = opendir(dname);
    if (d)
    {
        int i=0;
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            char temp[200];
            char fname[200]="/";
            strcpy(temp,dname);
            strcat(fname,dir->d_name);
            strcat(temp,fname);
            printf("%s\n",temp);
            i++;
            if(i>=3){
                strcpy(img[i-3],temp);
                printf("%s\n",img[i-3]);
                total_img=(i-3);
            }

        }
        closedir(d);
    }

    FileToPixel(picNo);


    for(int i=0;i<100;i++){

    for(int j=0;pic[i][j]!='\0';j++){

      // printf("%c ",pic[i][j]);
    }


}





	glutInitWindowSize(1000, 750);
	glutInitWindowPosition(0, 0);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("First_Lab!");

	//codes for initialization
	init();

	//enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	//display callback function
	glutDisplayFunc(display);
    glutSpecialFunc(specialKeyListener);
	//what you want to do in the idle time (when no drawing is occurring)
	glutIdleFunc(animate);

	//The main loop of OpenGL
	glutMainLoop();
	return 0;
}
