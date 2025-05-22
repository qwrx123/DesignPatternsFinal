#ifndef ITEXTBOX_H
#define ITEXTBOX_H

#include "IText.h"

class ITextBox : public IText
{
   public:
	virtual ~ITextBox() = default;

	virtual bool hasBorder() const		   = 0;
	virtual void setBorder(bool hasBorder) = 0;

	virtual bool isSelected() const			= 0;
	virtual void setSelected(bool selected) = 0;
};

#endif	// ITEXTBOX_H