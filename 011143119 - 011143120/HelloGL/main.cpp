#include "hello.h"

int window;

int main(int argc, char **argv)
{
    /* Initialize The Window */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(540, 680);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Box in the clouds!!");
    glutDisplayFunc(&render_scene);
    glutIdleFunc(&render_scene);
    glutReshapeFunc(&resize_glscene);
    glutSetKeyRepeat(0);
    glutKeyboardFunc(&key_pressed);
    glutSpecialFunc(&skey_down);
    glutSpecialUpFunc(&skey_up);
    init_gl(540, 680);
    glutMainLoop();
    return 1;
}
