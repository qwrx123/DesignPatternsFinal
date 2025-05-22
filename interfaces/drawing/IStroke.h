#ifndef ISTROKE_H
#define ISTROKE_H

#include <vector>
#include "Point.h"

struct Color
{
	float r, g, b, a;
};	// a = alpha is opacity

class IStroke
{
   public:
	IStroke()		   = default;
	virtual ~IStroke() = default;

	virtual const std::vector<Point>& getPoints() const				= 0;
	virtual void					  addPoint(const Point& point)	= 0;
	virtual float					  getThickness() const			= 0;
	virtual void					  setThickness(float thickness) = 0;
	virtual void					  setColor(const Color& color)	= 0;
	virtual Color					  getColor() const				= 0;
	virtual double					  getLength() const				= 0;
};

#endif	// ISTROKE_H