#ifndef ITEXT_H
#define ITEXT_H

#include <string>
#include "Bounds.h"

struct Color
{
	float r, g, b, a;
};	// a = alpha is opacity

class IText
{
   public:
	virtual ~IText() = default;

	virtual std::string getContent() const					= 0;
	virtual void		setContent(const std::string& text) = 0;

	virtual Bounds getBounds() const			   = 0;
	virtual void   setPosition(double x, double y) = 0;

	virtual std::string getFontName() const						 = 0;
	virtual void		setFontName(const std::string& fontName) = 0;

	virtual int	 getFontSize() const   = 0;
	virtual void setFontSize(int size) = 0;

	virtual Color getColor() const			   = 0;
	virtual void  setColor(const Color& color) = 0;

	virtual bool isEditable() const			= 0;
	virtual void setEditable(bool editable) = 0;
};

#endif	// ITEXT_H