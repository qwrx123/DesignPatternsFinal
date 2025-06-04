#ifndef ITEXT_H
#define ITEXT_H

#include <string>
#include "Bounds.h"
#include "Color.h"

class IText
{
   public:
	IText()						   = default;
	virtual ~IText()			   = default;
	IText(const IText&)			   = default;
	IText& operator=(const IText&) = default;
	IText(IText&&)				   = default;
	IText& operator=(IText&&)	   = default;

	[[nodiscard]] virtual std::string getContent() const				  = 0;
	virtual void					  setContent(const std::string& text) = 0;

	[[nodiscard]] virtual Bounds getBounds() const			   = 0;
	virtual void				 setPosition(float x, float y) = 0;

	[[nodiscard]] virtual std::string getFontName() const					   = 0;
	virtual void					  setFontName(const std::string& fontName) = 0;

	[[nodiscard]] virtual int getFontSize() const	= 0;
	virtual void			  setFontSize(int size) = 0;

	[[nodiscard]] virtual Color getColor() const			 = 0;
	virtual void				setColor(const Color& color) = 0;

	[[nodiscard]] virtual bool isEditable() const			   = 0;
	virtual void			   setEditable(bool editable)	   = 0;
	virtual void			   setBounds(const Bounds& bounds) = 0;
};

#endif	// ITEXT_H