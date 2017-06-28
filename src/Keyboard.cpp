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

extern int NMAX;
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
#define SetAngle(N,x,y)\
case N:Cr=x;Ci=y;VS=2.0;NMAX=1e2;break;
			SetAngle('_',-1.258191798355,+0.386442697238);
			SetAngle('1',-0.615873775035,+0.404426196260);
			SetAngle('2',-1.402480640849,+0.000184213080);
			SetAngle('3',-0.597512865217,+0.664859541642);
			SetAngle('4',+0.259020698362,-0.001228022777);
			SetAngle('5',-0.098733410965,+0.837333386750);
			SetAngle('6',+0.236550040362,-0.563960255907);
#undef SetAngle
		default:
			break;
	}
}


void Keyboard_sp(int key, int x, int y){
	static double speed = 5.0;
	switch(key){
		case GLUT_KEY_UP:
			VS *= (100-speed)/100;
			if(VS<1.0e-10) VS = 1.0e-10;
			break;
		case GLUT_KEY_DOWN:
			VS *= (100+speed)/100;
			if(3.0<VS) VS = 3.0;
			break;
		default:
			break;
	}
}

