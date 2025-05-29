#ifndef TEXT_H
#define TEXT_H

#include "IText.h"

class Text : public IText
{
   public:
	Text();
	~Text() override;
	Text(const std::string& text, const Bounds& bounds, const std::string& fontName, int fontSize,
		 const Color& color, bool editable);

	Text(const Text& other)				   = default;
	Text& operator=(const Text& other)	   = default;
	Text(Text&& other) noexcept			   = default;
	Text& operator=(Text&& other) noexcept = default;

	[[nodiscard]] std::string getContent() const override;
	void					  setContent(const std::string& text) override;

	[[nodiscard]] Bounds getBounds() const override;
	void				 setPosition(float x, float y) override;

	[[nodiscard]] std::string getFontName() const override;
	void					  setFontName(const std::string& fontName) override;

	[[nodiscard]] int getFontSize() const override;
	void			  setFontSize(int size) override;

	[[nodiscard]] Color getColor() const override;
	void				setColor(const Color& color) override;

	[[nodiscard]] bool isEditable() const override;
	void			   setEditable(bool editable) override;

   private:
	std::string content;
	Bounds		bounds;
	std::string fontName;
	int			fontSize = 0;
	Color		color;
	bool		editable = false;
};

#endif	// TEXT_H