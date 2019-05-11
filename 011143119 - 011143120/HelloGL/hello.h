#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ESCAPE 27
#define MAX_FPS 60


typedef struct object_type{
    int shape;
    float x;
    float y;
    float z;
    float radius;
    int total;
    int texture;
    float vertex[100][3];

} object;

extern int window;
extern int dox;
extern int doy;
extern float changerate;
extern int currentFPS;

extern int ballcount;
extern object triangle;
extern object rectangle;
extern object *control;
extern object balls[100];
extern int keystate [300];

extern char *playertex;
extern char *balltex;
extern int score;
extern int over;
extern int framecount;


//draw
void set_vertex(float *vertex, float v0, float v1, float v2);
void create_object(object *a, float x, float y, float z, int shape, int total, float radius, const char* texname);
void create_ball(object *a, float x, float y, float z, int shape, int total, float radius, const char* texname);
void draw_object(object *a);
void draw_object_arr(object *a, int objcount);
int load_texture(const char *filename, int width, int height);


//render
void init_gl(int Width, int Height);
void resize_glscene(int Width, int Height);
void draw_glscene();
void update(int flag);
void position_update();
void collision_update();
void counter_update();
void write_text(char *str, float x, float y);
void state_reset(int, int);
void render_scene();



//events
void key_pressed(unsigned char key, int x, int y);
void special_input(int key, int x, int y);
void skey_down(int key, int x, int y);
void skey_up(int key, int x, int y);

//collision
int check_collision(object *a, object *b);
