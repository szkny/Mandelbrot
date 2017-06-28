/* main.cpp
 *
 *     マンデルブロ集合計算プログラム
 *     (c) S.Suzuki 2017.6.27
 */
#include<stdio.h>
#include<math.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Objects.h>


/* Function Prototype Declaration */
void WindowCanvas(void);
void Controler(void);
void MouseDrawMode(void);
void PopUpMenu(void);
void Display(void);
void Resize(int w, int h);
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void KeyboardShortcut(unsigned char key, int x, int y);
void Keyboard_sp(int key, int x, int y);

/* main function */
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	WindowCanvas();
	PopUpMenu();
	Controler();
	
	glutMainLoop();
	return 0;
}

/******** Functions *********/

void WindowCanvas(void){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("Mandelbrot");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glClearColor(0.2,0.2,0.2,1.0);
}


void Controler(void){
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(KeyboardShortcut);
	glutSpecialFunc(Keyboard_sp);
}


void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawCanvas();
	glDisplayStrings();
	glColorBar();

	glutIdleFunc(glutPostRedisplay);
	glutSwapBuffers();
}

double windowW = 0.0;
double windowH = 0.0;

void Resize(int w, int h){
	windowW = w;
	windowH = h;
	glViewport(0, 0, w ,h);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}


