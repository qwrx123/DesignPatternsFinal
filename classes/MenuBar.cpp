#include "MenuBar.h"

MenuBar::MenuBar() {}

MenuBar::~MenuBar()
{
	if (!buttons.empty())
	{
		clearButtons();
	}
}

std::string MenuBar::getLabel() const override
{
	return label;
}

void MenuBar::setLabel(const std::string& label) override
{
	this->label = label;
}

Bounds MenuBar::getBounds() const override
{
	return bounds;
}

void MenuBar::setBounds(const Bounds& bounds) override
{
	this->bounds = bounds;
}

bool MenuBar::isOpen() const override
{
	return true;
}

bool MenuBar::isClosed() const override
{
	return false;
}

void MenuBar::open() override {}

void MenuBar::close() override {}

void MenuBar::addButton(std::shared_ptr<IButton> button) override
{
	buttons.insert(button);
}

void MenuBar::clearButtons() override
{
	buttons.clear();
}

const std::vector<std::shared_ptr<IButton>>& MenuBar::getButtons() const override
{
	return buttons;
}

int MenuBar::getSelectedIndex() const override
{
	return selectedIndex;
}

void MenuBar::setSelectedIndex(int index) override
{
	selectedIndex = index;
}

std::shared_ptr<IButton> MenuBar::getSelectedItem() const override
{
	return buttons.at(selectedIndex);
}

bool MenuBar::showSelectedLabelWhenClosed() const override
{
	return false;
}

void MenuBar::setShowSelectedLabelWhenClosed(bool show) override {}