//
// OpenGL_Animacja_Prostokat_ConsoleApplication1.cpp : Defines the entry point for the console application.
//
// Bounce.c
// Demonstrates a simple animated rectangle program with GLUT
// OpenGL SuperBible, 2nd Edition
// Richard S. Wright Jr.

#include "stdafx.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
 
#endif

double powerd(double x, int y);

double factorial_div(double value, int x);

double sine(double x)
{
	int i = 0;
	int j = 1;
	int sign = 1;
	double y1 = 0.0;
	double diff = 1000.0;
	if (x < 0.0)
	{
		x = -1 * x;
		sign = -1;
	}
	while (x > 360.0*3.1415926 / 180)
	{
		x = x - 360 * 3.1415926 / 180;
	}// End while(..)
	if (x > (270.0 * 3.1415926 / 180))
	{
		sign = sign * -1;
		x = 360.0*3.1415926 / 180 - x;
	}
	else if (x > (180.0 * 3.1415926 / 180))
	{
		sign = sign * -1;
		x = x - 180.0 *3.1415926 / 180;
	}
	else if (x > (90.0 * 3.1415926 / 180))
	{
		x = 180.0 *3.1415926 / 180 - x;
	}
	while (powerd(diff, 2) > 1.0E-16)
	{
		i++;
		diff = j * factorial_div(powerd(x, (2 * i - 1)), (2 * i - 1));
		y1 = y1 + diff;
		j = -1 * j;
	}// End while (..)
	return (sign * y1);
}
// End sine(..)

double powerd(double x, int y)
{
	int i = 0;
	double ans = 1.0;
	if (y == 0) return 1.000;
	else
	{
		while (i < y)
		{
			i++;
			ans = ans * x;
		}// End while(..)
	}// End else
	return ans;
}// End powerd(..)

double factorial_div(double value, int x)
{
	if (x == 0) return 1;
	else
	{
		while (x > 1)
		{
			value = value / x--;
		}// End while(..)
	}// End else
	return value;
}// End factorial_div(..)

double cosine(double x)
{
	int i = 0;
	int j = 1;
	int sign = 1;
	double y1 = 0.0;
	double diff = 1000.0;
	if (x < 0) x = -1 * x;
	while (x > 360.0*3.1415926 / 180)
	{
		x = x - 360 * 3.1415926 / 180;
	}
	if (x > (270 * (3.1415926 / 180)))
	{
		x = 360 * (3.1415926 / 180) - x;
	}
	if (x > (180 * (3.1415926 / 180)))
	{
		sign = -1;
		x = x - 180 * (3.1415926 / 180);
	}
	if (x > (90 * (3.1415926 / 180)))
	{
		sign = -1;
		x = 180 * (3.1415926 / 180) - x;
	}// End if(..)
	while (powerd(diff, 2) > 1.0E-16)
	{
		i++;
		diff = j * factorial_div(powerd(x, (2 * i - 2)), (2 * i - 2));
		y1 = y1 + diff;
		j = -1 * j;
	}// End while(..)
	return (y1*sign);
}// End cosine(..)

// Pocztkowy rozmiar i pozycja 

GLsizei rsize = 50.f;
GLfloat x1 = 50.0f;
GLfloat y1 = 50.0f;
// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;

GLfloat angle = 0.0f;

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	GLint trialangleAmount = 5;
	GLfloat twicePI = 2.f *3.14f;
	angle += 0.8f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x1, y1, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-x1, -y1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (GLint i = 0; i <= trialangleAmount; i++)
	{
		glVertex2f(
			x1 + ((6.0*cosine(i*twicePI / trialangleAmount)) * 4.0f),
			y1 + ((6.0*sine(i*twicePI / trialangleAmount)) * 4.0f)
			);
	}
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}
GLfloat xsteptemp = 0;
GLfloat ysteptemp = 0;

///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkoœæ
void TimerFunction(int value) {
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	//if (x1 < windowWidth - rsize || x1 < 0)
	//	xstep = -xstep;

	//// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	//if (y1 > windowHeight - rsize || y1 < 0)
	//	ystep = -ystep;
	GLboolean x_bool = false, y_bool = false;

	x1 += xsteptemp;
	y1 += ysteptemp;

	if (x1 == windowWidth - rsize && y1 == rsize) {
		xsteptemp = 0.f;
		ysteptemp = ystep;
	}

	if (x1 == windowWidth - rsize && y1 == windowHeight - rsize) {
		xsteptemp = -xstep;
		ysteptemp = 0.f;
	}

	if (x1 == rsize && y1 == windowHeight - rsize) {
		xsteptemp = 0.f;
		ysteptemp = -ystep;
	}

	if (x1 == rsize && y1 ==  rsize) {
		xsteptemp = xstep;
		ysteptemp = 0.f;
	}
	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	// przestrzeni¹ ograniczajc¹.     
	if (x1 > windowWidth - rsize)
		x1 = windowWidth - rsize - 1;

	if (y1 > windowHeight - rsize)
		y1 = windowHeight - rsize - 1;

	if (x1 < rsize) {
		x1 = rsize;
		xsteptemp = 0;
		ysteptemp = -1.0f;
	}

	if (y1 < rsize)
		y1 = rsize;

	// Wykonanie przesuniêcia 
	



	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	glClearColor(0.60f, 0.4f, 0.12f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT przy ka¿dej zmianie wielkoœci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk³adu wspó³rzêdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G³ówny punkt wejœcia programu
void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierszy program GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}