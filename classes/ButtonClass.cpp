#include "ButtonClass.h"
#include <GLFW/glfw3.h>

ButtonClass::ButtonClass(double x, double y, double width, double height, double percentRed,
						 double percentGreen, double percentBlue)
	: left(x), top(y), red(percentRed), green(percentGreen), blue(percentBlue)
{
	right  = left + width - 1;
	bottom = top + height - 1;
}

ButtonClass::~ButtonClass() {}

double ButtonClass::getTop()
{
	return top;
}

double ButtonClass::getBottom()
{
	return bottom;
}

double ButtonClass::getLeft()
{
	return left;
}

double ButtonClass::getRight()
{
	return right;
}

void ButtonClass::renderButton()
{
	glBegin(GL_QUADS);
	glColor3f(.8, .8, .8);
	glVertex2f(left, top);
	glColor3f(.7, .7, .7);
	glVertex2f(right, top);
	glColor3f(.3, .3, .3);
	glVertex2f(right, bottom);
	glColor3f(.5, .5, .5);
	glVertex2f(left, bottom);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(red, green, blue);
	glVertex2f(left + 3, top + 3);
	glVertex2f(right - 3, top + 3);
	glVertex2f(right - 3, bottom - 3);
	glVertex2f(left + 3, bottom - 3);
	glEnd();
}