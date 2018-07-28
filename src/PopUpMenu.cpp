/*
 *	PopupMenu Configurations
 */

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<MyGLUT.h>

extern bool SFLAG,CFLAG;
void Menu(int val);

void PopUpMenu(void){
    glutCreateMenu(Menu);
    glutAddMenuEntry("Show Status",2);
    glutAddMenuEntry("Change Color",1);
    glutAddMenuEntry("Quit",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
    switch(val){
        case 0: /* Quit */
            exit(0);
        case 1: /* Change Color */
            if(CFLAG) CFLAG = false;
            else      CFLAG = true;
            break;
        case 2: /* Show Status */
            if(SFLAG) SFLAG = false;
            else      SFLAG = true;
            break;
        default:
            break;
    }
}

