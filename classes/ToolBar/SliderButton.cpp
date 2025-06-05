#include "SliderButton.h"
#include <utility>
#include <iostream>
#include "Bounds.h"

SliderButton::SliderButton(std::string label, Bounds bounds, Color color)
    : label(std::move(label)), bounds(bounds), color(color)
{
}

SliderButton::~SliderButton() = default;

void SliderButton::setBounds(const Bounds& bounds)
{
    this->bounds = bounds;
}

Bounds SliderButton::getBounds() const
{
    return bounds;
}

void SliderButton::setColor(const Color& color)
{
    this->color = color;
}

Color SliderButton::getColor() const
{
    return color;
}

bool SliderButton::isHovered() const
{
    return hovered;
}

void SliderButton::setHovered(bool hovered)
{
    this->hovered = hovered;
}

bool SliderButton::isPressed() const
{
    return pressed;
}

void SliderButton::setPressed(bool pressed)
{
    this->pressed = pressed;
}

std::string SliderButton::getLabel() const
{
    return label;
}

void SliderButton::setLabel(const std::string& label)
{
    this->label = label;
}

void SliderButton::onClick(std::function<void()> callback)
{
    // This function is not implemented in the original code, but you can add functionality here if needed.
}

float SliderButton::getValue() const
{
    return value;
}

void SliderButton::setValue(float value)
{
    if (value < minValue || value > maxValue)
    {
        std::cerr << "Value out of bounds: " << value << " (min: " << minValue << ", max: " << maxValue << ")\n";
        return;
    }
    this->value = value;
    if (onValueChangeCallback)
    {
        onValueChangeCallback(value);
    }
}

void SliderButton::setMinValue(float minValue)
{
    this->minValue = minValue;
    if (value < minValue)
    {
        setValue(minValue);
    }
}

void SliderButton::setMaxValue(float maxValue)
{
    this->maxValue = maxValue;
    if (value > maxValue)
    {
        setValue(maxValue);
    }
}

float SliderButton::getMinValue() const
{
    return minValue;
}

float SliderButton::getMaxValue() const
{
    return maxValue;
}

void SliderButton::setOnValueChangeCallback(std::function<void(float)> callback)
{
    this->onValueChangeCallback = std::move(callback);
}

void SliderButton::updateValueFromPosition(double mouseX)
{
    float normalizedValue = (float) (mouseX - bounds.left) / (bounds.right - bounds.left);

    normalizedValue = std::max(normalizedValue, minValue);
    normalizedValue = std::min(normalizedValue, maxValue);
    
    setValue(minValue + (normalizedValue * (maxValue - minValue)));
}
