#include "ButtonClass.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "Bounds.h"

ButtonClass::ButtonClass(std::string label, Bounds bounds, Color color)
{
	this->label	 = label;
	this->bounds = bounds;
	this->color	 = color;
	hovered		 = false;
	pressed		 = false;
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

void ButtonClass::setColor(const Color& color)
{
	this->color = color;
}

Color ButtonClass::getColor() const
{
	return color;
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