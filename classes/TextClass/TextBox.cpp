#include "TextBox.h"

TextBox::TextBox() : borderStatus(false), selected(false) {}
TextBox::~TextBox() {}

bool TextBox::hasBorder() const
{
	return hasBorder;
}

void TextBox::setBorder(bool hasBorder)
{
	this->borderStatus = hasBorder;
}

bool TextBox::isSelected() const
{
	return selected;
}

void TextBox::setSelected(bool selected)
{
	this->selected = selected;
}
