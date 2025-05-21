#ifndef BUTTON_CLASS_H
#define BUTTON_CLASS_H

#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "Bounds.h"
#include "IButton.h"

class ButtonClass : public IButton
{
   public:
	ButtonClass(Bounds bounds, double percentRed, double percentGreen, double percentBlue);
	~ButtonClass();

	void   setBounds(const Bounds& bounds) override;
	Bounds getBounds() const override;

	bool isHovered() const override;
	void setHovered(bool hovered) override;
	bool isPressed() const override;
	void setPressed(bool pressed) override;

	std::string getLabel() const override;
	void		setLabel(const std::string& label) override;

	void onClick(std::function<void()> callback) override;

	void renderButton();

   private:
	Bounds		bounds;
	bool		hovered;
	bool		pressed;
	std::string label;

	double red;
	double green;
	double blue;
};

#endif