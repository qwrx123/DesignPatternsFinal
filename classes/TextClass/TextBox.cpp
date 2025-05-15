#include "TextBox.h"

TextBox::TextBox() : boarderStatus(false), selected(false) {}
TextBox::~TextBox() {}

bool TextBox::hasBorder() const
{
	return boarderStatus;
}

void TextBox::setBorder(bool hasBorder)
{
	this->boarderStatus = hasBorder;
}

bool TextBox::isSelected() const
{
	return selected;
}

void TextBox::setSelected(bool selected)
{
	this->selected = selected;
}
