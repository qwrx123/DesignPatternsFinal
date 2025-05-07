#ifndef IBUTTON_H
#define IBUTTON_H

#include <functional>
#include <string>
#include "Bounds.h"	 // contains bounds

class IButton
{
   public:
	IButton()		   = default;
	virtual ~IButton() = default;

	// Button bounds
	virtual void   setBounds(const Bounds& bounds) = 0;
	virtual Bounds getBounds() const			   = 0;

	// Button state
	virtual bool isHovered() const		  = 0;
	virtual void setHovered(bool hovered) = 0;
	virtual bool isPressed() const		  = 0;
	virtual void setPressed(bool pressed) = 0;

	// Button label
	virtual std::string getLabel() const				  = 0;
	virtual void		setLabel(const std::string& name) = 0;

	// Event callback
	virtual void onClick(std::function<void()> callback) = 0;
};

#endif	// IBUTTON_H