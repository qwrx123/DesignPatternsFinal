#include "Text.h"

Text::Text() {}

Text::~Text() {}

std::string Text::getContent() const
{
    return content;
}

void Text::setContent(const std::string& text)
{
    content = text;
}

Bounds Text::getBounds() const
{
    return bounds;
}

void Text::setPosition(double x, double y)
{
    bounds.left   = x;
    bounds.right  = x + bounds.right - bounds.left;
    bounds.top    = y;
    bounds.bottom = y + bounds.bottom - bounds.top;
}

std::string Text::getFontName() const
{
    return fontName;
}

void Text::setFontName(const std::string& fontName)
{
    this->fontName = fontName;
}

int Text::getFontSize() const
{
    return fontSize;
}

void Text::setFontSize(int size)
{
    fontSize = size;
}

Color Text::getColor() const
{
    return color;
}

void Text::setColor(const Color& color)
{
    this->color.a = color.a;
    this->color.r = color.r;
    this->color.g = color.g;
    this->color.b = color.b;    
}

bool Text::isEditable() const
{
    return editable;
}

void Text::setEditable(bool editable)
{
    this->editable = editable;
}