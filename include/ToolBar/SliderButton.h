#ifndef SLIDER_BUTTON_H
#define SLIDER_BUTTON_H

#include <functional>
#include <string>
#include "Bounds.h"
#include "IButton.h"

class SliderButton : public IButton
{
public:
    SliderButton(std::string label, Bounds bounds, Color color);
    ~SliderButton() override;
    SliderButton(const SliderButton& other) = default;
    SliderButton& operator=(const SliderButton& other) = default;
    SliderButton(SliderButton&& other) noexcept = default;
    SliderButton& operator=(SliderButton&& other) noexcept = default;

    void setBounds(const Bounds& bounds) override;
    [[nodiscard]] Bounds getBounds() const override;

    void setColor(const Color& color) override;
    [[nodiscard]] Color getColor() const override;

    [[nodiscard]] bool isHovered() const override;
    void setHovered(bool hovered) override;
    [[nodiscard]] bool isPressed() const override;
    void setPressed(bool pressed) override;

    [[nodiscard]] std::string getLabel() const override;
    void setLabel(const std::string& label) override;

    void onClick(std::function<void()> callback) override;

    float getValue() const;
    void setValue(float value);
    void setMinValue(float minValue);
    void setMaxValue(float maxValue);
    float getMinValue() const;
    float getMaxValue() const;
    void setOnValueChangeCallback(std::function<void(float)> callback);

private:
    Bounds bounds;
    Color color;
    bool hovered = false;
    bool pressed = false;
    std::string label;

    float value = 0.0F;
    float minValue = 0.0F;
    float maxValue = 1.0F;
    std::function<void(float)> onValueChangeCallback;

    void updateValueFromPosition(double mouseX);
};

#endif