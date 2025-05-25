#ifndef ITEXTBOX_H
#define ITEXTBOX_H

#include "IText.h"

class ITextBox : public IText
{
   public:
	ITextBox()							 = default;
	~ITextBox() override				 = default;
	ITextBox(const ITextBox&)			 = default;
	ITextBox& operator=(const ITextBox&) = default;
	ITextBox(ITextBox&&)				 = default;
	ITextBox& operator=(ITextBox&&)		 = default;

	[[nodiscard]] virtual bool hasBorder() const		 = 0;
	virtual void			   setBorder(bool hasBorder) = 0;

	[[nodiscard]] virtual bool isSelected() const		  = 0;
	virtual void			   setSelected(bool selected) = 0;
};

#endif	// ITEXTBOX_H