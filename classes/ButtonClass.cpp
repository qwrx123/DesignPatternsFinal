#include "ButtonClass.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "Bounds.h"

ButtonClass::ButtonClass(Bounds bounds, double percentRed, double percentGreen, double percentBlue)
	: red(percentRed), green(percentGreen), blue(percentBlue)
{
	this->bounds = bounds;
	hovered		 = false;
	pressed		 = false;
	label		 = "Button";
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

// for ease of rendering the buttons until proper renderer is done
void ButtonClass::renderButton()
{
	glBegin(GL_QUADS);
	glColor3f(.8, .8, .8);
	glVertex2f(bounds.left, bounds.top);
	glColor3f(.7, .7, .7);
	glVertex2f(bounds.right, bounds.top);
	glColor3f(.3, .3, .3);
	glVertex2f(bounds.right, bounds.bottom);
	glColor3f(.5, .5, .5);
	glVertex2f(bounds.left, bounds.bottom);

	glColor3f(red, green, blue);
	glVertex2f(bounds.left + 3, bounds.top + 3);
	glVertex2f(bounds.right - 3, bounds.top + 3);
	glVertex2f(bounds.right - 3, bounds.bottom - 3);
	glVertex2f(bounds.left + 3, bounds.bottom - 3);
	glEnd();
}