#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "ITextBox.h"
#include "Text.h"

class TextBox : public ITextBox, public Text
{
   public:
	TextBox();
	~TextBox();

	bool hasBorder() const override;
	void setBorder(bool hasBorder) override;

	bool isSelected() const override;
	void setSelected(bool selected) override;

   private:
	bool boarderStatus;
	bool selected;
};

#endif	// TEXTBOX_H