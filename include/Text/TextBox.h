#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "ITextBox.h"
#include "Text.h"

class TextBox : public ITextBox, public Text
{
   public:
	TextBox();
	~TextBox() override;

	[[nodiscard]] bool hasBorder() const override;
	void setBorder(bool hasBorder) override;

	[[nodiscard]] bool isSelected() const override;
	void setSelected(bool selected) override;

   private:
	bool boarderStatus = true;
	bool selected = false;
};

#endif	// TEXTBOX_H