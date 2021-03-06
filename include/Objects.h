#ifndef Object_h_
#define Object_h_

/*****************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
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

/* flags */
bool SFLAG = true;
bool CFLAG = false;
extern bool MFLAG;
extern bool VFLAG;

/* clock time */
clock_t FrameTbase = 0;   // for frame rate
int FrameCounter   = 0;   // for frame rate
int TmpCounter     = 0;   // for frame rate
double FrameTimer  = 0.0; // for frame rate

/* color offset */
double coloff = 0.5;

/* parameters */
double Cr  =-1.258191798355;
double Ci  = 0.386442697238;
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
    return NMAX; // 計算の繰り返し上限到達
}


inline void glDrawCanvas(void){
    NMAX = 1e2+1/pow(VS,0.25);
    if(NMAX<1e2) NMAX = 1e2;
    double dVS = 2.0*VS/windowW;
    glBegin(GL_QUADS);
    for(double a=Cr-VS;a<Cr+VS;a+=dVS){
        for(double b=Ci-VS;b<Ci+VS;b+=dVS){
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
        STRING("Cr    : %+.12lf",Cr,10,50);
        STRING("Ci    : %+.12lf",Ci,10,65);
    }	
}
#undef STRING


void glColorBar(void){
    if(CFLAG){
        double hmax = 1.0;
        double hbin = hmax/1000;
        glBegin(GL_QUADS);
        for(double h=0.0;h<hmax;h+=hbin){
            hue2rgb hue(h,hmax);
            glColor3d(hue.R(),hue.G(),hue.B());
            glVertex2d(h     ,0.0);
            glVertex2d(h+hbin,0.0);
            glVertex2d(h+hbin,30.0/windowH);
            glVertex2d(h     ,30.0/windowH);
        }
        glEnd();
    }
}


void glParameterBar(void){
    if(SFLAG&&!CFLAG){
        double x = -log(VS/3)/log(3.0/1e-10);
        static double y = 15.0;
        glColor3d(0.0,0.0,0.0);
        glBegin(GL_LINES);
        glVertex2d(0.0,y/windowH);
        glVertex2d(1.0,y/windowH);
        glEnd();
#define plot(a,b)\
        glColor3d(a,a,a);\
        glBegin(b);\
        glVertex2d(x-10/windowW,(y-5)/windowH);\
        glVertex2d(x+10/windowW,(y-5)/windowH);\
        glVertex2d(x+10/windowW,(y+5)/windowH);\
        glVertex2d(x-10/windowW,(y+5)/windowH);\
        glEnd();
        plot(0.8,GL_QUADS);
        plot(0.0,GL_LINE_LOOP);
#undef plot
    }
}


void SetRange(int x, int y){
    if((windowH-20<=y&&y<=windowH-10)||MFLAG){
        VFLAG = true;
        VS = pow(10,-x/windowW*(log10(3)+10)+log10(3));
        if(VS<2.0e-10) VS = 2.0e-10;
        if(1.5<VS) VS = 1.5;
    }
}


#undef DIV

/*****************************/

#endif //"Object_h_"
