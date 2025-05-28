#ifndef IMENU_H
#define IMENU_H

#include <memory>
#include <string>
#include <vector>
#include "IButton.h"

class IMenu
{
   public:
	IMenu()						   = default;
	virtual ~IMenu()			   = default;
	IMenu(const IMenu&)			   = default;
	IMenu& operator=(const IMenu&) = default;
	IMenu(IMenu&&)				   = default;
	IMenu& operator=(IMenu&&)	   = default;

	// Menu label
	[[nodiscard]] virtual std::string getLabel() const					 = 0;
	virtual void					  setLabel(const std::string& label) = 0;

	// Bounds of menu container
	[[nodiscard]] virtual Bounds getBounds() const				 = 0;
	virtual void				 setBounds(const Bounds& bounds) = 0;

	// Dropdown menu state
	[[nodiscard]] virtual bool isOpen() const	= 0;
	[[nodiscard]] virtual bool isClosed() const = 0;
	virtual void			   open()			= 0;
	virtual void			   close()			= 0;

	// Manage butons
	virtual void addButton(std::shared_ptr<IButton> button)								  = 0;
	virtual void clearButtons()															  = 0;
	[[nodiscard]] virtual const std::vector<std::shared_ptr<IButton>>& getButtons() const = 0;

	// Optional: selected item
	[[nodiscard]] virtual int					   getSelectedIndex() const	   = 0;
	virtual void								   setSelectedIndex(int index) = 0;
	[[nodiscard]] virtual std::shared_ptr<IButton> getSelectedItem() const	   = 0;

	// Optional: render label of selected item if closed
	[[nodiscard]] virtual bool showSelectedLabelWhenClosed() const		 = 0;
	virtual void			   setShowSelectedLabelWhenClosed(bool show) = 0;
};

#endif	// IMENU_H