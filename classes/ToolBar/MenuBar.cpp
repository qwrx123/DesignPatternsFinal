#include "MenuBar.h"
#include "Bounds.h"
#include "ButtonClass.h"
#include <iostream>
#include <cmath>
#include <cassert>

const int defaultButtonWidth = 50;

Color black	 = {.r = 0.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F};
Color red	 = {.r = 1.0F, .g = 0.0F, .b = 0.0F, .a = 1.0F};
Color orange = {.r = 1.0F, .g = 0.6F, .b = 0.1F, .a = 1.0F};
Color yellow = {.r = 0.9F, .g = 0.9F, .b = 0.0F, .a = 1.0F};
Color green	 = {.r = 0.0F, .g = 0.7F, .b = 0.1F, .a = 1.0F};
Color blue	 = {.r = 0.0F, .g = 0.2F, .b = 0.9F, .a = 1.0F};
Color purple = {.r = 0.6F, .g = 0.0F, .b = 0.6F, .a = 1.0F};
Color white	 = {.r = 1.0F, .g = 1.0F, .b = 1.0F, .a = 1.0F};

MenuBar::MenuBar() : label("Menu Bar"), bounds{0, 0, 0, 0}, tool(nullptr)
{
	buttons.push_back(
		std::make_shared<ButtonClass>("emptyEdge", Bounds{0, 0, 0, 0}, Color{0, 0, 0, 0}));
}

MenuBar::~MenuBar()
{
	if (!buttons.empty())
	{
		buttons.clear();
	}
}

MenuBar::MenuBar(const MenuBar& other)
	: label(other.label),
	  bounds(other.bounds),
	  selectedIndex(other.selectedIndex),
	  buttons(std::move(other.cloneButtons()))
{
}

MenuBar& MenuBar::operator=(const MenuBar& other)
{
	if (this != &other)
	{
		label		  = other.label;
		bounds		  = other.bounds;
		selectedIndex = other.selectedIndex;
		buttons.clear();

		buttons = std::move(other.cloneButtons());
	}
	return *this;
}

MenuBar::MenuBar(MenuBar&& other) noexcept
	: label(std::move(other.label)),
	  bounds(other.bounds),
	  selectedIndex(other.selectedIndex),
	  buttons(std::move(other.buttons))
{
}

MenuBar& MenuBar::operator=(MenuBar&& other) noexcept
{
	if (this != &other)
	{
		label		  = std::move(other.label);
		bounds		  = other.bounds;
		selectedIndex = other.selectedIndex;
		buttons		  = std::move(other.buttons);

		other.selectedIndex = 0;  // Reset moved-from state
	}
	return *this;
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
	halfHeight = (bounds.bottom / 2) - bounds.top;
	quarterHeight = (bounds.bottom / 4) - bounds.top;
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

void MenuBar::setDefaultButtons()
{
	addButton(std::make_shared<ButtonClass>(
		"brush",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		black));
	addButton(std::make_shared<ButtonClass>(
		"eraser",
		Bounds{.top	   = bounds.top + (float) halfHeight,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"text",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		black));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		black));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top + (float) halfHeight,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		white));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		red));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top + (float) halfHeight,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		orange));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		yellow));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top + (float) halfHeight,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		green));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top,
			   .bottom = bounds.top + (float) halfHeight,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().right + 1,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right + defaultButtonWidth},
		blue));
	addButton(std::make_shared<ButtonClass>(
		"color",
		Bounds{.top	   = bounds.top + (float) halfHeight,
			   .bottom = bounds.bottom,
			   .left   = buttons.at(buttons.size() - 1)->getBounds().left,
			   .right  = buttons.at(buttons.size() - 1)->getBounds().right},
		purple));
}

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
		if (button->getBounds().contains(x, y) && action == KeyAction::Press)
		{
			std::string label = button->getLabel();
			if (label == "color")
			{
				tool->getActiveTool()->setColor(button->getColor());
			}
			else if (label == "text")
			{
				if (text->isTextToolActive())
				{
					text->setTextToolInactive();
					button->setColor(black);
				}
				else
				{
					text->setTextToolActive();
					button->setColor(green);
				}
			}
			else
			{
				tool->selectTool(label);
			}
		}
	}
}

void MenuBar::onKey(int key, KeyAction action) {}

void MenuBar::onChar(unsigned int codepoint) {}

void MenuBar::setToolPointer(const std::shared_ptr<IToolManager>& ptr)
{
	tool = ptr;
}

void MenuBar::setTextPointer(const std::shared_ptr<ITextManager>& ptr)
{
	text = ptr;
}

std::vector<std::shared_ptr<IButton>> MenuBar::cloneButtons() const
{
	std::vector<std::shared_ptr<IButton>> clonedButtons;

	for (const auto& btn : buttons)
	{
		auto btnPtr = std::dynamic_pointer_cast<ButtonClass>(btn);	// C++ be like that
		if (btnPtr)
		{
			clonedButtons.push_back(std::make_shared<ButtonClass>(*btnPtr));
		}
		else
		{
			assert(false);	// Welp, fix this
		}
	}

	return clonedButtons;
}
