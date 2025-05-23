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

	void onClick(std::function<void()> callback) override;

   private:
	Bounds		bounds;
	Color		color;
	bool		hovered = false;
	bool		pressed = false;
	std::string label;
};

#endif