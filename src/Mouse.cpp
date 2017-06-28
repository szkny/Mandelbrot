/*
*	Mouse Configurations 
*/

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

extern double windowW,windowH;
extern bool CFLAG;
extern double coloff;
extern double Cr,Ci,VS;
bool MFLAG;

/* mouse click */
void MouseClick(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){
				if(CFLAG) coloff = x/windowW;
			}
			if(state==GLUT_UP){
				CFLAG = false;
				MFLAG = false;
			}
			break;
		default:
			break;
	}
}


/* mouse motion */
void MouseMotion(int x, int y){
	static int xmouse;
	static int ymouse;
	if(MFLAG){
		if(CFLAG) coloff = x/windowW;
		else{
			Cr -= (double)(x-xmouse)/200*VS;
			if(Cr<-2.0) Cr = -2.0;
			if( 2.0<Cr) Cr =  2.0;
			Ci += (double)(y-ymouse)/200*VS;
			if(Ci<-2.0) Ci = -2.0;
			if( 2.0<Ci) Ci =  2.0;
		}
	}
	xmouse = x;
	ymouse = y;
	MFLAG  = true;
}

