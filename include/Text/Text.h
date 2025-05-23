#ifndef TEXT_H
#define TEXT_H

#include "IText.h"

class Text : public IText
{
   public:
	Text();
	~Text();

	std::string getContent() const override;
	void		setContent(const std::string& text) override;

	Bounds getBounds() const override;
	void   setPosition(double x, double y) override;

	std::string getFontName() const override;
	void		setFontName(const std::string& fontName) override;

	int	 getFontSize() const override;
	void setFontSize(int size) override;

	Color getColor() const override;
	void  setColor(const Color& color) override;

	bool isEditable() const override;
	void setEditable(bool editable) override;

   private:
	std::string content;
	Bounds		bounds;
	std::string fontName;
	int			fontSize;
	Color		color;
	bool		editable;
};

#endif	// TEXT_H