/*
*	Keyboard Shortcuts Configurations 
*/

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<MyGLUT.h>

extern double Cr,Ci,VS;
extern bool SFLAG,CFLAG;


void KeyboardShortcut(unsigned char key, int x, int y){
	switch(key){
		case 'q':
			exit(0);
		case 's':
			if(SFLAG) SFLAG = false;
			else      SFLAG = true;
			break;
		case 'c':
			if(CFLAG) CFLAG = false;
			else      CFLAG = true;
			break;
		case '_':
			Cr =-1.373392;
			Ci = 0.022046;
			VS = 2.0;
			break;
		default:
			break;
	}
}


void Keyboard_sp(int key, int x, int y){
	static double speed = 5.0;
	switch(key){
		case GLUT_KEY_UP:
			VS *= (100-speed)/100;
			if(VS<1.0e-6) VS = 1.0e-6;
			break;
		case GLUT_KEY_DOWN:
			VS *= (100+speed)/100;
			if(3.0<VS) VS = 3.0;
			break;
		default:
			break;
	}
}

