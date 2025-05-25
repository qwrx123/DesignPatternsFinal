#include "MenuBar.h"
#include "Bounds.h"
#include "ButtonClass.h"
#include <iostream>
#include <cmath>

MenuBar::MenuBar() : label("Menu Bar"), bounds{0, 0, 0, 0}, tool(nullptr)
{
	buttons.push_back(
		std::make_shared<ButtonClass>("emptyEdge", Bounds{0, 0, 0, 0}, Color(0, 0, 0, 0)));
	colors.push_back(black);
	colors.push_back(red);
	colors.push_back(green);
	colors.push_back(blue);
}

MenuBar::~MenuBar()
{
	if (!buttons.empty())
	{
		buttons.clear();
	}
}

std::string MenuBar::getLabel() const
{
	return label;
}

void MenuBar::setLabel(const std::string& label)
{
	this->label = label;
}

Bounds MenuBar::getBounds() const
{
	return bounds;
}

void MenuBar::setBounds(const Bounds& bounds)
{
	this->bounds = bounds;
}

bool MenuBar::isOpen() const
{
	return true;
}

bool MenuBar::isClosed() const
{
	return false;
}

void MenuBar::open() {}

void MenuBar::close() {}

void MenuBar::addButton(std::shared_ptr<IButton> button)
{
	buttons.push_back(button);
}

void MenuBar::clearButtons()
{
	buttons.clear();
}

const std::vector<std::shared_ptr<IButton>>& MenuBar::getButtons() const
{
	return buttons;
}

int MenuBar::getSelectedIndex() const
{
	return selectedIndex;
}

void MenuBar::setSelectedIndex(int index)
{
	selectedIndex = index;
}

std::shared_ptr<IButton> MenuBar::getSelectedItem() const
{
	return buttons.at(selectedIndex);
}

bool MenuBar::showSelectedLabelWhenClosed() const
{
	return false;
}

void MenuBar::setShowSelectedLabelWhenClosed(bool show) {}

void MenuBar::onMouseMove(double x, double y) {}

void MenuBar::onMouseButton(MouseButton click, KeyAction action, double x, double y)
{
	for (auto& button : buttons)
	{
		Bounds boundaries = button->getBounds();
		if (x >= boundaries.left && x <= boundaries.right && y >= boundaries.top &&
			y <= boundaries.bottom && action == KeyAction::Press)
		{
			std::cout << "click " << button->getLabel() << std::endl;
			i = (i + 1) % 4;
			button->setColor(colors.at(i));
			tool->getActiveTool()->setColor(button->getColor());
		}
	}
}

void MenuBar::onKey(int key, KeyAction action) {}

void MenuBar::onChar(unsigned int codepoint) {}

void MenuBar::setToolPointer(const std::shared_ptr<IToolManager>& ptr)
{
	tool = ptr;
}