#ifndef ISTROKE_H
#define ISTROKE_H

#include <vector>

struct Point { double x, y; };
struct Color { float r, g, b, a; }; // a = alpha is opacity

class IStroke {
public:
 IStroke()			= default;
 virtual ~IStroke() = default;

 virtual const std::vector<Point>& getPoints() const	= 0;
 virtual float					   getThickness() const = 0;
 virtual Color					   getColor() const		= 0;
 virtual double					   getLength() const	= 0;
};

#endif // ISTROKE_H