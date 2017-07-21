/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glaux.h"
#include <math.h>

static int slices = 16;
static int stacks = 16;
static float angleRot = 0;
static float xRot = 0.0f;
static float yRot = 0.0f;
static float zRot = 0.0f;

static float angleCamTeta = 0.0f;
static float angleCamPhi = 0.0f;

static float lxCam = 0.0f;
static float lzCam = 1.0f;
static float xCam = 0.0f;
static float yCam = 0.0f;
static float zCam = 5.0f;

static float xPos = 0.0f;
static float yPos = 0.0f;
static float zPos = -30.0f;

static float xVec = 0.0f;
static float yVec = 0.1f;
static float zVec = 0.0f;

static HDC hDC = NULL;
static HGLRC hRC = NULL;
static HWND hWnd = NULL;
static HINSTANCE hInstance;

static GLuint base;
static GLfloat cnt1;
static GLfloat cnt2;

static bool keys[256];
static bool active = TRUE;
static bool fullscreen = TRUE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static void camUp();
float modulo(float x, float y);

/* GLUT callback Handlers */

/*static void BuildFont(void) {

    HFONT font;
    HFONT oldfont;

    base = glGenLists(96);

    font = CreateFont(-24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Courier New");

    oldfont = (HFONT)SelectObject(hDC, font);
    wglUseFontBitmaps(hDC, 32, 96, base);
    SelectObject(hDC, oldfont);
    DeleteObject(font);
}

static void KillFont(void) {

    glDeleteLists(base, 96);
}

static void glPrint(const char *fmt, ...) {

    char text[256];
    va_list ap;

    if(fmt == NULL)
        return;

    va_start(ap, fmt);
        vsprintf(text, fmt, ap);
    va_end(ap);

    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

static int InitGL(void) {

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    BuildFont();

    return TRUE;
}

static int DrawGLScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(1.0f, 1.0f, -30.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-15.0f, -15.0f);
    glPrint("OKKKKKKKKKKKKKKKKKKAY ! - %7.2f", cnt1);

    cnt1 += 0.051f;
    cnt2 += 0.005f;

    return TRUE;
}*/

static void resize(int width, int height)
{
    if(height == 0)
        height = 1;

    const float ar = (float) width / (float) height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(90, ar, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}*/

/*void setTriangle(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
        glTranslatef(-0.4f, -2.0f, -4.0f);
        glVertex3f(0.4f, -2.0f, -4.0f);
		glVertex3f(0.4f, 2.0f, -4.0f);
		glVertex3f(-0.4f, 2.0f, -4.0f);
		glVertex3f(-0.4f, -2.0f, -4.0f);
	glEnd();

	glutSwapBuffers();
}*/

void setKapla(/*float pX, float pY, float pZ, float rX, float rY, float rZ*/) {

    glColor3f(0.76f, 0.42f, 0.0f);

    float rX = xRot;
    float rY = yRot;
    float rZ = zRot;

    float pX = xPos;
    float pY = yPos;
    float pZ = zPos;

    glPushMatrix();
        glTranslatef(pX, pY, pZ);
        glRotatef(angleRot, rX, rY, rZ);
        glScalef(1.0f, 3.0f, 15.0f);
        glutSolidCube(2);
    glPopMatrix();
}

void renderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    printf("   xCam : %f | yCam : %f\n", xCam, yCam);

    glPushMatrix();
        gluLookAt(xCam, yCam, zCam,
                  0.0f, 0.0f, -30.0f,
                  xVec, yVec, zVec);

        xPos = -10.0f;
        yPos = -10.0f;
        setKapla();

        xPos = 10.0f;
        yPos = 10.0f;
        setKapla();

    glPopMatrix();

    glutSwapBuffers();
}

/*static void printIt(char *str) {

    int len, i;

    len = strlen(str);
    glRasterPos2d(100, 700);

    for(i = 0; i < len; i++) {

        glColor3f(0.0f, 0.0f, 0.0f);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}*/

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'x':

            xRot += 0.1f;
            break;

        case 'y':

            yRot += 0.1f;
            break;

        case 'z':

            zRot += 0.1f;
            break;

        case 'a':

            angleRot += 1;
            break;

        case ' ':

            angleRot = 0;
            xRot = 0.0f;
            yRot = 0.0f;
            zRot = 1.0f;
            break;
    }

    /*char toPrint[80] = "";
    sprintf(toPrint, "Angle : %f  X : %f  Y : %f  Z : %f", angleRot, xRot, yRot, zRot);

    printIt(toPrint);*/

    glutPostRedisplay();
}

static void specialKey(int key, int xx, int yy) {

    float fraction = 0.1f;

    switch (key) {

		case GLUT_KEY_LEFT :

            angleCamTeta -= fraction;
			xCam = ((zCam - zPos) * (sin(angleCamTeta)));
			break;

		case GLUT_KEY_RIGHT :

            angleCamTeta += fraction;
			xCam = ((zCam - zPos) * (sin(angleCamTeta)));
			break;

		case GLUT_KEY_UP :

            angleCamPhi += fraction;
            camUp();
			break;

		case GLUT_KEY_DOWN :

            angleCamPhi -= fraction;
			yCam = ((zCam - zPos) * (sin(angleCamPhi)));
			break;
	}

    glutPostRedisplay();
}

static void camUp() {

    if((modulo(angleCamPhi, (2*M_PI))) >= 0 && (modulo(angleCamPhi, (2*M_PI))) < (M_PI / 2)) {

        yCam = ((zCam - zPos) * (sin(angleCamPhi)));
    }

    else if((modulo(angleCamPhi, (2*M_PI))) >= (M_PI / 2) && (modulo(angleCamPhi, (2*M_PI))) < M_PI) {

        yCam = ((zCam - zPos) * (sin(angleCamPhi)));
        zCam = zPos - zCam;
    }

    else if((modulo(angleCamPhi, (2*M_PI))) >= M_PI && (modulo(angleCamPhi, (2*M_PI))) < ((3 * M_PI) / 2)) {

        yCam = -((zCam - zPos) * (sin(angleCamPhi)));
        zCam = zPos - zCam;
    }

    else if((modulo(angleCamPhi, (2*M_PI))) >= ((3 * M_PI) / 2)) {

        yCam = -((zCam - zPos) * (sin(angleCamPhi)));
    }
}


float modulo(float x, float y)
{
    x -= y * abs(x/y);
    if (x >= 0.) return (x);
    else return (x+y);
}

float

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

//const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
//const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
//const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(resize);

	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

	glutMainLoop();

	return 1;

}
