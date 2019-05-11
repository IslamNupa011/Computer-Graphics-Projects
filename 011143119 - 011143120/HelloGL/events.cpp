#include "hello.h"

int keystate[300];

/* (Replaced) Function to Check for key presses */
void key_pressed(unsigned char key, int x, int y)
{
    if (key == ESCAPE) {
        glutDestroyWindow(window);
        exit(0);
    }
    if(key == 'r'){
        state_reset(0, 0);
    }
    if(key == 's'){
        state_reset(1, 0);
    }
}

/*Function to set the state of a key -> down */
void skey_down(int key, int x, int y)
{
    keystate[key] = 1;
}

/* Function to set the state of a key -> up */
void skey_up(int key, int x, int y)
{
    keystate[key] = 0;
}

