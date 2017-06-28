#ifndef Object_h_
#define Object_h_

/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include"MyGLUT.h"
#include"Hue2rgb.h"
#include"Define.h"

/* divergence constant */
#define DIV 4.0

/* calculate loop max */
int NMAX = 1e2; 

extern double windowW,windowH;

/* status flag */
bool SFLAG = true;
bool CFLAG = false;

/* clock time */
clock_t FrameTbase = 0;   // for frame rate
int FrameCounter   = 0;   // for frame rate
int TmpCounter     = 60;  // for frame rate
double FrameTimer  = 0.0; // for frame rate

/* color offset */
double coloff = 0.0;

/* parameters */
double Cr  =-1.373392;
double Ci  = 0.022046;
double VS  = 2.0;

inline double mandelbrot(double a, double b){
	double x = 0.0;
	double y = 0.0;
	double x1, y1;
	for(int n=1;n<=NMAX;n++){
		x1 = x*x-y*y+a;
		y1 = 2.0*x*y+b;
		if( x1*x1+y1*y1>DIV) return n; // 発散
		x = x1;
		y = y1;
	}
	return 1.0; // 計算の繰り返し上限到達
}
	

inline void glDrawCanvas(void){
	double dVS = 2.0*VS/windowW;
	glBegin(GL_QUADS);
		for(double a=Cr-VS;a<Cr+VS;a+=dVS){
			for(double b=Ci-VS;b<Ci+VS;b+=dVS){
				//hue2rgb C(log(mandelbrot(a,b))+log(NMAX)*coloff,log(NMAX));
				hue2rgb C(mandelbrot(a,b)+NMAX*coloff,NMAX);
				glColor3d(C.R(),C.G(),C.B());
				glVertex2d(0.5+(-Cr+a    )/(2*VS),0.5+(-Ci+b    )/(2*VS));
				glVertex2d(0.5+(-Cr+a+dVS)/(2*VS),0.5+(-Ci+b    )/(2*VS));
				glVertex2d(0.5+(-Cr+a+dVS)/(2*VS),0.5+(-Ci+b+dVS)/(2*VS));
				glVertex2d(0.5+(-Cr+a    )/(2*VS),0.5+(-Ci+b+dVS)/(2*VS));
			}
		}
	glEnd();
}


#define STRING(arg1,arg2,x,y)\
sprintf(s,arg1,arg2);\
glDrawString(s,x/windowW,(windowH-y)/windowH);
/* Draw String Information */
inline void glDisplayStrings(void){
	if(SFLAG){
		FrameTimer = (double)(clock()-FrameTbase)/CLOCKS_PER_SEC;
		if(FrameTimer>=1.0){
			TmpCounter = FrameCounter;
			FrameCounter = 0;
			FrameTbase = clock();
		}
		++FrameCounter;
		/* Strings */
		glColor3d(0.0,0.0,0.0);
		static char s[128];
		STRING("frame : %d fps",TmpCounter,10,20);
		STRING("Range : %5.2e",VS,10,35);
		STRING("Cr    : %+f",Cr,10,50);
		STRING("Ci    : %+f",Ci,10,65);
	}	
}
#undef STRING


void glColorBar(void){
	if(CFLAG){
		double hmax = 1.0;
		double hbin = hmax/1000;
		int i = 0;
		glBegin(GL_QUADS);
		for(double h=0.0;h<hmax;h+=hbin){
			hue2rgb hue(h,hmax);
			glColor3d(hue.R(),hue.G(),hue.B());
			glVertex2d(h     ,0.0);
			glVertex2d(h+hbin,0.0);
			glVertex2d(h+hbin,30.0/windowH);
			glVertex2d(h     ,30.0/windowH);
			++i;
		}
		glEnd();
	}
}
#undef DIV

/*****************************/

#endif //"Object_h_"
