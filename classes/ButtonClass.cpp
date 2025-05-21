#include "ButtonClass.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "Bounds.h"

ButtonClass::ButtonClass(double x, double y, double width, double height, double percentRed,
						 double percentGreen, double percentBlue)
	: left(x), top(y), red(percentRed), green(percentGreen), blue(percentBlue)
{
	right  = left + width - 1;
	bottom = top + height - 1;
}

ButtonClass::~ButtonClass() {}

void ButtonClass::setBounds(const Bounds& bounds)
{
	this->bounds = bounds;
}

Bounds ButtonClass::getBounds() const
{
	return bounds;
}

bool ButtonClass::isHovered() const
{
	return hovered;
}

void ButtonClass::setHovered(bool hovered)
{
	this->hovered = hovered;
}

bool ButtonClass::isPressed() const
{
	return pressed;
}

void ButtonClass::setPressed(bool pressed)
{
	this->pressed = pressed;
}

std::string ButtonClass::getLabel() const
{
	return label;
}

void ButtonClass::setLabel(const std::string& label)
{
	this->label = label;
}

// customize for specialized button classes inheriting from ButtonClass
void ButtonClass::onClick(std::function<void()> callback) {}

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