

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#include <Vector.h>



#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//#include <glut.h>
#endif
//#include <glut.h>
#include<GL/glut.h>

using namespace std;
#define GROUND 1, 1, 1
#define PI 3.1416

//make a global variable -- for tracking the anglular position of camera
double cameraAngle,rot=0;			//in radian
double cameraAngleDelta;
double selfRot=0, uniRot=0,cyl_rotate=0,car_speed,cart_rotate;
double wheel_1_rotate=0,wheel_2_rotate=0,wheel_3_rotate=0,wheel_4_rotate=0;
double cameraHeight;
double cameraRadius;

double uniRotDelta;	//in degree
double speed;
GLUquadricObj *quadric;
double wheel_x,wheel_y;
int full_rot,move_key;
double _rot=0;
float i_i;

bool increasing,decreasing;


class Point3{
public:
	float x,y,z;

	void set(float dx,float dy, float dz)
	{
	  x=dx;
	  y=dy;
	  z=dz;
	}

	void set(Point3& p)
	{
	  x=p.x;
	  y=p.y;
	  z=p.z;

	}

	Point3(float xx,float yy,float zz)
	{
	  x=xx;
	  y=yy;
	  z=zz;

	}

	Point3()
	{
	  x=0;
	  y=0;
	  z=0;
	}

};

class Vector3{
  public:
    float x,y,z;

    void set(float dx,float dy, float dz)
    {
          x=dx;
          y=dy;
          z=dz;
    }
	void set(Vector3 const  &v)
	{
    	  x=v.x;
    	  y=v.y;
    	  z=v.z;

	}
    void flip()
	{
    	  x=-x;
    	  y=-y;
    	  z=-z;

	}
	void setDiff(Point3& a,Point3& b)
    {
         x=a.x-b.x;
    	 y=a.y-b.y;
    	 z=a.z-b.z;

    }
    void normalize()
    {
        double sizeSq = x*x+y*y+z*z;

    	float d=(float)sqrt(sizeSq);
    	x /= d;
    	y /= d;
    	z /= d;

    }

    Vector3(float xx,float yy,float zz)
	{
    	 x=xx;
    	 y=yy;
    	 z=zz;
	}

    Vector3(Vector3 const &v)
	{
    	  x=v.x;
    	  y=v.y;
    	  z=v.z;
	}
    Vector3()
	{
    	  x=0;
    	  y=0;
    	  z=0;
	}
	float dot(Vector3 b)
    {
          return x*b.x+y*b.y+z*b.z;
    }

    Vector3 cross(Vector3 b)
    {
          Vector3 to_ret= Vector3( float(y*b.z - z*b.y) , float(z*b.x - x*b.z) , float(x*b.y - y*b.x) );
          return to_ret;
    }
};

class Camera_class{


   public:
       Point3 eye, look,up;
	   Vector3 u,v,n;
	   double viewAngle,aspect,nearDist,farDist;
	   void setModelviewMatrix();
	   Camera_class();
	   void set(Point3 eye,Point3 look,Vector3 up);

	   void slide(float delU,float delV,float delN);

	   void roll(float angle);

	   void pitch(float angle);

	   void yaw(float angle);




};

Camera_class::Camera_class()
{

}

void Camera_class::setModelviewMatrix(void)
{

       float m[16];
		Vector3 eVec(eye.x,eye.y,eye.z);
		m[0]=u.x; m[4]=u.y;  m[8]=u.z; m[12]=-eVec.dot(u);

		m[1]=v.x; m[5]=v.y;  m[9]=v.z; m[13]=-eVec.dot(v);

		m[2]=n.x; m[6]=n.y;  m[10]=n.z; m[14]=-eVec.dot(n);

		m[3]=0;  m[7]=0;  m[11]=0; m[15]=1;

		glMatrixMode(GL_MODELVIEW);

		glLoadMatrixf(m);



}

void Camera_class::set(Point3 Eye,Point3 look,Vector3 up)
{
       eye.set(Eye);
	   n.set(eye.x-look.x,eye.y-look.y,eye.z-look.z);
	   u.set(up.cross(n));
	   n.normalize();
	   u.normalize();
	   v.set(n.cross(u));
	   //printf("\n%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t",eye.x,eye.y,eye.z,	cam.look.x,cam.look.y,cam.look.z,	cam.up.x,cam.up.y,cam.up.z);
	   //printf("\n%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f",eye.x,eye.y,eye.z,u.x,u.y,u.z,v.x,v.y,v.z,n.x,n.y,n.z);
       setModelviewMatrix();

}


void Camera_class::slide(float delU,float delV,float delN)
{
		eye.x += delU*u.x+ delV*v.x + delN*n.x;
		eye.y += delU*u.y+ delV*v.y + delN*n.y;
		eye.z += delU*u.z+ delV*v.z + delN*n.z;

		setModelviewMatrix();



}


void Camera_class::roll(float angle)
{

		float cs=cos(3.14159265/180*angle);
		float sn=sin(3.14159265/180*angle);

		Vector3 t(u);

		u.set(cs*t.x-sn*v.x,cs*t.y-sn*v.y,cs*t.z-sn*v.z);
		v.set(sn*t.x+cs*v.x,sn*t.y+cs*v.y,sn*t.z+cs*v.z);

        setModelviewMatrix();


}


void Camera_class::pitch(float angle)
{


	float cs = cos( 3.14159265/180 * angle ) ;
    float sn = sin( 3.14159265/180 * angle ) ;

    Vector3 t( v ) ;

    v.set( cs*t.x - sn*n.x, cs*t.y - sn*n.y, cs*t.z - sn*n.z ) ;
    n.set( sn*t.x + cs*n.x, sn*t.y + cs*n.y, sn*t.z + cs*n.z ) ;

	setModelviewMatrix() ;


}



void Camera_class::yaw(float angle)
{



	float cs = cos( 3.14159265/180 * angle ) ;
    float sn = sin( 3.14159265/180 * angle ) ;

    Vector3 t( n ) ;

    n.set( cs*t.x - sn*u.x, cs*t.y - sn*u.y, cs*t.z - sn*u.z ) ;
    u.set( sn*t.x + cs*u.x, sn*t.y + cs*u.y, sn*t.z + cs*u.z ) ;

	setModelviewMatrix() ;


}

Camera_class cam;

Point3 eye(0,250,280);

Point3 look(1,1,25);

Vector3 up(0,0,1);




void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(GROUND, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//load the correct matrix -- MODEL-VIEW matrix
	//glMatrixMode(GL_MODELVIEW);//********************

	//initialize the matrix
	//glLoadIdentity();//****************************


	//instead of CONSTANT information, we will define a circular path.
	//gluLookAt(120*cos(cameraAngle),120*sin(cameraAngle),15,	0,0,70,	0,0,1);
    //gluLookAt(10,30,10,	0,0,10,	0,0,1);
    //gluLookAt(0,1,200,	0,0,65,	0,0,1);
    //gluLookAt(-60,120,65,	0,0,65,	0,0,1);
    //gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,65,		0,0,1);
	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN


	//gluLookAt(cam.eye.x,cam.eye.y,cam.eye.z,	cam.look.x,cam.look.y,cam.look.z,	cam.up.x,cam.up.y,cam.up.z);

	//again select MODEL-VIEW
	//glMatrixMode(GL_MODELVIEW);//******************


	/****************************
	/ Add your objects from here
	****************************/
   //Rikshaw implimantation

  GLint i;
  GLfloat  inner_radius =50,outer_radius = 55,tooth_depth = .7 ,width =3.5;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;
  GLfloat teeth =80;
  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2.0;
  r2 = outer_radius + tooth_depth / 2.0;

  GLfloat  inner_radius1=48,outer_radius1 = 50,tooth_depth1 = .0 ,width1 =3.5;
  GLfloat r3 ,r4, r5;
  GLfloat angle1, da1;
  double rot;
  //GLfloat u, v, len;
 // GLfloat teeth1 =80;
  r3 = inner_radius1;
  r4 = outer_radius1 - tooth_depth1 / 3.0;

  da = 2.0 * M_PI  / teeth /4.0;


    glPushMatrix();
    {

                   glTranslatef(wheel_x,wheel_y,0);
                    glRotatef(full_rot,0,0,1);


 glPushMatrix();{
                   glTranslatef(-60,0,0);
                    glRotatef(90,0,0,1);


               //     glRotatef(rot,1.0,0.0,0.0);
 //the polygon base undernith the holder of the back wheel

 glColor3f(   0.0,  0.0, 0.0 );
   glPushMatrix();{

                   glTranslatef(20,-180,-35);
                  glRotatef(-360,1.0,0.0,0.0);
    glBegin(GL_POLYGON);  //black

    glVertex3f(  50, -4, 2 );//+
    glVertex3f(  50,  4, 2 );//+
    glVertex3f( -50,  4, 2 );//+
    glVertex3f( -50, -4, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 50, -4,  2  );//+
  glVertex3f( 50,  4,  2 );//+
  glVertex3f( 50,  4, -2 );//-
  glVertex3f( 50, -4, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -50, 4, -2 );  //minus
  glVertex3f( -50,-4, -2 );  //minus
  glVertex3f(  50,-4, -2 );//-
  glVertex3f(  50, 4, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -4,  2 );
  glVertex3f( -50,  4,  2 );
  glVertex3f( -50,  4, -2 );
  glVertex3f( -50, -4, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  4,  2 );
  glVertex3f(  50,  4, -2 );
  glVertex3f( -50,  4, -2 );
  glVertex3f( -50,  4,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -4, -2 );//-
  glVertex3f(  50, -4,  2 );
  glVertex3f( -50, -4,  2 );
  glVertex3f( -50, -4, -2 );//-
  glEnd();

//}glPopMatrix();
  glFlush();

   glColor3f(   0.0,  0.0, 0.0 );
  //base structure
  glPushMatrix();
  {
                 glTranslatef(46,28,0);

   glBegin(GL_POLYGON);  //black
  //  glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -25, 2 );//+
    glVertex3f(  4,  25, 2 );//+
    glVertex3f( -4,  25, 2 );//+
    glVertex3f( -4, -25, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -25,  2  );//+
  glVertex3f( 4,  25,  2 );//+
  glVertex3f( 4,  25, -2 );//-
  glVertex3f( 4, -25, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 25, -2 );  //minus
  glVertex3f( -4,-25, -2 );  //minus
  glVertex3f(  4,-25, -2 );//-
  glVertex3f(  4, 25, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -25,  2 );
  glVertex3f( -4,  25,  2 );
  glVertex3f( -4,  25, -2 );
  glVertex3f( -4, -25, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  25,  2 );
  glVertex3f(  4,  25, -2 );
  glVertex3f( -4,  25, -2 );
  glVertex3f( -4,  25,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -25, -2 );//-
  glVertex3f(  4, -25,  2 );
  glVertex3f( -4, -25,  2 );
  glVertex3f( -4, -25, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();


   //base structure  2nd
   glColor3f(   0.0,  0.0, 0.0 );
  glPushMatrix();
  {
                 glTranslatef(-46,28,0);

   glBegin(GL_POLYGON);  //black

    glVertex3f(  4, -25, 2 );//+
    glVertex3f(  4,  25, 2 );//+
    glVertex3f( -4,  25, 2 );//+
    glVertex3f( -4, -25, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -25,  2  );//+
  glVertex3f( 4,  25,  2 );//+
  glVertex3f( 4,  25, -2 );//-
  glVertex3f( 4, -25, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 25, -2 );  //minus
  glVertex3f( -4,-25, -2 );  //minus
  glVertex3f(  4,-25, -2 );//-
  glVertex3f(  4, 25, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -25,  2 );
  glVertex3f( -4,  25,  2 );
  glVertex3f( -4,  25, -2 );
  glVertex3f( -4, -25, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  25,  2 );
  glVertex3f(  4,  25, -2 );
  glVertex3f( -4,  25, -2 );
  glVertex3f( -4,  25,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -25, -2 );//-
  glVertex3f(  4, -25,  2 );
  glVertex3f( -4, -25,  2 );
  glVertex3f( -4, -25, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();

  //triangle shape
  //*******************************left side
  glColor3f(   0.0,  0.0, 0.0 );
  glPushMatrix();
  {
                 glTranslatef(24,82,0);
                 glRotatef(35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  4, -40, 2 );//+
    glVertex3f(  4,  40, 2 );//+
    glVertex3f( -4,  40, 2 );//+
    glVertex3f( -4, -40, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -40,  2  );//+
  glVertex3f( 4,  40,  2 );//+
  glVertex3f( 4,  40, -2 );//-
  glVertex3f( 4, -40, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 40, -2 );  //minus
  glVertex3f( -4,-40, -2 );  //minus
  glVertex3f(  4,-40, -2 );//-
  glVertex3f(  4, 40, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -40,  2 );
  glVertex3f( -4,  40,  2 );
  glVertex3f( -4,  40, -2 );
  glVertex3f( -4, -40, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  40,  2 );
  glVertex3f(  4,  40, -2 );
  glVertex3f( -4,  40, -2 );
  glVertex3f( -4,  40,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -40, -2 );//-
  glVertex3f(  4, -40,  2 );
  glVertex3f( -4, -40,  2 );
  glVertex3f( -4, -40, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();



  //*************************************************another ine


  glColor3f(   0.0,  0.0, 0.0 );
   glPushMatrix();
  {
                 glTranslatef(-24,82,0);
                 glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  4, -40, 2 );//+
    glVertex3f(  4,  40, 2 );//+
    glVertex3f( -4,  40, 2 );//+
    glVertex3f( -4, -40, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -40,  2  );//+
  glVertex3f( 4,  40,  2 );//+
  glVertex3f( 4,  40, -2 );//-
  glVertex3f( 4, -40, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 40, -2 );  //minus
  glVertex3f( -4,-40, -2 );  //minus
  glVertex3f(  4,-40, -2 );//-
  glVertex3f(  4, 40, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -40,  2 );
  glVertex3f( -4,  40,  2 );
  glVertex3f( -4,  40, -2 );
  glVertex3f( -4, -40, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  40,  2 );
  glVertex3f(  4,  40, -2 );
  glVertex3f( -4,  40, -2 );
  glVertex3f( -4,  40,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -40, -2 );//-
  glVertex3f(  4, -40,  2 );
  glVertex3f( -4, -40,  2 );
  glVertex3f( -4, -40, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //base 3,front tire holder

  glColor3f(   0.0,  0.0, 0.0 );
    glPushMatrix();
  {
                 glTranslatef(0,135,0);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  6, -24, 3 );//+
    glVertex3f(  6,  24, 3 );//+
    glVertex3f( -6,  24, 3 );//+
    glVertex3f( -6, -24, 3 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 6, -24,  3  );//+
  glVertex3f( 6,  24,  3 );//+
  glVertex3f( 6,  24, -3 );//-
  glVertex3f( 6, -24, -3 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -6, 24, -3 );  //minus
  glVertex3f( -6,-24, -3 );  //minus
  glVertex3f(  6,-24, -3 );//-
  glVertex3f(  6, 24, -3 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -6, -24,  3 );
  glVertex3f( -6,  24,  3 );
  glVertex3f( -6,  24, -3 );
  glVertex3f( -6, -24, -3 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  6,  24,  3 );
  glVertex3f(  6,  24, -3 );
  glVertex3f( -6,  24, -3 );
  glVertex3f( -6,  24,  3 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  6, -24, -3 );//-
  glVertex3f(  6, -24,  3 );
  glVertex3f( -6, -24,  3 );
  glVertex3f( -6, -24, -3 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//base which holds the seat abd hood

glColor3f(   0.6,  0.5, 0.5 );

  glPushMatrix();
  {

                 glTranslatef(-46,22,22);

   glBegin(GL_POLYGON);  //blue
  //  glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -10, 3);//+
    glVertex3f(  4,  10, 3 );//+
    glVertex3f( -4,  10, 3 );//+
    glVertex3f( -4, -10, 3 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -10,  3  );//+
  glVertex3f( 4,  10,  3 );//+
  glVertex3f( 4,  10, -3 );//-
  glVertex3f( 4, -10, -3 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 10, -3 );  //minus
  glVertex3f( -4,-10, -3 );  //minus
  glVertex3f(  4,-10, -3 );//-
  glVertex3f(  4, 10, -3 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4,  10,  3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4, -10, -3 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  10,  3 );
  glVertex3f(  4,  10, -3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4,  10,  3 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -10, -3 );//-
  glVertex3f(  4, -10,  3 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4, -10, -3 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//bottom on base  left
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(46,22,22);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -10, 3);//+
    glVertex3f(  4,  10, 3 );//+
    glVertex3f( -4,  10, 3 );//+
    glVertex3f( -4, -10, 3 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -10,  3  );//+
  glVertex3f( 4,  10,  3 );//+
  glVertex3f( 4,  10, -3 );//-
  glVertex3f( 4, -10, -3 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 10, -3 );  //minus
  glVertex3f( -4,-10, -3 );  //minus
  glVertex3f(  4,-10, -3 );//-
  glVertex3f(  4, 10, -3 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4,  10,  3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4, -10, -3 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  10,  3 );
  glVertex3f(  4,  10, -3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4,  10,  3 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -10, -3 );//-
  glVertex3f(  4, -10,  3 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4, -10, -3 );//-
  glEnd();
}glPopMatrix();
  glFlush();



  //bottom base right
  glColor3f(   0.6,  0.5, 0.5 );

  glPushMatrix();
  {
                 glTranslatef(-46,22,5);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -10, 3);//+
    glVertex3f(  4,  10, 3 );//+
    glVertex3f( -4,  10, 3 );//+
    glVertex3f( -4, -10, 3 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -10,  3  );//+
  glVertex3f( 4,  10,  3 );//+
  glVertex3f( 4,  10, -3 );//-
  glVertex3f( 4, -10, -3 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 10, -3 );  //minus
  glVertex3f( -4,-10, -3 );  //minus
  glVertex3f(  4,-10, -3 );//-
  glVertex3f(  4, 10, -3 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4,  10,  3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4, -10, -3 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  10,  3 );
  glVertex3f(  4,  10, -3 );
  glVertex3f( -4,  10, -3 );
  glVertex3f( -4,  10,  3 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -10, -3 );//-
  glVertex3f(  4, -10,  3 );
  glVertex3f( -4, -10,  3 );
  glVertex3f( -4, -10, -3 );//-
  glEnd();
}glPopMatrix();
  glFlush();

   //bottom right
   glColor3f(   0.6,  0.5, 0.5 );

   glPushMatrix();
  {
                 glTranslatef(46,22,5);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -10, 4);//+
    glVertex3f(  4,  10, 4 );//+
    glVertex3f( -4,  10, 4 );//+
    glVertex3f( -4, -10, 4 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -10,  4  );//+
  glVertex3f( 4,  10,  4 );//+
  glVertex3f( 4,  10, -4 );//-
  glVertex3f( 4, -10, -4 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 10, -4 );  //minus
  glVertex3f( -4,-10, -4 );  //minus
  glVertex3f(  4,-10, -4 );//-
  glVertex3f(  4, 10, -4 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -10,  4 );
  glVertex3f( -4,  10,  4 );
  glVertex3f( -4,  10, -4 );
  glVertex3f( -4, -10, -4 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  10,  4 );
  glVertex3f(  4,  10, -4 );
  glVertex3f( -4,  10, -4 );
  glVertex3f( -4,  10,  4 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -10, -4 );//-
  glVertex3f(  4, -10,  4 );
  glVertex3f( -4, -10,  4 );
  glVertex3f( -4, -10, -4 );//-
  glEnd();

}glPopMatrix();
  glFlush();

//bottom right
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(-46,29,12);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -3, 7);//+
    glVertex3f(  4,  3, 7 );//+
    glVertex3f( -4,  3, 7 );//+
    glVertex3f( -4, -3, 7 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -3,  7  );//+
  glVertex3f( 4,  3,  7 );//+
  glVertex3f( 4,  3, -7 );//-
  glVertex3f( 4, -3, -7 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 3, -7 );  //minus
  glVertex3f( -4,-3, -7 );  //minus
  glVertex3f(  4,-3, -7 );//-
  glVertex3f(  4, 3, -7 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4,  3,  7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4, -3, -7 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  3,  7 );
  glVertex3f(  4,  3, -7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4,  3,  7 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -3, -7 );//-
  glVertex3f(  4, -3,  7 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4, -3, -7 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//bottom right,behind
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(-46,15,12);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -3, 7);//+
    glVertex3f(  4,  3, 7 );//+
    glVertex3f( -4,  3, 7 );//+
    glVertex3f( -4, -3, 7 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -3,  7  );//+
  glVertex3f( 4,  3,  7 );//+
  glVertex3f( 4,  3, -7 );//-
  glVertex3f( 4, -3, -7 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 3, -7 );  //minus
  glVertex3f( -4,-3, -7 );  //minus
  glVertex3f(  4,-3, -7 );//-
  glVertex3f(  4, 3, -7 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4,  3,  7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4, -3, -7 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  3,  7 );
  glVertex3f(  4,  3, -7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4,  3,  7 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -3, -7 );//-
  glVertex3f(  4, -3,  7 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4, -3, -7 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//bottom ,left,behind
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(46,15,12);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -3, 7);//+
    glVertex3f(  4,  3, 7 );//+
    glVertex3f( -4,  3, 7 );//+
    glVertex3f( -4, -3, 7 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -3,  7  );//+
  glVertex3f( 4,  3,  7 );//+
  glVertex3f( 4,  3, -7 );//-
  glVertex3f( 4, -3, -7 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 3, -7 );  //minus
  glVertex3f( -4,-3, -7 );  //minus
  glVertex3f(  4,-3, -7 );//-
  glVertex3f(  4, 3, -7 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4,  3,  7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4, -3, -7 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  3,  7 );
  glVertex3f(  4,  3, -7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4,  3,  7 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -3, -7 );//-
  glVertex3f(  4, -3,  7 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4, -3, -7 );//-
  glEnd();
}glPopMatrix();
  glFlush();

//bottom left,front
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(46,29,12);
              //   glRotatef(-35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   1.0,  0.0, 1.0 );
    glVertex3f(  4, -3, 7);//+
    glVertex3f(  4,  3, 7 );//+
    glVertex3f( -4,  3, 7 );//+
    glVertex3f( -4, -3, 7 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -3,  7  );//+
  glVertex3f( 4,  3,  7 );//+
  glVertex3f( 4,  3, -7 );//-
  glVertex3f( 4, -3, -7 );//-
  glEnd();

  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 3, -7 );  //minus
  glVertex3f( -4,-3, -7 );  //minus
  glVertex3f(  4,-3, -7 );//-
  glVertex3f(  4, 3, -7 );//-
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4,  3,  7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4, -3, -7 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  3,  7 );
  glVertex3f(  4,  3, -7 );
  glVertex3f( -4,  3, -7 );
  glVertex3f( -4,  3,  7 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   4.0,  0.0,  0.0 );
  glVertex3f(  4, -3, -7 );//-
  glVertex3f(  4, -3,  7 );
  glVertex3f( -4, -3,  7 );
  glVertex3f( -4, -3, -7 );//-
  glEnd();
}glPopMatrix();
  glFlush();


 ///rest of the code goes here
 //*******************holder of  hood

 glColor3f(   0.6,  0.5, 0.5 );

 glPushMatrix();
  {
                 glTranslatef(46,25,25);
            //     glRotatef(35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -25, 1 );//+
    glVertex3f(  4,  25, 1 );//+
    glVertex3f( -4,  25, 1 );//+
    glVertex3f( -4, -25, 1 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -25,  1  );//+
  glVertex3f( 4,  25,  1 );//+
  glVertex3f( 4,  25, -1 );//-
  glVertex3f( 4, -25, -1 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 25, -1 );  //minus
  glVertex3f( -4,-25, -1 );  //minus
  glVertex3f(  4,-25, -1 );//-
  glVertex3f(  4, 25, -1 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -25,  1 );
  glVertex3f( -4,  25,  1 );
  glVertex3f( -4,  25, -1 );
  glVertex3f( -4, -25, -1 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  25,  1 );
  glVertex3f(  4,  25, -1 );
  glVertex3f( -4,  25, -1 );
  glVertex3f( -4,  25,  1 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -25, -1 );//-
  glVertex3f(  4, -25,  1 );
  glVertex3f( -4, -25,  1 );
  glVertex3f( -4, -25, -1 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //*************************************************


 glColor3f(   0.6,  0.5, 0.5 );

 glPushMatrix();
  {
                 glTranslatef(46,-5,33);
                 glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //steel behind wheel
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();

 //***********************************************************************

  glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(46,55,33);
                 glRotatef(-33,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //******************************************************************
  glColor3f(   0.6,  0.5, 0.5 );

  glPushMatrix();
  {
                 glTranslatef(46,54,48);
                 glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();

 //***********************************************************************
  //do not change
  glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(46,-5,48);
                 glRotatef(-33,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();



 //*******************************************************************
 glColor3f(   0.6,  0.5, 0.5 );

 glPushMatrix();
  {
                 glTranslatef(46,25,56);
            //     glRotatef(35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -24, 1 );//+
    glVertex3f(  4,  24, 1 );//+
    glVertex3f( -4,  24, 1 );//+
    glVertex3f( -4, -24, 1 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -24,  1  );//+
  glVertex3f( 4,  24,  1 );//+
  glVertex3f( 4,  24, -1 );//-
  glVertex3f( 4, -24, -1 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 24, -1 );  //minus
  glVertex3f( -4,-24, -1 );  //minus
  glVertex3f(  4,-24, -1 );//-
  glVertex3f(  4, 24, -1 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -24,  1 );
  glVertex3f( -4,  24,  1 );
  glVertex3f( -4,  24, -1 );
  glVertex3f( -4, -24, -1 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  24,  1 );
  glVertex3f(  4,  24, -1 );
  glVertex3f( -4,  24, -1 );
  glVertex3f( -4,  24,  1 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -24, -1 );//-
  glVertex3f(  4, -24,  1 );
  glVertex3f( -4, -24,  1 );
  glVertex3f( -4, -24, -1 );//-
  glEnd();
}glPopMatrix();
  glFlush();



    //************************************************MOU
  glColor3f(   0.6,  0.5, 0.5 );

    glPushMatrix();
  {
                 glTranslatef(-46,25,25);
            //     glRotatef(35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -25, 1 );//+
    glVertex3f(  4,  25, 1 );//+
    glVertex3f( -4,  25, 1 );//+
    glVertex3f( -4, -25, 1 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -25,  1  );//+
  glVertex3f( 4,  25,  1 );//+
  glVertex3f( 4,  25, -1 );//-
  glVertex3f( 4, -25, -1 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 25, -1 );  //minus
  glVertex3f( -4,-25, -1 );  //minus
  glVertex3f(  4,-25, -1 );//-
  glVertex3f(  4, 25, -1 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -25,  1 );
  glVertex3f( -4,  25,  1 );
  glVertex3f( -4,  25, -1 );
  glVertex3f( -4, -25, -1 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  25,  1 );
  glVertex3f(  4,  25, -1 );
  glVertex3f( -4,  25, -1 );
  glVertex3f( -4,  25,  1 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -25, -1 );//-
  glVertex3f(  4, -25,  1 );
  glVertex3f( -4, -25,  1 );
  glVertex3f( -4, -25, -1 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //*************************************************


  glColor3f(   0.6,  0.5, 0.5 );

 glPushMatrix();
  {
                 glTranslatef(-46,-5,33);
                 glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
///  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();

 //***********************************************************************
glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(-46,55,33);
                 glRotatef(-33,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //******************************************************************
  glColor3f(   0.6,  0.5, 0.5 );

  glPushMatrix();
  {
                 glTranslatef(-46,54,48);
                 glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();

 //***********************************************************************
  //do not change

  glColor3f(   0.6,  0.5, 0.5 );

glPushMatrix();
  {
                 glTranslatef(-46,-5,48);
                 glRotatef(-33,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -1, 10 );//+
    glVertex3f(  4,  1, 10 );//+
    glVertex3f( -4,  1, 10 );//+
    glVertex3f( -4, -1, 10 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -1,  10  );//+
  glVertex3f( 4,  1,  10 );//+
  glVertex3f( 4,  1, -10 );//-
  glVertex3f( 4, -1, -10 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 1, -10 );  //minus
  glVertex3f( -4,-1, -10 );  //minus
  glVertex3f(  4,-1, -10 );//-
  glVertex3f(  4, 1, -10 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4,  1,  10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4, -1, -10 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  1,  10 );
  glVertex3f(  4,  1, -10 );
  glVertex3f( -4,  1, -10 );
  glVertex3f( -4,  1,  10 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -1, -10 );//-
  glVertex3f(  4, -1,  10 );
  glVertex3f( -4, -1,  10 );
  glVertex3f( -4, -1, -10 );//-
  glEnd();
}glPopMatrix();
  glFlush();



 //*******************************************************************
 glColor3f(   0.6,  0.5, 0.5 );

 glPushMatrix();
  {
                 glTranslatef(-46,25,56);
            //     glRotatef(35,0.0,0.0,1.0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -24, 1 );//+
    glVertex3f(  4,  24, 1 );//+
    glVertex3f( -4,  24, 1 );//+
    glVertex3f( -4, -24, 1 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -24,  1  );//+
  glVertex3f( 4,  24,  1 );//+
  glVertex3f( 4,  24, -1 );//-
  glVertex3f( 4, -24, -1 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  1.0,  1.0 );
  glVertex3f( -4, 24, -1 );  //minus
  glVertex3f( -4,-24, -1 );  //minus
  glVertex3f(  4,-24, -1 );//-
  glVertex3f(  4, 24, -1 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -24,  1 );
  glVertex3f( -4,  24,  1 );
  glVertex3f( -4,  24, -1 );
  glVertex3f( -4, -24, -1 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  24,  1 );
  glVertex3f(  4,  24, -1 );
  glVertex3f( -4,  24, -1 );
  glVertex3f( -4,  24,  1 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -24, -1 );//-
  glVertex3f(  4, -24,  1 );
  glVertex3f( -4, -24,  1 );
  glVertex3f( -4, -24, -1 );//-
  glEnd();
}glPopMatrix();
  glFlush();
///////////////////////////right pa
glColor3f(   0.6,  0.7, 0.6 );

glPushMatrix();
  {
                 glTranslatef(-46,25,60);
                // glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -4, 5 );//+
    glVertex3f(  4,  4, 5 );//+
    glVertex3f( -4,  4, 5 );//+
    glVertex3f( -4, -4, 5 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -4,   5 );//+
  glVertex3f( 4,  4,  5 );//+
  glVertex3f( 4, 4, -5 );//-
  glVertex3f( 4, -4, -5 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -4, 4, -5 );  //minus
  glVertex3f( -4,-4, -5 );  //minus
  glVertex3f(  4,-4, -5 );//-
  glVertex3f(  4, 4, -5 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -4,  5 );
  glVertex3f( -4,  4,  5 );
  glVertex3f( -4,  4, -5 );
  glVertex3f( -4, -4, -5 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  4,  5 );
  glVertex3f(  4,  4, -5 );
  glVertex3f( -4,  4, -5 );
  glVertex3f( -4,  4,  5 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -4, -5 );//-
  glVertex3f(  4, -4,  5 );
  glVertex3f( -4, -4,  5 );
  glVertex3f( -4, -4, -5 );//-
  glEnd();
}glPopMatrix();
  glFlush();



////////////////////left pa
glColor3f(   0.6,  0.7, 0.6 );

glPushMatrix();
  {
                 glTranslatef(46,25,60);
                // glRotatef(35,1.0,0.0,0.0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0.0,  0.0, 1.0 );
    glVertex3f(  4, -4, 5 );//+
    glVertex3f(  4,  4, 5 );//+
    glVertex3f( -4,  4, 5 );//+
    glVertex3f( -4, -4, 5 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f( 4, -4,   5 );//+
  glVertex3f( 4,  4,  5 );//+
  glVertex3f( 4, 4, -5 );//-
  glVertex3f( 4, -4, -5 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -4, 4, -5 );  //minus
  glVertex3f( -4,-4, -5 );  //minus
  glVertex3f(  4,-4, -5 );//-
  glVertex3f(  4, 4, -5 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -4, -4,  5 );
  glVertex3f( -4,  4,  5 );
  glVertex3f( -4,  4, -5 );
  glVertex3f( -4, -4, -5 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  4,  4,  5 );
  glVertex3f(  4,  4, -5 );
  glVertex3f( -4,  4, -5 );
  glVertex3f( -4,  4,  5 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  4, -4, -5 );//-
  glVertex3f(  4, -4,  5 );
  glVertex3f( -4, -4,  5 );
  glVertex3f( -4, -4, -5 );//-
  glEnd();
}glPopMatrix();
  glFlush();


///////////////////////////padani

glColor3f(   0.3,  0.7,0.8);
glPushMatrix();
  {
                 glTranslatef(0,80,60);
                 glRotatef(10,-1,0,0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  50, -25, 2 );//+
    glVertex3f(  50,  25, 2 );//+
    glVertex3f( -50,  25, 2 );//+
    glVertex3f( -50, -25, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  //glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f(  50, -25,   2 );//+
  glVertex3f( 50,  25,  2 );//+
  glVertex3f( 50, 25, -2);//-
  glVertex3f( 50, -25, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 25, -2 );  //minus
  glVertex3f( -50,-25, -2 );  //minus
  glVertex3f(  50,-25, -2 );//-
  glVertex3f(  50, 25, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -25,  2 );
  glVertex3f( -50,  25,  2 );
  glVertex3f( -50,  25, -2 );
  glVertex3f( -50, -25, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  25,  2 );
  glVertex3f(  50,  25, -2 );
  glVertex3f( -50,  25, -2 );
  glVertex3f( -50,  25,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -25, -2 );//-
  glVertex3f(  50, -25,  2 );
  glVertex3f( -50, 25,  2 );
  glVertex3f( -50, -25, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();
///////////////////////////////////curve
glColor3f(   0.3,  0.7, 0.8 );
glPushMatrix();
  {
                 glTranslatef(0,55,64);
                 glRotatef(15,-2,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   1,1, 0 );
    glVertex3f(  50, -6, 3 );//+
    glVertex3f(  50,  6, 3 );//+
    glVertex3f( -50,  6, 3 );//+
    glVertex3f( -50, -6, 3 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f(  50, -6,   3 );//+
  glVertex3f( 50,  6,  3 );//+
  glVertex3f( 50, 6, -3);//-
  glVertex3f( 50, -6, -3 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
 // glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 6, -3 );  //minus
  glVertex3f( -50,-6, -3 );  //minus
  glVertex3f(  50,-6, -3 );//-
  glVertex3f(  50, 6, -3 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -6,  3 );
  glVertex3f( -50,  6,  3 );
  glVertex3f( -50,  6, -3 );
  glVertex3f( -50, -6, -3 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  6,  3 );
  glVertex3f(  50,  6, -3 );
  glVertex3f( -50,  6, -3 );
  glVertex3f( -50,  6,  3 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -6, -3 );//-
  glVertex3f(  50, -6,  3 );
  glVertex3f( -50, 6,  3 );
  glVertex3f( -50, -6, -3 );//-
  glEnd();
}glPopMatrix();
  glFlush();


    ///////////////////////////////////curve1,sit
    glColor3f(   0.8,0.8,0.8);
    glPushMatrix();
  {
                 glTranslatef(0,41,80);
                 glRotatef(5,-1,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   .1,.1, 0 );
    glVertex3f(  50, -14, 16 );//+
    glVertex3f(  50,  14, 16 );//+
    glVertex3f( -50,  14, 16 );//+
    glVertex3f( -50, -14, 16 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   .1, .1, 0.1 );
  glVertex3f(  50, -14, 16 );//+
  glVertex3f( 50,  14,  16 );//+
  glVertex3f( 50, 14,  -16);//-
  glVertex3f( 50, -14, -16 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  //glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 14, -16 );  //minus
  glVertex3f( -50,-14, -16 );  //minus
  glVertex3f(  50,-14, -16 );//-
  glVertex3f(  50, 14, -16 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -14,  16 );
  glVertex3f( -50,  14,  16 );
  glVertex3f( -50,  14, -16 );
  glVertex3f( -50, -14, -16 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  14,  16 );
  glVertex3f(  50,  14, -16 );
  glVertex3f( -50,  14, -16 );
  glVertex3f( -50,  14,  16 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -14, -16 );//-
  glVertex3f(  50, -14,  16 );
  glVertex3f( -50, 14,   16 );
  glVertex3f( -50, -14, -16 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  //////////////////////////////////////////////////////////////

   ///////////////////////////////////curve1,sit
    glColor3f(  0,1,1);
    glPushMatrix();
  {
                 glTranslatef(0,43,103);
                 glRotatef(5,-1,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   .1,.1, 0 );
    glVertex3f(  50, -14, 8 );//+
    glVertex3f(  50,  14, 8 );//+
    glVertex3f( -50,  14, 8 );//+
    glVertex3f( -50, -14, 8 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   .1, .1, 0.1 );
  glVertex3f(  50, -14, 8 );//+
  glVertex3f( 50,  14,  8 );//+
  glVertex3f( 50, 14,  -8);//-
  glVertex3f( 50, -14, -8 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  //glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 14, -8 );  //minus
  glVertex3f( -50,-14, -8 );  //minus
  glVertex3f(  50,-14, -8 );//-
  glVertex3f(  50, 14, -8 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -14,  8 );
  glVertex3f( -50,  14,  8 );
  glVertex3f( -50,  14, -8 );
  glVertex3f( -50, -14, -8 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  14,  8 );
  glVertex3f(  50,  14, -8 );
  glVertex3f( -50,  14, -8 );
  glVertex3f( -50,  14,  8 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -14, -8 );//-
  glVertex3f(  50, -14,  8 );
  glVertex3f( -50, 14,   8 );
  glVertex3f( -50, -14, -8 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//////////////////////////////////////////////////////////////////////////////

    glColor3f(  0.8,0.8,0.8);
    glPushMatrix();
  {
                 glTranslatef(0,23,85);
                 glRotatef(5,-1,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   .1,.1, 0 );
    glVertex3f(  50, -5, 20 );//+
    glVertex3f(  50,  5, 20 );//+
    glVertex3f( -50,  5, 20 );//+
    glVertex3f( -50, -5, 20 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   .1, .1, 0.1 );
  glVertex3f(  50, -5, 20 );//+
  glVertex3f( 50,  5,  20 );//+
  glVertex3f( 50, 5,  -20);//-
  glVertex3f( 50, -5, -20 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  //glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 5, -20 );  //minus
  glVertex3f( -50,-5, -20 );  //minus
  glVertex3f(  50,-5, -20 );//-
  glVertex3f(  50, 5, -20 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -5,  20 );
  glVertex3f( -50,  5,  20 );
  glVertex3f( -50,  5, -20 );
  glVertex3f( -50, -5, -20 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  5,  20 );
  glVertex3f(  50,  5, -20 );
  glVertex3f( -50,  5, -20 );
  glVertex3f( -50,  5,  20 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -5, -20 );//-
  glVertex3f(  50, -5,  20 );
  glVertex3f( -50,  5,  20 );
  glVertex3f( -50, -5, -20 );//-
  glEnd();
}glPopMatrix();
  glFlush();

///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

    glColor3f(  1,0,0);
    glPushMatrix();
  {
                 glTranslatef(0,26,119);
                 glRotatef(5,-1,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   .1,.1, 0 );
    glVertex3f(  50, -5, 15 );//+
    glVertex3f(  50,  5, 15 );//+
    glVertex3f( -50,  5, 15);//+
    glVertex3f( -50, -5, 15 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   .1, .1, 0.1 );
  glVertex3f(  50, -5, 15 );//+
  glVertex3f( 50,  5,  15 );//+
  glVertex3f( 50, 5,  -15);//-
  glVertex3f( 50, -5, -15 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  //glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 5, -15 );  //minus
  glVertex3f( -50,-5, -15 );  //minus
  glVertex3f(  50,-5, -15 );//-
  glVertex3f(  50, 5, -15 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -5,  15 );
  glVertex3f( -50,  5,  15 );
  glVertex3f( -50,  5, -15 );
  glVertex3f( -50, -5, -15 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  5,  15 );
  glVertex3f(  50,  5, -15 );
  glVertex3f( -50,  5, -15 );
  glVertex3f( -50,  5,  15 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -5, -15 );//-
  glVertex3f(  50, -5,  15 );
  glVertex3f( -50,  5,  15 );
  glVertex3f( -50, -5, -15 );//-
  glEnd();
}glPopMatrix();
  glFlush();





////////////////////////////////////////////////////////////////////////////


    glColor3f(  0.8,0.8,0.8);
    glPushMatrix();
  {
                 glTranslatef(0,19,100);
                 glRotatef(5,-1,0,0);

   glBegin(GL_POLYGON);  //blue
   // glColor3f(   .1,.1, 0 );
    glVertex3f(  50, -1, 35 );//+
    glVertex3f(  50,  1.5, 35 );//+
    glVertex3f( -50,  1.5, 35);//+
    glVertex3f( -50, -1, 35 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
 // glColor3f(   .1, .1, 0.1 );
  glVertex3f(  50, -1, 35 );//+
  glVertex3f( 50,  1,  35 );//+
  glVertex3f( 50, 1,  -35);//-
  glVertex3f( 50, -1, -35 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  //glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 1, -35 );  //minus
  glVertex3f( -50,-1, -35 );  //minus
  glVertex3f(  50,-1, -35 );//-
  glVertex3f(  50, 1, -35 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -1,  35 );
  glVertex3f( -50,  1,  35 );
  glVertex3f( -50,  1, -35 );
  glVertex3f( -50, -1, -35 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  1,  35 );
  glVertex3f(  50,  1, -35 );
  glVertex3f( -50,  1, -35 );
  glVertex3f( -50,  1,  35 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -1, -35 );//-
  glVertex3f(  50, -1,  35 );
  glVertex3f( -50,  1,  35 );
  glVertex3f( -50, -1, -35 );//-
  glEnd();
}glPopMatrix();
  glFlush();

/////////////////////////////////////////////////////////////////////////////////


glColor3f(   0.7,0.8,0.8);
glPushMatrix();
  {
                 glTranslatef(0,103,63);
              //   glRotatef(10,-1,0,0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  50, -2, 6 );//+
    glVertex3f(  50,  2, 6 );//+
    glVertex3f( -50,  2, 6 );//+
    glVertex3f( -50, -2, 6 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  //glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f(  50, -2, 6 );//+
  glVertex3f( 50,  2,  6 );//+
  glVertex3f( 50, 2,  -6);//-
  glVertex3f( 50, -2, -6 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -50, 2, -6 );  //minus
  glVertex3f( -50,-2, -6 );  //minus
  glVertex3f(  50,-2, -6 );//-
  glVertex3f(  50, 2, -6 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50, -2,  6 );
  glVertex3f( -50,  2,  6 );
  glVertex3f( -50,  2, -6 );
  glVertex3f( -50, -2, -6 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  50,  2,  6 );
  glVertex3f(  50,  2, -6 );
  glVertex3f( -50,  2, -6 );
  glVertex3f( -50,  2,  6 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  50, -2, -6 );//-
  glVertex3f(  50, -2,  6 );
  glVertex3f( -50, 2,   6 );
  glVertex3f( -50, -2, -6 );//-
  glEnd();
}glPopMatrix();
  glFlush();



/////////////////////////////////////////////////////////////////////////////////


glColor3f( 0.7,0.8,0.8);
glPushMatrix();
  {
                 glTranslatef(-48,79,68);
                 glRotatef(12,-1,0,0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  2, -26, 6 );//+
    glVertex3f(  2,  26, 6 );//+
    glVertex3f( -2,  26, 6 );//+
    glVertex3f( -2, -26, 6 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  //glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f(  2, -26, 6 );//+
  glVertex3f( 2,  26,  6 );//+
  glVertex3f( 2, 26,  -6);//-
  glVertex3f( 2, -26, -6 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -2, 26, -6 );  //minus
  glVertex3f( -2,-26, -6 );  //minus
  glVertex3f(  2,-26, -6 );//-
  glVertex3f(  2, 26, -6 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -2, -26,  6 );
  glVertex3f( -2,  26,  6 );
  glVertex3f( -2,  26, -6 );
  glVertex3f( -2, -26, -6 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  2,  26,  6 );
  glVertex3f(  2,  26, -6 );
  glVertex3f( -2,  26, -6 );
  glVertex3f( -2,  26,  6 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  2, -26, -6 );//-
  glVertex3f(  2, -26,  6 );
  glVertex3f( -2, 26,   6 );
  glVertex3f( -2, -26, -6 );//-
  glEnd();
}glPopMatrix();
  glFlush();



/////////////////////////////////////////////////////////////////////////////////


glColor3f( 0.7,0.8,0.8);
glPushMatrix();
  {
                 glTranslatef(48,79,68);
                 glRotatef(12,-1,0,0);

   glBegin(GL_POLYGON);  //blue

    glVertex3f(  2, -26, 6 );//+
    glVertex3f(  2,  26, 6 );//+
    glVertex3f( -2,  26, 6 );//+
    glVertex3f( -2, -26, 6 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  //glColor3f(   1.0, 1.0, 0.0 );
  glVertex3f(  2, -26, 6 );//+
  glVertex3f( 2,  26,  6 );//+
  glVertex3f( 2, 26,  -6);//-
  glVertex3f( 2, -26, -6 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
 // glColor3f(  1.0,  4.0,  1.0 );
  glVertex3f( -2, 26, -6 );  //minus
  glVertex3f( -2,-26, -6 );  //minus
  glVertex3f(  2,-26, -6 );//-
  glVertex3f(  2, 26, -6 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -2, -26,  6 );
  glVertex3f( -2,  26,  6 );
  glVertex3f( -2,  26, -6 );
  glVertex3f( -2, -26, -6 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
 // glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  2,  26,  6 );
  glVertex3f(  2,  26, -6 );
  glVertex3f( -2,  26, -6 );
  glVertex3f( -2,  26,  6 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
 // glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  2, -26, -6 );//-
  glVertex3f(  2, -26,  6 );
  glVertex3f( -2, 26,   6 );
  glVertex3f( -2, -26, -6 );//-
  glEnd();
}glPopMatrix();
  glFlush();

///////////////////////////////////////////////////////////////////////////////
// 1/4 circle on the  upper side of the tire
//left
//front face
glColor3f(   0.8,  0.7,  0.6 );
glPushMatrix();
{
               glTranslatef(62,20,20);

               glRotatef(270,0,1,0);

  glBegin(GL_QUAD_STRIP);
  for (i = -30; i < 30; i++) {
    angle = i * M_PI/teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }

 // glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
 // glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();


}glPopMatrix();
glColor3f(   0.8,  0.7,  0.6 );
    glPushMatrix();{
    glTranslatef(42,20,76);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,1.5, 1.5, 20, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

//right
//front face
glColor3f(   0.8,  0.7,  0.6 );
glPushMatrix();
{
               glTranslatef(-64,20,20);

               glRotatef(270,0,1,0);
  // draw outward faces of teeth

  glBegin(GL_QUAD_STRIP);
  for (i = -30; i < 30; i++) {
    angle = i * M_PI/teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }
  glEnd();


}glPopMatrix();
glColor3f(   0.8,  0.7,  0.6 );
    glPushMatrix();{
    glTranslatef(-65,20,76);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,1.5, 1.5, 18, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

//front


glColor3f(   0.8,  0.7,  0.6 );


glPushMatrix();
{
               glTranslatef(0,226,31);

               glRotatef(270,0,1,0);
  // draw outward faces of teeth

  glBegin(GL_QUAD_STRIP);
  for (i = -50; i < 20; i++) {
    angle = i * M_PI/teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }


  glEnd();


}glPopMatrix();

  glColor3f(   0.8,  0.7, 0.6 );
    glPushMatrix();{
    glTranslatef(0,200,80);
    glRotatef(25, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 30, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();




/////////////////////////////////////////holding front tire

 glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(12,230,28);
    glRotatef(25, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 87, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(-12,230,28);
    glRotatef(25, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 87, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(-14,190,104);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3,28, 50, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();



///////////////////////////////////////////////////////////////////////////////////////////
    //holder of the paddel

    glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(-10,160,0);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3, 20, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    ///////////////////////////////////////////////////////////////////////


}glPopMatrix();

//fronmt base

  glColor3f(   0.6,  0.6, 0.6 );

    glPushMatrix();{
    glTranslatef(10,-70,-35);
    glRotatef(5, 0, 1,0);
    gluCylinder(quadric ,1.5,1.5 , 100, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


      glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(30,-70,-35);
    glRotatef(-5, 0, 1,0);
    gluCylinder(quadric ,1.5,1.5 , 100, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,-22,-35);
    glRotatef(26, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 108, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,-24,-35);
    glRotatef(-18, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 108, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();



      glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,9,65);
    glRotatef(90, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 81, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


   glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,6,55);
    glRotatef(90, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 73, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,9,65);
    glRotatef(20, 1,0 ,0);
    gluCylinder(quadric ,2,2 , 18, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(-1,3,82);
    glRotatef(90, 0,1 ,0);
    gluCylinder(quadric ,1.5,1.5 , 42, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

  glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(0,-4,82);
    glRotatef(270, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 7, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

     glColor3f(   0,  0, 0 );
    glPushMatrix();{
    glTranslatef(0,-10,82);
    glRotatef(270, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 7, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

   glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
    glTranslatef(40,-4,82);
    glRotatef(270, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 7, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

      glColor3f(   0,  0, 0 );
    glPushMatrix();{
    glTranslatef(40,-10,82);
    glRotatef(270, 1,0 ,0);
    gluCylinder(quadric ,1.5,1.5 , 7, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

  //bell
    glColor3f(1,0.9,0.8);
    glPushMatrix();{
		glTranslatef(6,2,86);
		//glRotatef(45, 1,1,1);
		glutSolidSphere(3, 4,40);
	}glPopMatrix();


    glColor3f(   0.6,  0.6, 0.6 );
    glPushMatrix();{
    glTranslatef(20,-70,65);
    glRotatef(10, 1,0 ,0);
    gluCylinder(quadric ,2,2 , 10, 40, 12);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


// glPushMatrix();{
   //   glRotatef(-wheel_4_rotate,0,0,1);
   //  glRotatef(-wheel_4_rotate,1,0,0);
    ///////////////////////////////////////right paddel
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
    glTranslatef(0,-20,-35);
    glRotatef(-270, 0.0, 1.0, 0.0);

    gluCylinder(quadric ,3, 3, 10, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glPushMatrix();{
    glTranslatef(0,-20,-34);
    glRotatef(90, 1.0, 0, 0.0);


    glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
       glRotatef(-wheel_4_rotate,1,0,0);
       gluCylinder(quadric ,3, 3, 30, 55, 15);

        glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
    glTranslatef(-10,0,30);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3, 10, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    }glPopMatrix();






   ///////////////////////////////////////left paddel
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
    glTranslatef(30,-20,-35);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3, 10, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glPushMatrix();{
    glTranslatef(40,-20,-34);
    glRotatef(-360, 0.0, 1.0, 0.0);


    glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
       glRotatef(-wheel_4_rotate,1,0,0);
       gluCylinder(quadric ,3, 3, 30, 55, 15);

        glColor3f(0.6,0.6,0.6);
    glPushMatrix();{
    glTranslatef(0,0,30);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3, 10, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    }glPopMatrix();

/////////////////////////////////////////////circle on the paddel
glPushMatrix();{
                glTranslatef(0,-20,-30);
                glRotatef(-270, 0.0, 1.0, 0.0);
glPushMatrix();{
                    double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -12;//30


     glTranslatef(0,0,-5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,5);
    glutSolidSphere(15,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
}glPopMatrix();

}glPopMatrix();

 //  }glPopMatrix();
   //sit of the rikshaw puller
   ////////////////////////////////////////////////////////////////////////////

    glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(10,-75,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 24, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(12,-72,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 20, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

   	glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(14,-69,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 16, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


     	glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(16,-66,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 10, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

     	glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(18,-63,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 6, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();


    	glColor3f(0,0,0);
    glPushMatrix();{
    glTranslatef(19,-60,78);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,2, 2, 4, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//rikshaw hood add any animation of hood from heere

  glPushMatrix();
  {
                 glTranslatef(-10,-158,132);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
    glColor3f(   1,1, 0 );
    glVertex3f(  20, -1, 35 );//+
    glVertex3f(  20,  1, 35 );//+
    glVertex3f( -20, 1, 35 );//+
    glVertex3f( -20, -1, 35 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  glColor3f(   1, 1, 0 );
  glVertex3f( 20, -1,   35 );//+
  glVertex3f( 20,  1,  35 );//+
  glVertex3f( 20, 1, -35);//-
  glVertex3f( 20, -1, -35 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  glColor3f(  1,  1,  0 );
  glVertex3f( -20, 1, -35 );  //minus
  glVertex3f( -20,-1, -35 );  //minus
  glVertex3f(  20,-1, -35 );//-
  glVertex3f(  20, 1, -35 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1, 0 );
  glVertex3f( -20, -1,  35 );
  glVertex3f( -20,  1,  35 );
  glVertex3f( -20,  1, -35 );
  glVertex3f( -20, -1, -35 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  20,  1,  35 );
  glVertex3f(  20,  1, -35 );
  glVertex3f( -20,  1, -35 );
  glVertex3f( -20,  1,  35 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  20, -1, -35 );//-
  glVertex3f(  20, -1,  35 );
  glVertex3f( -20, 1,  35 );
  glVertex3f( -20, -1, -35 );//-
  glEnd();
}glPopMatrix();
  glFlush();

///////////////////////////////////////////////////////////////////////////////////////

glPushMatrix();
  {
                 glTranslatef(50,-158,132);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
    glColor3f(   1,1, 0 );
    glVertex3f(  20, -1, 35 );//+
    glVertex3f(  20,  1, 35 );//+
    glVertex3f( -20, 1, 35 );//+
    glVertex3f( -20, -1, 35 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  glColor3f(   1, 1, 0 );
  glVertex3f( 20, -1,   35 );//+
  glVertex3f( 20,  1,  35 );//+
  glVertex3f( 20, 1, -35);//-
  glVertex3f( 20, -1, -35 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  glColor3f(  1,  1,  0 );
  glVertex3f( -20, 1, -35 );  //minus
  glVertex3f( -20,-1, -35 );  //minus
  glVertex3f(  20,-1, -35 );//-
  glVertex3f(  20, 1, -35 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1, 0 );
  glVertex3f( -20, -1,  35 );
  glVertex3f( -20,  1,  35 );
  glVertex3f( -20,  1, -35 );
  glVertex3f( -20, -1, -35 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  20,  1,  35 );
  glVertex3f(  20,  1, -35 );
  glVertex3f( -20,  1, -35 );
  glVertex3f( -20,  1,  35 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  20, -1, -35 );//-
  glVertex3f(  20, -1,  35 );
  glVertex3f( -20, 1,  35 );
  glVertex3f( -20, -1, -35 );//-
  glEnd();
}glPopMatrix();
  glFlush();

//////////////////////////////////////////////////////////////////////////////////////////////

glPushMatrix();
  {
                 glTranslatef(20,-158,165);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
    glColor3f(   1,1, 0 );
    glVertex3f(  50, -1, 4 );//+
    glVertex3f(  50,  1, 4 );//+
    glVertex3f( -50, 1, 4 );//+
    glVertex3f( -50, -1, 4 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
  glColor3f(   1, 1, 0 );
  glVertex3f( 50, -1,   4 );//+
  glVertex3f( 50,  1,  4 );//+
  glVertex3f( 50, 1, -4);//-
  glVertex3f( 50, -1, -4 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
  glColor3f(  1,  1,  0 );
  glVertex3f( -50, 1, -4 );  //minus
  glVertex3f( -50,-1, -4 );  //minus
  glVertex3f(  50,-1, -4 );//-
  glVertex3f(  50, 1, -4 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1, 0 );
  glVertex3f( -50, -1,  4 );
  glVertex3f( -50,  1,  4 );
  glVertex3f( -50,  1, -4 );
  glVertex3f( -50, -1, -4 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  50,  1,  4 );
  glVertex3f(  50,  1, -4 );
  glVertex3f( -50,  1, -4 );
  glVertex3f( -50,  1,  4 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0 );
  glVertex3f(  50, -1, -4 );//-
  glVertex3f(  50, -1,  4 );
  glVertex3f( -50, 1 , 4 );
  glVertex3f( -50, -1, -4 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//////////////////////////////////////top////////////////////////////////////////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(20,-149,171);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0,1, 0 );
    glVertex3f(  50, -10, 2 );//+
    glVertex3f(  50,  10, 2 );//+
    glVertex3f( -50, 10, 2 );//+
    glVertex3f( -50, -10, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 50, -10,   2 );//+
  glVertex3f( 50,  10,  2 );//+
  glVertex3f( 50, 10, -2);//-
  glVertex3f( 50, -10, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -50, 10, -2 );  //minus
  glVertex3f( -50,-10, -2 );  //minus
  glVertex3f(  50,-10, -2 );//-
  glVertex3f(  50, 10, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -50, -10,  2 );
  glVertex3f( -50,  10,  2 );
  glVertex3f( -50,  10, -2 );
  glVertex3f( -50, -10, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50,  10,  2 );
  glVertex3f(  50,  10, -2 );
  glVertex3f( -50,  10, -2 );
  glVertex3f( -50,  10,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
///  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50, -10, -2 );//-
  glVertex3f(  50, -10,  2 );
  glVertex3f( -50, 10,  2 );
  glVertex3f( -50, -10, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();

//////////////////////////////////////top2////////////////////////////////////////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(20,-130,171);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0,1, 0 );
    glVertex3f(  50, -10, 2 );//+
    glVertex3f(  50,  10, 2 );//+
    glVertex3f( -50, 10, 2 );//+
    glVertex3f( -50, -10, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 50, -10,   2 );//+
  glVertex3f( 50,  10,  2 );//+
  glVertex3f( 50, 10, -2);//-
  glVertex3f( 50, -10, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -50, 10, -2 );  //minus
  glVertex3f( -50,-10, -2 );  //minus
  glVertex3f(  50,-10, -2 );//-
  glVertex3f(  50, 10, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -50, -10,  2 );
  glVertex3f( -50,  10,  2 );
  glVertex3f( -50,  10, -2 );
  glVertex3f( -50, -10, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50,  10,  2 );
  glVertex3f(  50,  10, -2 );
  glVertex3f( -50,  10, -2 );
  glVertex3f( -50,  10,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
///  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50, -10, -2 );//-
  glVertex3f(  50, -10,  2 );
  glVertex3f( -50, 10,  2 );
  glVertex3f( -50, -10, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();


//////////////////////////////////////top3////////////////////////////////////////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(20,-120,171);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
 //   glColor3f(   0,1, 0 );
    glVertex3f(  50, -6, 2 );//+
    glVertex3f(  50,  6, 2 );//+
    glVertex3f( -50, 6, 2 );//+
    glVertex3f( -50, -6, 2 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 50, -6,   2 );//+
  glVertex3f( 50,  6,  2 );//+
  glVertex3f( 50, 6, -2);//-
  glVertex3f( 50, -6, -2 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -50, 6, -2 );  //minus
  glVertex3f( -50,-6, -2 );  //minus
  glVertex3f(  50,-6, -2 );//-
  glVertex3f(  50, 6, -2 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -50, -6,  2 );
  glVertex3f( -50,  6,  2 );
  glVertex3f( -50,  6, -2 );
  glVertex3f( -50, -6, -2 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50,  6,  2 );
  glVertex3f(  50,  6, -2 );
  glVertex3f( -50,  6, -2 );
  glVertex3f( -50,  6,  2 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
///  glColor3f(   0,  1.0,  0 );
  glVertex3f(  50, -6, -2 );//-
  glVertex3f(  50, -6,  2 );
  glVertex3f( -50, 6,  2 );
  glVertex3f( -50, -6, -2 );//-
  glEnd();
}glPopMatrix();
  glFlush();




/////////////////////////////////////////////////////////left/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(68,-152,135);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 36 );//+
    glVertex3f(  2,  5, 36 );//+
    glVertex3f( -2, 5, 36 );//+
    glVertex3f( -2, -5, 36 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   36 );//+
  glVertex3f( 2,  5,  36 );//+
  glVertex3f( 2, 5, -36);//-
  glVertex3f( 2, -5, -36 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -36 );  //minus
  glVertex3f( -2,-5, -36 );  //minus
  glVertex3f(  2,-5, -36 );//-
  glVertex3f(  2, 5, -36 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  36 );
  glVertex3f( -2,  5,  36 );
  glVertex3f( -2,  5, -36 );
  glVertex3f( -2, -5, -36 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  36 );
  glVertex3f(  2,  5, -36 );
  glVertex3f( -2,  5, -36 );
  glVertex3f( -2,  5,  36 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -36 );//-
  glVertex3f(  2, -5,  36 );
  glVertex3f( -2, 5,  36 );
  glVertex3f( -2, -5, -36 );//-
  glEnd();
}glPopMatrix();
  glFlush();


  /////////////////////////////////////////////////////////left2/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(68,-144,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();

  /////////////////////////////////////////////////////////left3/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(68,-135,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();

  /////////////////////////////////////////////////////////left4/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(68,-125,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();

  /////////////////////////////////////////////////////////right4/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(-28,-125,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();





 /////////////////////////////////////////////////////////right3/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(-28,-135,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();



 /////////////////////////////////////////////////////////right2/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(-28,-144,125);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 48 );//+
    glVertex3f(  2,  5, 48 );//+
    glVertex3f( -2, 5, 48 );//+
    glVertex3f( -2, -5, 48 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   48 );//+
  glVertex3f( 2,  5,  48 );//+
  glVertex3f( 2, 5, -48);//-
  glVertex3f( 2, -5, -48 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -48 );  //minus
  glVertex3f( -2,-5, -48 );  //minus
  glVertex3f(  2,-5, -48 );//-
  glVertex3f(  2, 5, -48 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  48 );
  glVertex3f( -2,  5,  48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2, -5, -48 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  48 );
  glVertex3f(  2,  5, -48 );
  glVertex3f( -2,  5, -48 );
  glVertex3f( -2,  5,  48 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -48 );//-
  glVertex3f(  2, -5,  48 );
  glVertex3f( -2, 5,  48 );
  glVertex3f( -2, -5, -48 );//-
  glEnd();
}glPopMatrix();
  glFlush();




//////////////////////////////////////////////right/////////////////////////
glColor3f(   0,1, 0 );
glPushMatrix();
  {
                 glTranslatef(-28,-152,135);
                //glRotatef(-4,0,0,0);

   glBegin(GL_POLYGON);  //blue
//    glColor3f(   0,1, 0 );
    glVertex3f(  2, -5, 36 );//+
    glVertex3f(  2,  5, 36 );//+
    glVertex3f( -2, 5, 36 );//+
    glVertex3f( -2, -5, 36 );//+
    glEnd();

  glBegin(GL_POLYGON);//yellow
//  glColor3f(   0, 1, 0 );
  glVertex3f( 2, -5,   36 );//+
  glVertex3f( 2,  5,  36 );//+
  glVertex3f( 2, 5, -36);//-
  glVertex3f( 2, -5, -36 );//-
  glEnd();

   glPushMatrix();
                  {
              //    glTranslatef(45,-40,-54);
  glBegin(GL_POLYGON);
  //white
//  glColor3f(  0,  1,  0 );
  glVertex3f( -2, 5, -36 );  //minus
  glVertex3f( -2,-5, -36 );  //minus
  glVertex3f(  2,-5, -36 );//-
  glVertex3f(  2, 5, -36 );//-
  glEnd();

  }glPopMatrix();


  // Green side - LEFT
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1, 0 );
  glVertex3f( -2, -5,  36 );
  glVertex3f( -2,  5,  36 );
  glVertex3f( -2,  5, -36 );
  glVertex3f( -2, -5, -36 );
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
//  glColor3f(   0,  1.0,  0 );
  glVertex3f(  2,  5,  36 );
  glVertex3f(  2,  5, -36 );
  glVertex3f( -2,  5, -36 );
  glVertex3f( -2,  5,  36 );
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
//  glColor3f(   1,  1.0,  0 );
  glVertex3f(  2, -5, -36 );//-
  glVertex3f(  2, -5,  36 );
  glVertex3f( -2, 5,  36 );
  glVertex3f( -2, -5, -36 );//-
  glEnd();
}glPopMatrix();
  glFlush();




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // glShadeModel(GL_FLAT);
  glPushMatrix();{

                  glTranslatef(30,40,-70);

    //holding the two wheel s of back
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{
    glTranslatef(-70,-200,45);
    glRotatef(-270, 0.0, 1.0, 0.0);
    gluCylinder(quadric ,3, 3, 120, 55, 15);
  //  gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

   //back wheel, right

  glPushMatrix();
  {
                glTranslatef(-75,-200,45);
                glRotatef(90, 0.0, 1.0, 0.0);


  glPushMatrix();
  {
                glRotatef(wheel_1_rotate,0,0,1);

  glColor3f(1.0,1.0,0.8);
  // draw front face

  glColor3f(0.0,0.0,0.2);
  glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  //}glPopMatrix();

  // draw front sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
  angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle +3 * da), width * 0.5);
  }
  glEnd();

  //glNormal3f(0.0, 0.0, -1.0);
  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw back sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw outward faces of teeth

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

    //main
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-7);
    gluCylinder(quadric, 3, 3, 14, 15, 5);
    gluCylinder(quadric, 3, 2, 14, 15, 5);
    }glPopMatrix();

   //this circle use to hold the break
   //1st one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-2);
    gluCylinder(quadric ,2, 2, 4, 25, 15);
    gluCylinder(quadric, 2, 2, 4 , 25, 15);
    }glPopMatrix();

    	}glPopMatrix();

    //2nd one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,22);
    gluCylinder(quadric ,2, 2, 4, 55, 15);
    gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    	}glPopMatrix();


  //two circle on both side of wheel
  //1st circle
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{

       double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = -12;//30
                    glTranslatef(0,0,5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,-5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
     }glPopMatrix();

 //second circle clipped
   glPushMatrix();{
                    double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -12;//30


     glTranslatef(0,0,-5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
}glPopMatrix();

//front face
glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da1), width1 * 0.5);
  }
  glEnd();

  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
  }
  glEnd();

  glPushMatrix();{
                  glTranslatef(0,0,-2);
                  gluCylinder(quadric ,48, 48, 4, 55, 15);
  }glPopMatrix();
 //lines in the wheel
 glColor3f(0.8,0.7,0.9);
 glLineWidth(2);
 glBegin(GL_LINES);
 {
                   //one side
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);

           }
           glEnd();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(40,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(80,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(120,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(160,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(200,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(240,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(280,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(320,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(360,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glEnd();

  }glPopMatrix();


  }glPopMatrix();

   glPushMatrix();
  {
                glTranslatef(55,-200,45);
                glRotatef(88, 0.0, 1.0, 0.0);

     //second wheel / back wheel
    glPushMatrix();
  {               glRotatef(wheel_2_rotate,0,0,1);


  glColor3f(1.0,1.0,0.8);
  // draw front face

  glColor3f(0.0,0.0,0.2);
  glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  //}glPopMatrix();

  // draw front sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
  angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle +3 * da), width * 0.5);
  }
  glEnd();

  //glNormal3f(0.0, 0.0, -1.0);
  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw back sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw outward faces of teeth
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

  //glShadeModel(GL_SMOOTH);

  //draw inside radius cylinder



    //small circle inside the wheel
    //main
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-7);
    gluCylinder(quadric, 3, 3, 14, 15, 5);
    gluCylinder(quadric, 3, 2, 14, 15, 5);
    }glPopMatrix();


   //this circle use to hold the break
   //1st one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-2);
    gluCylinder(quadric ,2, 2, 4, 25, 15);
    gluCylinder(quadric, 2, 2, 4 , 25, 15);
    }glPopMatrix();

    	}glPopMatrix();

    //2nd one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,22);
    gluCylinder(quadric ,2, 2, 4, 55, 15);
    gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    	}glPopMatrix();


  //two circle on both side of wheel
  //1st circle
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{

       double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = -12;//30
                    glTranslatef(0,0,5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,-5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
     }glPopMatrix();



 //second circle clipped
   glPushMatrix();{
                    double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -12;//30


     glTranslatef(0,0,-5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
}glPopMatrix();




//front face
glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da1), width1 * 0.5);
  }
  glEnd();

  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
  }
  glEnd();

  glPushMatrix();{
                  glTranslatef(0,0,-2);
                  gluCylinder(quadric ,48, 48, 4, 55, 15);
  }glPopMatrix();
//gluCylinder(quadric ,35.5, 35.5, 4, 55, 15);
//gluCylinder(quadric ,36, 36, 4, 55, 15);
//lines inside the  wheel arbitary ways


 //lines in the wheel
 glColor3f(0.8,0.7,0.9);
 glLineWidth(2);
 glBegin(GL_LINES);
 {
                   //one side
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);

           }
           glEnd();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(40,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(80,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(120,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(160,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(200,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(240,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(280,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(320,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(360,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);
                        }
           glEnd();
           }glPopMatrix();
  // the long holeders
   glEnd();
  }glPopMatrix();
}glPopMatrix();

 }glPopMatrix();




//front tire
glPushMatrix();
  {
                glTranslatef(20,50,-10);
                glRotatef(90, 0.0, 1.0, 0.0);


 glPushMatrix();
  {
                 glRotatef(-wheel_3_rotate,0,0,1);

  glColor3f(1.0,1.0,0.8);
  // draw front face

  glColor3f(0.0,0.0,0.2);
  glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  //}glPopMatrix();

  // draw front sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
  angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle +3 * da), width * 0.5);
  }
  glEnd();

  //glNormal3f(0.0, 0.0, -1.0);
  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw back sides of teeth

  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  // draw outward faces of teeth

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
  //  glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
  //  glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
   // glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
   // glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

    //main
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-7);
    gluCylinder(quadric, 3, 3, 14, 15, 5);
    gluCylinder(quadric, 3, 2, 14, 15, 5);
    }glPopMatrix();

   //this circle use to hold the break
   //1st one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,-2);
    gluCylinder(quadric ,2, 2, 4, 25, 15);
    gluCylinder(quadric, 2, 2, 4 , 25, 15);
    }glPopMatrix();

    	}glPopMatrix();

    //2nd one
     glPushMatrix();{
                     glTranslatef(0,0,-12);
    //most inner cylinder
    glColor3f(1.0,0.0,0.7);
    glPushMatrix();{
    glTranslatef(0,0,22);
    gluCylinder(quadric ,2, 2, 4, 55, 15);
    gluCylinder(quadric, 2, 2, 4 , 55, 15);
    }glPopMatrix();

    	}glPopMatrix();


  //two circle on both side of wheel
  //1st circle
    glColor3f(1.0,1.0,0.7);
    glPushMatrix();{

       double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = -12;//30
                    glTranslatef(0,0,5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,-5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
     }glPopMatrix();

 //second circle clipped
   glPushMatrix();{
                    double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = 1;//-1.z
	equ[3] = -12;//30


     glTranslatef(0,0,-5);
	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
    glPushMatrix();{
    glTranslatef(0,0,5);
    glutSolidSphere(10,15,20);

    	}glPopMatrix();

    	}glDisable(GL_CLIP_PLANE0);
}glPopMatrix();

//front face
glBegin(GL_QUAD_STRIP);

  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da1), width1 * 0.5);
  }
  glEnd();

  // draw back face

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= 360; i++) {
    angle1 = i * 2.0 * M_PI / teeth;
    glVertex3f(r4 * cos(angle1), r4 * sin(angle1), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
    glVertex3f(r4 * cos(angle1 + 3 * da1), r4 * sin(angle1 + 3 * da), -width1 * 0.5);
    glVertex3f(r3 * cos(angle1), r3 * sin(angle1), -width1 * 0.5);
  }
  glEnd();

  glPushMatrix();{
                  glTranslatef(0,0,-2);
                  gluCylinder(quadric ,48, 48, 4, 55, 15);
  }glPopMatrix();
 //lines in the wheel
  glColor3f(0.8,0.7,0.9);
 glLineWidth(2);
 glBegin(GL_LINES);
 {
                   //one side
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);

           }
           glEnd();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(40,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(80,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(120,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(160,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(200,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(240,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

           glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(280,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();


 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(320,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glPushMatrix();{
                // glTranslatef(0,10,0);
                glRotatef(360,0.0,0.0,1.0);
 glBegin(GL_LINES);
 {
              glVertex3f(1,7,7);
              glVertex3f(40,30,0);
                   //oposite side
              glVertex3f(-1,-7,-7);
              glVertex3f(-40,-30,0);

              glVertex3f(-1,-7,7);
              glVertex3f(-40,30,0);

              glVertex3f(-1,7,-7);
              glVertex3f(40,-30,0);


           }
           glEnd();
           }glPopMatrix();

 glEnd();

  }glPopMatrix();


 }glPopMatrix();





}glPopMatrix();

}glPopMatrix();



	glColor3f(0.9, 0.9, 0.9);	//grey
	glBegin(GL_LINES);{
		for(int i=-35;i<=35;i++){

	//		if(i==0)
	//			continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i*10, -350,-80);
			glVertex3f(i*10,  350, -80);

			//lines parallel to X-axis
			glVertex3f(-350, i*10, -80);
			glVertex3f( 350, i*10, -80);
		}
	}glEnd();


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void init(){

	rot =3;
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.006;
	//rectAngle = 0;
	//canDrawGrid = true;
	cameraHeight = 150;
	cameraRadius = 150;

	wheel_x=wheel_y=0;
	full_rot=0;
	car_speed=0;

	//Vector c1(-23.51,0,-32.36), u1(0,0,1);
	//s1 = new Seat(c1,u1);
	//Vector c2(23.51,0,-32.36), u2(0,0,1);
	//s2 = new Seat(c2,u2);
	//Vector c3(38,0,12.36), u3(0,0,1);
	//s3 = new Seat(c3,u3);
	//Vector c4(0,0,40), u4(0,0,1);
	//s4 = new Seat(c4,u4);
	//Vector c5(-38,0,12.26), u5(0,0,1);
	//s5 = new Seat(c5,u5);





    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);

	glClearColor(GROUND, 0);


	/*glClearDepth(1);
	glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);*/

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//gluPerspective(viewAngle,	aspectRatio,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}






void animate(){
	//codes for any changes in Camera

	cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!

    if(move_key==1)
    {
      wheel_1_rotate-=100;
      wheel_2_rotate-=100;
      wheel_3_rotate-=100;
      wheel_4_rotate-=100;
      move_key=0;
    }
    else if(move_key==-1)
    {
      wheel_1_rotate+=100;
      wheel_2_rotate+=100;
      wheel_3_rotate+=100;
      wheel_4_rotate+=100;
      move_key=0;
    }
    else if(move_key==-2)
    {
      wheel_1_rotate+=100;
      wheel_2_rotate+=100;
      wheel_3_rotate-=100;
      wheel_4_rotate-=100;
      move_key=0;
    }
    else if(move_key==2)
    {
      wheel_1_rotate-=100;
      wheel_2_rotate-=100;
      wheel_3_rotate+=100;
      wheel_4_rotate+=100;
      move_key=0;
    }

    uniRot+=uniRotDelta;

    if(uniRotDelta!=0)
    {
        if(cart_rotate<=0)
        {
            cart_rotate=cart_rotate+.05;
            increasing=1;
            decreasing=0;
            i_i=0;
        }
        else if(cart_rotate>=1)
        {
             cart_rotate=cart_rotate-.05;
             increasing=0;
             decreasing=1;
             i_i=0;
        }
        else if(cart_rotate>0 && cart_rotate<1)
        {
             i_i+=.1;
             if(increasing)cart_rotate=cart_rotate+.05;
             if(decreasing)cart_rotate=cart_rotate-.05;
        }
    }

    /*if(i_i>=5)
        i_i=0;
    else
        i_i+=.5;*/

    //wheel_x*=car_speed;
    //wheel_y*=car_speed;

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		//case '1':	//reverse the rotation of camera
			//uniRotDelta += 1;
			//break;

	//	case '2':	//increase rotation of camera by 10%
		//	uniRotDelta-=1;
			//break;

		//case '3':	//decrease rotation
		    //if(car_speed<2)
		  //  car_speed+=1;

			//break;

		//case '4':	//toggle grids
		    //if(car_speed>.1)
		   // car_speed-=1;
			//break;

		//case 'f':	//reverse the rotation of camera
			//cam.slide(0,0,-.5);
			//break;

		case 'b':	//reverse the rotation of camera
			cam.slide(0,0,.5);
			break;

		case 'u':	//toggle grids
			cam.slide(0,.5,0);
			break;

		case 'd':	//toggle grids
			cam.slide(0,-.5,0);
			break;

		//case 'l':	//toggle grids
		//	cam.slide(-.5,0,0);
		//	break;

		case 'r':	//toggle grids
			cam.slide(.5,0,0);
			break;

		case 'o':	//increase rotation of camera by 10%
		   cam.roll(1);
			break;

		//case 'p':	//decrease rotation
		//	cam.pitch(1);
			//break;


		//case 'y':	//toggle grids
			//cam.yaw(1);
			//break;

		case 'q':	//increase rotation of camera by 10% rotate
		   cam.roll(-1);
			break;

		//case 'a':	//decrease rotation
			//cam.pitch(-1);
			//break;


		case 'z':	//toggle grids
			cam.yaw(-1);
			break;

		//case 27:	//ESCAPE KEY -- simply exit
			//exit(0);
			//break;
		//case  'A':
             // rot +=rot;
             // break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){

		case GLUT_KEY_DOWN:		//down arrow key
            move_key=-1;
            /*if(car_speed>0)
            {
                            wheel_x*=car_speed/10;
                            wheel_y*=car_speed/10;
                            //car_speed=0;
            }
            if(car_speed<0)
            {
                            wheel_x/=abs(car_speed)/10;
                            wheel_y/=abs(car_speed)/10;
                            //car_speed=0;
            }*/
            if(abs(full_rot)%360>=90 && abs(full_rot)%360<=270)
            {
                                     //printf("\nfull_rot=%d prev_wheel_x=%f prev_wheel_y=%f \nnew_wheel_x=%f\n",full_rot,wheel_x,wheel_y,wheel_x+cos(full_rot*(PI/180)));

                                     if(full_rot>=0)
                                     {
                                         wheel_x=wheel_x+fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=180)
                                         {

                                               wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                               //printf("11.new_wheel_y=%f\n\n",wheel_y);

                                         }
                                         else
                                         {

                                               wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                               //printf("21.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }
                                     else
                                     {
                                         wheel_x=wheel_x+fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=180)
                                         {

                                               wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                               //printf("12.new_wheel_y=%f\n\n",wheel_y);

                                         }
                                         else
                                         {

                                               wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                               //printf("22.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }



            }
            else
            {
                                     //printf("\nfull_rot=%d prev_wheel_x=%f prev_wheel_y=%f \nnew_wheel_x=%f\n",full_rot,wheel_x,wheel_y,wheel_x-cos(full_rot*(PI/180)));

                                     if(full_rot>0)
                                     {
                                         wheel_x=wheel_x-fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=270)
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("31.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("41.new_wheel_y=%f\n\n",wheel_y);

                                         }
                                     }
                                     else
                                     {
                                         wheel_x=wheel_x-fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=270)
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("32.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("42.new_wheel_y=%f\n\n",wheel_y);

                                         }
                                     }
            }

			break;

		case GLUT_KEY_UP:		// up arrow key
            move_key=1;
            /*if(car_speed>0)
            {
                            wheel_x*=car_speed/10;
                            wheel_y*=car_speed/10;
                            //car_speed=0;
            }
            if(car_speed<0)
            {
                            wheel_x/=abs(car_speed)/10;
                            wheel_y/=abs(car_speed)/10;
                            //car_speed=0;
            }*/
			if(abs(full_rot)%360>=90 && abs(full_rot)%360<=270)
			{
                                     //printf("\nfull_rot=%d prev_wheel_x=%f prev_wheel_y=%f\n",full_rot,wheel_x,wheel_y);

                                     if(full_rot>=0)
                                     {
                                         wheel_x=wheel_x-fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=180)
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("51.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("61.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }
                                     else
                                     {
                                         wheel_x=wheel_x-fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f value=%f cos value=%f\n",wheel_x,fabs(full_rot)*PI/180,abs(cos(abs(full_rot)*PI/180)));
                                         if(abs(full_rot)%360>=180)
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("52.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("62.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }
            }
            else
            {
                                     //printf("\nfull_rot=%d prev_wheel_x=%f prev_wheel_y=%f \nnew_wheel_x=%f\n",full_rot,wheel_x,wheel_y,wheel_x+cos(full_rot*(PI/180)));

                                     if(full_rot>=0)
                                     {
                                         wheel_x=wheel_x+fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=270)
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("71.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("81.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }
                                     else
                                     {
                                         wheel_x=wheel_x+fabs(cos(full_rot*(PI/180)));
                                         //printf("new_wheel_x=%f\n",wheel_x);
                                         if(abs(full_rot)%360>=270)
                                         {

                                              wheel_y=wheel_y+fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("72.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                         else
                                         {

                                              wheel_y=wheel_y-fabs(sin(abs(full_rot)*(PI/180)));
                                              //printf("82.new_wheel_y=%f\n\n",wheel_y);
                                         }
                                     }

            }
			break;

		case GLUT_KEY_RIGHT:
             move_key=2;
             full_rot-=3;
             break;

		case GLUT_KEY_LEFT:
             move_key=-2;
             full_rot+=3;
			break;

		case GLUT_KEY_PAGE_UP:

			break;
		case GLUT_KEY_PAGE_DOWN:

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

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			//if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			//	cam.roll(5);

             if(_rot<=10){
                  _rot +=0.05;
                   break;
		}
			//break;

		case GLUT_RIGHT_BUTTON:
		//	if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
		//		cam.pitch(5);

             if(_rot!=0){
                        _rot -= 5;
                         break;
			}
		//	break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("RIKSHAW PROJECT");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	//glutKeyboardUpFunc(keyUp);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	cam.set(eye,look,up);



	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
