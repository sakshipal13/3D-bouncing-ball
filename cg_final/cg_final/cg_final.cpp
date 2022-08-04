#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

int first,sec,third,fourth,fifth,speedmenu,mainmenu,qualitymenu;
double radius = 0.5;
static double theta = 0.0;

void Display(void);
void myinit(void);
void MakeGeometry(void);
void MakeLighting(void);
void MakeCamera(int,int,int);
void toggleballkeys(int key,int x, int y);
void HandleMouse(int,int,int,int);
void HandleMainMenu(int);
void HandleSpeedMenu(int);
void HandleLightMenu(int);
void HandleVisibility(int vis);
void HandleIdle(void);
void DrawTextXY(double,double,double,double,char *);
void optionkeys(unsigned char,int,int);
void aboutuskeys(unsigned char,int,int);
void helpkeys(unsigned char,int,int);
void keyboard(unsigned char,int,int);

#define TRUE  1
#define FALSE 0
#define PI 3.141592653589793238462643

#define DRAFT  0				// DRAW QUALITY ATTRIBUTE
#define RED 1					// LIGHT COLOR ATTRIBUTE
#define GREEN 2				    // LIGHT COLOR ATTRIBUTE
#define BLUE 3					// LIGHT COLOR ATTRIBUTE
int drawquality = DRAFT;		// BALL DRAW QUALITY
int lighting;					// LIGHTING COLOR
int spincamera = TRUE;          // DEFAULT CAMERA SPIN STATE
int cameradirection = 1;		// INITIAL CAMERA DIRECTION
double updownrotate = 70;		// INITIAL PLATFROM POSITION
int ballbounce = TRUE;			// DEFAULT BALL BOUNCE STATE
double ballspeed = 2;			// INITIAL BALL SPEED


void myreshape1(int w,int h)
{
	glClearColor(1.0,1.0,0.0,1.0);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
}

void myreshape2(int w,int h)
{
	glClearColor(0.0,1.0,0.0,1.0);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
}

void myreshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
}

void myreshape4(int w,int h)
{
	glClearColor(0.0,1.0,1.0,1.0);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
}


void introdisp(void)			//INITIAL MENU
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glutFullScreen();
	DrawTextXY(-1.15,1.0,0.0,0.002,"BOUNCING BALL");
    DrawTextXY(-0.83,0.0,0.0,0.0015,"Press any key  ");
 	DrawTextXY(-2.6,-1.18,0.0,0.0015,"SAPTHAGIRI COLLEGE OF ENGINEERING - BANGALORE");
	glFlush();

}

void helpdisp(void)			//HELP DESCRIPTION
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,1.0);
	DrawTextXY(-0.5,1.5,0.0,0.0022,"HELP");
	DrawTextXY(-2.5,1.1,1.0,0.0016,"Click on the right button to get these options");
    DrawTextXY(-2.5,0.8,1.5,0.0011,"Toggle camera spin:To start and stop the rotation of camera");
	DrawTextXY(-2.5,0.5,1.3,0.0011,"Toggle Ball bounce:To start and stop the bouncing of ball");
	DrawTextXY(-2.5,0.2,2.5,0.0011,"Ball speed:To increase and decrease the speed of bouncing of the ball");
	DrawTextXY(-2.5,-0.1,2.7,0.0011,"Quit:To exit from the execution");
	DrawTextXY(-0.5,-1.5,0.0,0.001,"PRESS H : HOME");
    glFlush();
	
}

void aboutdisp(void)			//ABOUT US DESCRIPTION
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	DrawTextXY(-0.5,1.5,0.0,0.0022,"ABOUT US");
	DrawTextXY(-2.5,1.1,1.0,0.0016,"Submitted By:");
    DrawTextXY(-2.5,0.8,1.5,0.0012,"PRASHANT YADAV (1SG15CS072)");
	DrawTextXY(-2.5,0.5,1.3,0.0012,"PRATIK KUMAR SHARMA (1SG15CS073)");
	DrawTextXY(-2.5,0.0,2.5,0.0016,"Under The Guidance Of:");
	DrawTextXY(-2.5,-0.3,2.7,0.0012,"PROF. KAMALAKSHI N");
	DrawTextXY(-2.5,-0.6,2.9,0.0012,"PROF. VEENA K R");
	DrawTextXY(-0.5,-1.5,0.0,0.0012,"PRESS H : HOME");
	glFlush();
	
}


void optndisp(void)			//HOME PAGE
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.70,0.0,0.50);
	DrawTextXY(-0.5,1.5,0.0,0.0022,"OPTIONS");
	DrawTextXY(-1.0,0.80,0.0,0.0015,"PRESS A : EXECUTION");
	DrawTextXY(-1.0,0.0,0.0,0.0015,"PRESS B : HELP");
	DrawTextXY(-1.0,-0.80,0.0,0.0015,"PRESS C : ABOUT US");
	DrawTextXY(-1.0,-1.60,0.0,0.0015,"PRESS D : EXIT");
	glFlush();
	glutSwapBuffers();
}

void Display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   MakeCamera(FALSE,0,0);
   MakeLighting();
   MakeGeometry();
   glPopMatrix();
   glutSwapBuffers();
   glFlush();
}

void helpkeys(unsigned char key,int x,int y)		
{
	glutInitWindowSize(1000,1000);
	sec=glutCreateWindow("Home");
	glutFullScreen();
	glutReshapeFunc(myreshape2);
	glutDisplayFunc(optndisp);
	glutKeyboardFunc(optionkeys);
	glutMainLoop();
}

void aboutuskeys(unsigned char key,int x,int y)		
{
	glutInitWindowSize(1000,1000);
	sec=glutCreateWindow("Home");
	glutFullScreen();
	glutReshapeFunc(myreshape2);
	glutDisplayFunc(optndisp);
	glutKeyboardFunc(optionkeys);
	glutMainLoop();
}


void keyboard(unsigned  char key,int x,int y)			//FOR BALL BOUNCE 
{
	if(key=='h'||key=='H')			//JUMP TO SECOND PAGE FROM BALL ANIMATION
		helpkeys('x',0,0);
	else if(key=='e'||key=='E')			//QUIT TO WINDOWS FROM BALL ANIMATION
		exit(0);		
}

 void myinit(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH); 
	glShadeModel(GL_SMOOTH);    
	glLineWidth(0.5);
	glPointSize(0.5);
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_COLOR_MATERIAL);
}


void optionkeys(unsigned char key,int x,int y)		
{
	if(key=='a'||key=='A')					// BALL ANIMATION
	{
		glutInitWindowSize(1000,700);
		glutInitWindowPosition(188,50);
		third=glutCreateWindow("bouncing ball");
		glutReshapeFunc(myreshape);
		glutDisplayFunc(Display);
		glutVisibilityFunc(HandleVisibility);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(toggleballkeys);
		glutMouseFunc(HandleMouse);
		myinit();
		speedmenu = glutCreateMenu(HandleSpeedMenu);
			glutAddMenuEntry("Slow",1);
			glutAddMenuEntry("Medium",2);
			glutAddMenuEntry("fast",3);
		qualitymenu = glutCreateMenu(HandleLightMenu);
			glutAddMenuEntry("Red",1);
			glutAddMenuEntry("Green",2);
			glutAddMenuEntry("Blue",3);
		mainmenu = glutCreateMenu(HandleMainMenu);
			glutAddMenuEntry("Toggle camera spin",1);
			glutAddMenuEntry("Toggle ball bounce",2);
			glutAddSubMenu("Ball speed",speedmenu);
			glutAddSubMenu("Lighting",qualitymenu);
			glutAddMenuEntry("Quit",100);
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		glutMainLoop();
		glutSwapBuffers();
		glFlush();
	}

	if(key=='b'||key=='B')				//FOR HELP
	{
		fourth=glutCreateWindow("help");
		glutFullScreen();
		glutReshapeFunc(myreshape4);
		glutDisplayFunc(helpdisp);
		glutKeyboardFunc(helpkeys);
		glutMainLoop();
		glFlush();
	}

	if(key=='c'||key=='C')				//FOR ABOUT US
	{
		fifth=glutCreateWindow("about us");
		glutFullScreen();
		glutReshapeFunc(myreshape4);
		glutDisplayFunc(aboutdisp);
		glutKeyboardFunc(aboutuskeys);
		glutMainLoop();
		glFlush();
	}


	if(key=='d'||key=='D')				//FOR EXIT
		exit(0);

}


void MakeGeometry(void)				//FOR PLATFORM AND BALL
{
	glPushMatrix();
    glColor3f(1.0,1.0,1.0);			//(0.0,0.5,1.0);			//ball color
	
	glTranslatef(0.0,radius+0.5*(1+sin(PI*theta/180)),0.0);
	glScalef(radius,radius,radius);
	if (ballbounce)
		theta += ballspeed;
	glutWireSphere(1.0,26,26);
	glPopMatrix();
    
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.5,0.5);        //platform color
	glVertex3f( 2.0, 0.0, 2.0);
	glVertex3f( 2.0, 0.0,-2.0);
	glVertex3f(-2.0, 0.0,-2.0);
	glVertex3f(-2.0, 0.0, 2.0); 
	glEnd();

	glColor3f(1.0,1.0,1.0);			//text color
	DrawTextXY(-2.0,-0.25,2.0,0.002,"Bouncing Ball");
}


void MakeLighting(void)
{
	GLfloat ambred[] = {1.0,0.3,0.3,0.0};
	GLfloat ambgreen[] = {0.4,1.0,0.4,0.0};
	GLfloat ambblue[] = {0.4,0.4,1.0,0.0};

	GLfloat pos0[] = {13.0,13.0,0.0,0.0};      
	GLfloat dif0[] = {0.8,0.8,0.8,1.0};
	GLfloat pos1[] = {7.0,7.0,0.0,0.0};   
	GLfloat dif1[] = {0.8,0.8,0.8,1.0};

	if (lighting==RED) 
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambred);
		glLightfv(GL_LIGHT0,GL_POSITION,pos0);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,dif0);
		glLightfv(GL_LIGHT1,GL_POSITION,pos1);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,dif1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
	}
    if (lighting==GREEN) 
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambgreen);
		glLightfv(GL_LIGHT0,GL_POSITION,pos0);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,dif0);
		glLightfv(GL_LIGHT1,GL_POSITION,pos1);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,dif1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
	}
	if (lighting==BLUE) 
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambblue);
		glLightfv(GL_LIGHT0,GL_POSITION,pos0);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,dif0);
		glLightfv(GL_LIGHT1,GL_POSITION,pos1);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,dif1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
	}
}


void MakeCamera(int pickmode,int x,int y)
{
	static double theta = 0;
	GLint viewport[4];
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (pickmode == TRUE) 
	{
		gluPickMatrix(x,viewport[3]-y,3.0,3.0,viewport);
	}
	gluPerspective(70.0,1.0,0.1,1000.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5*cos(theta*PI/180)*sin(updownrotate*PI/180),
             5*cos(updownrotate*PI/180),
             5*sin(theta*PI/180)*sin(updownrotate*PI/180), 
             0.0,0.0,0.0,                                   
             0.0,1.0,0.0);                                  
	if (spincamera)
		theta += (cameradirection * 0.2);
}


void toggleballkeys(int key,int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:  cameradirection = -1; break;
	case GLUT_KEY_RIGHT: cameradirection = 1;  break;
	case GLUT_KEY_UP:    updownrotate -= 2;  break;
	case GLUT_KEY_DOWN:  updownrotate += 2;  break;
	}
}


void HandleMouse(int button,int state,int x,int y)
{
	int maxselect = 100,nhits = 0;
	if (state == GLUT_DOWN) 
	{
		glPushMatrix();
		MakeCamera(TRUE,x,y);
		MakeGeometry();
		glPopMatrix();
	}
}


void HandleMainMenu(int whichone)
{
	switch (whichone)
	{
	case 1: spincamera = !spincamera; break;
	case 2: ballbounce = !ballbounce; break;
	case 100: exit(0); break;
	}
}


void HandleSpeedMenu(int whichone)
{
	switch (whichone) 
	{
	case 1: ballspeed = 0.6; break;
	case 2: ballspeed = 3.5;   break;
	case 3: ballspeed = 9;  break;
	}
}

void HandleLightMenu(int whichone)
{
	switch (whichone)
	{
	case 1: lighting = RED;
			MakeLighting();
			break;
	case 2:	lighting = GREEN;
			MakeLighting();
			break;
	case 3:	lighting = BLUE;
			MakeLighting();
			break;
	}
}


void HandleIdle(void)
{
	glutPostRedisplay();
}


void HandleVisibility(int visible)
{
	if (visible == GLUT_VISIBLE)
		glutIdleFunc(HandleIdle);
	else
		glutIdleFunc(NULL);
}


void DrawTextXY(double x,double y,double z,double scale,char *s)
{
	int i,l=strlen(s);
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(scale,scale,scale);
	for (i=0;i <l;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
	glPopMatrix();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(10,10);
	first=glutCreateWindow("Introduction");
	glutReshapeFunc(myreshape1);
	glutDisplayFunc(introdisp);
	glutKeyboardFunc(helpkeys);
	glutMainLoop();
	return(0);
}