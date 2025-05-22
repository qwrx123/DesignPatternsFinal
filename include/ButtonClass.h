#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include <functional>
#include <string>
#include "Bounds.h"
#include "IButton.h"

class ButtonClass : public IButton
{
   public:
	ButtonClass(std::string label, Bounds bounds, bColor color);
	~ButtonClass();

	void   setBounds(const Bounds& bounds) override;
	Bounds getBounds() const override;

	void   setColor(const bColor& color) override;
	bColor getColor() const override;

	bool isHovered() const override;
	void setHovered(bool hovered) override;
	bool isPressed() const override;
	void setPressed(bool pressed) override;

	std::string getLabel() const override;
	void		setLabel(const std::string& label) override;

	void onClick(std::function<void()> callback) override;

   private:
	Bounds		bounds;
	bColor		color;
	bool		hovered;
	bool		pressed;
	std::string label;
};

#endif