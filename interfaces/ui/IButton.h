#ifndef IBUTTON_H
#define IBUTTON_H

#include <functional>
#include <string>
#include "Bounds.h"	 // contains bounds
#include "Color.h"

class IButton
{
   public:
	IButton()						   = default;
	virtual ~IButton()				   = default;
	IButton(const IButton&)			   = default;
	IButton& operator=(const IButton&) = default;
	IButton(IButton&&)				   = default;
	IButton& operator=(IButton&&)	   = default;

	// Button bounds
	virtual void				 setBounds(const Bounds& bounds) = 0;
	[[nodiscard]] virtual Bounds getBounds() const				 = 0;

	// Button color
	virtual void				setColor(const Color& color) = 0;
	[[nodiscard]] virtual Color getColor() const			 = 0;

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

	virtual float getValue() const		= 0;
	virtual void  setValue(float value) = 0;
};

#endif	// IBUTTON_H