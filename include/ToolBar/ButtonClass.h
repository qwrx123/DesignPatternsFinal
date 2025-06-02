#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include <functional>
#include <string>
#include "Bounds.h"
#include "IButton.h"

class ButtonClass : public IButton
{
   public:
	ButtonClass(std::string label, Bounds bounds, Color color);
	~ButtonClass() override;
	ButtonClass(const ButtonClass& other)				 = default;
	ButtonClass& operator=(const ButtonClass& other)	 = default;
	ButtonClass(ButtonClass&& other) noexcept			 = default;
	ButtonClass& operator=(ButtonClass&& other) noexcept = default;

	void				 setBounds(const Bounds& bounds) override;
	[[nodiscard]] Bounds getBounds() const override;

	void				setColor(const Color& color) override;
	[[nodiscard]] Color getColor() const override;

	[[nodiscard]] bool isHovered() const override;
	void			   setHovered(bool hovered) override;
	[[nodiscard]] bool isPressed() const override;
	void			   setPressed(bool pressed) override;

	[[nodiscard]] std::string getLabel() const override;
	void					  setLabel(const std::string& label) override;

	void  onClick(std::function<void()> callback) override;
	float getValue() const override;
	void  setValue(float value) override;

   private:
	Bounds		bounds;
	Color		color;
	bool		hovered = false;
	bool		pressed = false;
	std::string label;
	float		value = 0.0f;
};

#endif