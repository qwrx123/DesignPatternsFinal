#ifndef ISTROKE_H
#define ISTROKE_H

#include <vector>
#include "Point.h"
#include "Color.h"

class IStroke
{
   public:
	IStroke()						   = default;
	virtual ~IStroke()				   = default;
	IStroke(const IStroke&)			   = default;
	IStroke& operator=(const IStroke&) = default;
	IStroke(IStroke&&)				   = default;
	IStroke& operator=(IStroke&&)	   = default;

	[[nodiscard]] virtual const std::vector<Point>& getPoints() const			  = 0;
	virtual void									addPoint(const Point& point)  = 0;
	[[nodiscard]] virtual float						getThickness() const		  = 0;
	virtual void									setThickness(float thickness) = 0;
	virtual void									setColor(const Color& color)  = 0;
	[[nodiscard]] virtual Color						getColor() const			  = 0;
	[[nodiscard]] virtual double					getLength() const			  = 0;
};

#endif	// ISTROKE_H