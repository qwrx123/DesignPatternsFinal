#include "MenuBar.h"
#include "Bounds.h"
#include "ButtonClass.h"
#include <cassert>

MenuBar::MenuBar() : label("Menu Bar"), bounds(0, 0, 0, 0)
{
	buttons.push_back(
		std::make_shared<ButtonClass>("emptyEdge", Bounds(0, 0, 0, 0), bColor(0, 0, 0, 0)));
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
