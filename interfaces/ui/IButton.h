#ifndef IBUTTON_H
#define IBUTTON_H

#include <functional>
#include <string>
#include "Bounds.h"	 // contains bounds

struct bColor
{
	float r, g, b, a;

	bColor() : r(0), g(0), b(0), a(1) {}

	bColor(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {}
};

class IButton
{
   public:
	IButton()		   = default;
	virtual ~IButton() = default;

	// Button bounds
	virtual void				 setBounds(const Bounds& bounds) = 0;
	[[nodiscard]] virtual Bounds getBounds() const				 = 0;

	// Button color
	virtual void				 setColor(const bColor& color) = 0;
	[[nodiscard]] virtual bColor getColor() const			   = 0;

	// Button state
	[[nodiscard]] virtual bool isHovered() const		= 0;
	virtual void			   setHovered(bool hovered) = 0;
	[[nodiscard]] virtual bool isPressed() const		= 0;
	virtual void			   setPressed(bool pressed) = 0;

	// Button label
	[[nodiscard]] virtual std::string getLabel() const					= 0;
	virtual void					  setLabel(const std::string& name) = 0;

	// Event callback
	virtual void onClick(std::function<void()> callback) = 0;
};

#endif	// IBUTTON_H