#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "ITextBox.h"
#include "Text.h"

class TextBox : public ITextBox, public Text
{
   public:
    TextBox() = default;
    ~TextBox() override = default;

    bool hasBorder() const override;
    void setBorder(bool hasBorder) override;

    bool isSelected() const override;
    void setSelected(bool selected) override;

    private:
    bool borderStatus;
    bool selected;

};

#endif    // TEXTBOX_H